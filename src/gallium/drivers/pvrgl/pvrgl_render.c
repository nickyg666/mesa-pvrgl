/*
 * pvrgl_render.c — M3: native hardware render path for pvrgl.
 *
 * Builds the full render infrastructure the kernel powervr driver requires
 * for GEOMETRY + FRAGMENT jobs:
 *   - global + local free lists
 *   - HWRT render-target dataset (TPC / vheap+rtc / mlist / region headers)
 *   - RENDER context (VDM callstack BO + minimal static state)
 *   - geometry + fragment fw streams, submitted via winsys render_submit
 *
 * Reference: mesa vulkan driver pvr_arch_job_render.c + pvr_drm_job_render.c.
 * Hand-ported into pvrgl (no Vulkan runtime objects), same pattern as the
 * TQ clear backend in pvrgl_tq.c.
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "pvrgl_render.h"
#include "pvrgl_screen.h"
#include "pvrgl_tq.h"
#include "pvrgl_resource.h"

#include "hwdef/rogue_hw_defs.h"
#include "hwdef/rogue_hw_utils.h"
#include "imagination/vulkan/pds/pvr_pds.h"
#include "imagination/vulkan/pvr_csb.h"
#include "imagination/vulkan/pvr_csb_enum_helpers.h"
#include "imagination/common/pvr_device_info.h"
#include "imagination/vulkan/pvr_formats.h"
#include "imagination/vulkan/pvr_job_common.h"
#include "imagination/vulkan/pvr_job_render.h"
#include "imagination/vulkan/pvr_mrt.h"
#include "imagination/vulkan/pvr_usc.h"
#include "imagination/vulkan/winsys/pvr_winsys.h"
#include "pco_uscgen_programs.h"
#include "util/log.h"
#include "util/macros.h"
#include "util/u_math.h"

#define PVRGL_RT_WIDTH 128u
#define PVRGL_RT_HEIGHT 128u
#define PVRGL_RT_SAMPLES 1u
#define PVRGL_RT_LAYERS 1u

#define DWORDS_PER_U64 2U

/* Same values as pvr_arch_device.c global free list. */
#define PVRGL_GLOBAL_FL_INITIAL (2U * 1024U * 1024U)
#define PVRGL_GLOBAL_FL_MAX (256U * 1024U * 1024U)
#define PVRGL_GLOBAL_FL_GROW (1U * 1024U * 1024U)
#define PVRGL_GLOBAL_FL_GROW_THRESHOLD 13U

/* pvr_arch_job_context.c. */
#define PVRGL_VDM_CALLSTACK_MAX_DEPTH 1U

/* pvr_arch_job_render.c. */
#define PVRGL_NUM_PC_ENTRIES_PER_PAGE 0x400U
#define PVRGL_NUM_PD_ENTRIES_PER_PAGE 0x200U
#define PVRGL_NUM_PT_ENTRIES_PER_PAGE 0x200U

struct pvrgl_render {
   struct pvrgl_screen *screen;

   /* Free lists (BOs kept alive for list lifetime). */
   struct pvr_winsys_free_list *global_fl;
   struct pvr_winsys_free_list *local_fl;
   struct pvrgl_bo global_fl_bo;
   struct pvrgl_bo local_fl_bo;

   /* HWRT render-target dataset. */
   struct pvr_winsys_rt_dataset *rt_dataset;
   struct pvrgl_bo vheap_rtc_bo;
   struct pvrgl_bo tpc_bo;
   struct pvrgl_bo mlist_bo;
   uint32_t mlist_size;
   struct pvrgl_bo rgn_hdr_bo;
   uint64_t rgn_headers_stride;
   uint64_t tpc_stride;

   /* Render context. */
   struct pvr_winsys_render_ctx *rctx;
   struct pvrgl_bo vdm_callstack_bo;

   /* Aux BOs referenced by job streams. */
   struct pvrgl_bo ctrl_stream_bo;    /* VDM ctrl stream (terminate only). */
   struct pvrgl_bo border_colour_bo;  /* zeroed, never read without textures. */
   struct pvrgl_bo event_pds_bo;      /* pixel-event PDS prog (EOT kicker). */

   /* BG-object clear (load-op) chain [pvr_arch_mrt.c:642 recipe], built once
    * at init; the frag stream packs bgnd_reg_values[] into CR_PDS_BGRND0/1/3
    * (both the bgnd and PR-bgnd slots). */
   struct pvrgl_bo bg_usc_bo;       /* USC clear shader (usc heap). */
   struct pvrgl_bo bg_pds_frag_bo;  /* PDS kick-USC prog (data|code). */
   struct pvrgl_bo bg_pds_tex_bo;   /* PDS DOUTD consts prog (data only). */
   struct pvrgl_bo bg_pds_unitex_bo; /* PDS unitex code prog (texunicode). */
   struct pvrgl_bo bg_const_bo;     /* clear-color dword (general heap). */
   uint64_t bgnd_reg_values[3];

   /* Render-context switch state (LLS buffers + PDS store/resume programs),
    * mirrors upstream pvr_render_ctx_switch_init() [pvr_arch_job_context.c].
    * The FW runs the geom ctx store/resume tasks on every job; with zeroed
    * base addrs it targets addr 0 -> DM_GEOM GUILTY_LOCKUP (2026-08-31). */
   struct pvrgl_bo vdm_state_bo;      /* LLS VDM resume buffer (general). */
   struct pvrgl_bo geom_state_bo;     /* LLS TA state buffer (general). */
   struct pvrgl_bo usc_store_bo;      /* CS_STORE_SR usc blob (usc heap). */
   struct pvrgl_bo usc_load_bo;       /* CS_LOAD_SR usc blob (usc heap). */
   struct pvrgl_bo sr_store_load_bo;  /* shared-regs state (pds heap). */
   struct pvrgl_bo pt_store_resume_bo;/* PT persistent temps (pds heap). */
   struct pvrgl_bo pt_store_prog_bo;
   struct pvrgl_bo pt_resume_prog_bo;
   struct pvrgl_bo sr_store_prog_bo;
   struct pvrgl_bo sr_load_prog_bo;
   struct pvr_pds_upload pt_store_up, pt_resume_up, sr_store_up, sr_load_up;
   uint32_t bg_temps;          /* USC temps (BGRND3.pds_tempsize). */
   uint32_t bg_tex_data_size;  /* DOUTD prog data size dwords (BGRND3). */
   uint32_t bg_shareds_count;  /* consts dwords (BGRND3.usc_sharedsize). */
   struct pvrgl_bo scissor_bo;        /* one full-RT IPF scissor entry. */
   struct pvrgl_bo depth_bias_bo;     /* one zeroed entry. */
   /* Bound render-target geometry (dataset cache key). */
   uint32_t tgt_w, tgt_h;
};

static uint32_t
pvrgl_rt_get_mlist_size(const struct pvr_winsys_free_list *global_fl,
                        const struct pvr_winsys_free_list *local_fl)
{
   /* pvr_rt_get_mlist_size() — sizes are in bytes (kernel stores pages). */
   uint64_t total_pages =
      ((2U * 1024U * 1024U) + (2U * 1024U * 1024U)) >>
      ROGUE_BIF_PM_PHYSICAL_PAGE_SHIFT;
   uint32_t num_pte_pages;
   uint32_t num_pde_pages;
   uint32_t num_pce_pages;
   uint32_t mlist_size;

   (void)global_fl;
   (void)local_fl;

   num_pte_pages =
      DIV_ROUND_UP(total_pages, PVRGL_NUM_PT_ENTRIES_PER_PAGE);
   num_pde_pages =
      DIV_ROUND_UP(num_pte_pages, PVRGL_NUM_PD_ENTRIES_PER_PAGE);
   num_pce_pages =
      DIV_ROUND_UP(num_pde_pages, PVRGL_NUM_PC_ENTRIES_PER_PAGE);

   mlist_size = (num_pce_pages + num_pde_pages + num_pte_pages) *
                ROGUE_NUM_PM_ADDRESS_SPACES * ROGUE_MLIST_ENTRY_STRIDE;

   return ALIGN_POT(mlist_size, ROGUE_BIF_PM_PHYSICAL_PAGE_SIZE);
}

static VkResult
pvrgl_render_bg_clear_init(struct pvrgl_render *r)
{
   struct pvrgl_screen *screen = r->screen;
   const struct pvr_device_info *dev_info = screen->dev_info;
   pco_ctx *pco = pvrgl_tq_pco_ctx(screen->tq_priv);
   uint32_t usc_bin_size;
   struct usc_mrt_resource mrt_res;
   struct usc_mrt_setup mrt_setup;
   struct pvr_load_op load_op;
   pco_shader *loadop;
   pco_data *fs_data;
   uint32_t *staging;
   VkResult vk;

   /* Minimal single-RT MRT setup: clear color -> USC output reg 0. */
   memset(&mrt_res, 0, sizeof(mrt_res));
   mrt_res.type = USC_MRT_RESOURCE_TYPE_OUTPUT_REG;
   mrt_res.intermediate_size = 4;
   mrt_res.reg.output_reg = 0;
   memset(&mrt_setup, 0, sizeof(mrt_setup));
   mrt_setup.num_render_targets = 1;
   mrt_setup.num_output_regs = 1;
   mrt_setup.mrt_resources = &mrt_res;

   memset(&load_op, 0, sizeof(load_op));
   load_op.is_hw_object = true;
   load_op.clears_loads_state.rt_clear_mask = 1U;
   load_op.clears_loads_state.dest_vk_format[0] = VK_FORMAT_B8G8R8A8_UNORM;
   load_op.clears_loads_state.depth_clear_to_reg = PVR_NO_DEPTH_CLEAR_TO_REG;
   load_op.clears_loads_state.mrt_setup = &mrt_setup;

   /* 1. USC clear shader [pvr_arch_mrt.c:649]. uscgen also fills
    *    shareds_count/const_shareds_count (pvr_usc.c:1278). */
   loadop = pvr_uscgen_loadop(pco, &load_op);
   if (!loadop)
      return VK_ERROR_UNKNOWN;

   r->bg_shareds_count = load_op.shareds_count;
   usc_bin_size = pco_shader_binary_size(loadop);

   vk = pvrgl_upload(screen, screen->heaps->usc_heap,
                     pco_shader_binary_data(loadop),
                     pco_shader_binary_size(loadop), 64, &r->bg_usc_bo);
   if (vk != VK_SUCCESS)
      goto err_loadop;

   /* 2. PDS kick-USC bgnd program [pvr_arch_mrt.c:575]. */
   fs_data = pco_shader_data(loadop);
   {
      struct pvr_pds_kickusc_program kick = { 0 };
      const pvr_dev_addr_t exec_addr =
         PVR_DEV_ADDR(r->bg_usc_bo.dev_addr + fs_data->common.entry_offset);

      pvr_pds_setup_doutu(&kick.usc_task_control,
                          exec_addr.addr,
                          fs_data->common.temps,
                          ROGUE_PDSINST_DOUTU_SAMPLE_RATE_INSTANCE,
                          fs_data->fs.uses.phase_change);
      pvr_pds_kick_usc(&kick, NULL, 0, false, PDS_GENERATE_SIZES);

      staging = calloc(kick.code_size + kick.data_size, 4);
      if (!staging) {
         vk = VK_ERROR_OUT_OF_HOST_MEMORY;
         goto err_usc_bo;
      }

      pvr_pds_kick_usc(&kick, staging, 0, false,
                       PDS_GENERATE_CODEDATA_SEGMENTS);

      /* pvr_gpu_upload_pds layout: data @0 (16B), code right after (16B). */
      vk = pvrgl_upload(screen, screen->heaps->pds_heap, staging,
                        PVR_DW_TO_BYTES(kick.data_size + kick.code_size), 16,
                        &r->bg_pds_frag_bo);
      free(staging);
      if (vk != VK_SUCCESS)
         goto err_usc_bo;
   }

   r->bg_temps = fs_data->common.temps;
   ralloc_free(loadop);
   loadop = NULL;

   /* 3. Clear-color constants: 1 dword (B8G8R8A8 accum) on general heap.
    *    Keep in sync with the USC clear reg0 value in the frag stream. */
   {
      const uint32_t const_data = 0xFF0000FFu; /* red in B8G8R8A8 dword */

      vk = pvrgl_upload(screen, screen->heaps->general_heap, &const_data,
                        sizeof(const_data), 4, &r->bg_const_bo);
      if (vk != VK_SUCCESS)
         goto err_frag_bo;
   }

   /* 4. DOUTD constants-load program — data-only, no code
    *    [pvr_arch_cmd_buffer.c:914]. */
   {
      struct pvr_pds_pixel_shader_sa_program sa = { 0 };

      sa.num_texture_dma_kicks = 1;
      pvr_csb_pack (&sa.texture_dma_address[0],
                    PDSINST_DOUT_FIELDS_DOUTD_SRC0, value) {
         value.sbase = PVR_DEV_ADDR(r->bg_const_bo.dev_addr);
      }
      pvr_csb_pack (&sa.texture_dma_control[0],
                    PDSINST_DOUT_FIELDS_DOUTD_SRC1, value) {
         value.dest = ROGUE_PDSINST_DOUTD_DEST_COMMON_STORE;
         value.bsize = r->bg_shareds_count;
      }

      pvr_pds_set_sizes_pixel_shader_sa_texture_data(&sa, dev_info);
      r->bg_tex_data_size = sa.data_size;

      staging = calloc(sa.data_size, 4);
      if (!staging) {
         vk = VK_ERROR_OUT_OF_HOST_MEMORY;
         goto err_const_bo;
      }
      pvr_pds_generate_pixel_shader_sa_texture_state_data(&sa, staging,
                                                          dev_info);

      vk = pvrgl_upload(screen, screen->heaps->pds_heap, staging,
                        PVR_DW_TO_BYTES(sa.data_size), 16,
                        &r->bg_pds_tex_bo);
      free(staging);
      if (vk != VK_SUCCESS)
         goto err_const_bo;
   }

   /* 4b. Unitex code program [pvr_arch_mrt.c:526] — 1 texture DMA kick,
    *    code-only. BGRND0.texunicode_addr points at its code. */
   {
      struct pvr_pds_pixel_shader_sa_program ux = { 0 };

      ux.num_texture_dma_kicks = 1;
      pvr_pds_set_sizes_pixel_shader_uniform_texture_code(&ux);

      staging = calloc(ux.code_size, 4);
      if (!staging) {
         vk = VK_ERROR_OUT_OF_HOST_MEMORY;
         goto err_const_bo;
      }
      pvr_pds_generate_pixel_shader_sa_code_segment(&ux, staging);

      vk = pvrgl_upload(screen, screen->heaps->pds_heap, staging,
                        PVR_DW_TO_BYTES(ux.code_size), 16,
                        &r->bg_pds_unitex_bo);
      free(staging);
      if (vk != VK_SUCCESS)
         goto err_const_bo;
   }

   /* 5. BGRND reg values [pvr_pds_bgnd_pack_state]. All addresses are FULL
    *    device addresses (data section start of each upload). */
   pvr_csb_pack (&r->bgnd_reg_values[0], CR_PDS_BGRND0_BASE, value) {
      value.shader_addr = PVR_DEV_ADDR(r->bg_pds_frag_bo.dev_addr);
      value.texunicode_addr = PVR_DEV_ADDR(r->bg_pds_unitex_bo.dev_addr);
   }
   pvr_csb_pack (&r->bgnd_reg_values[1], CR_PDS_BGRND1_BASE, value) {
      value.texturedata_addr = PVR_DEV_ADDR(r->bg_pds_tex_bo.dev_addr);
   }
   pvr_csb_pack (&r->bgnd_reg_values[2], CR_PDS_BGRND3_SIZEINFO, value) {
      value.usc_sharedsize =
         DIV_ROUND_UP(r->bg_shareds_count,
                      ROGUE_CR_PDS_BGRND3_SIZEINFO_USC_SHAREDSIZE_UNIT_SIZE);
      value.pds_texturestatesize =
         DIV_ROUND_UP(r->bg_tex_data_size,
                      ROGUE_CR_PDS_BGRND3_SIZEINFO_PDS_TEXTURESTATESIZE_UNIT_SIZE);
      value.pds_tempsize =
         DIV_ROUND_UP(r->bg_temps,
                      ROGUE_CR_PDS_BGRND3_SIZEINFO_PDS_TEMPSIZE_UNIT_SIZE);
   }

   mesa_logi("pvrgl: bg-clear ready (usc=%u B tex=%u B temps=%u "
             "shareds=%u bgrnd3=%016llx)",
             usc_bin_size, r->bg_tex_data_size * 4, r->bg_temps,
             r->bg_shareds_count, (unsigned long long)r->bgnd_reg_values[2]);

   return VK_SUCCESS;

err_const_bo:
   pvrgl_bo_free(screen, &r->bg_const_bo);
err_frag_bo:
   pvrgl_bo_free(screen, &r->bg_pds_frag_bo);
err_usc_bo:
   pvrgl_bo_free(screen, &r->bg_usc_bo);
err_loadop:
   if (loadop)
      ralloc_free(loadop);
   return vk;
}

static VkResult
pvrgl_render_dataset_init(struct pvrgl_render *r, uint32_t width, uint32_t height)
{
   struct pvrgl_screen *screen = r->screen;
   const struct pvr_device_info *dev_info = screen->dev_info;
   const struct pvr_device_runtime_info *runtime_info = screen->runtime_info;
   struct pvr_winsys_rt_dataset_create_info create_info;
   struct pvr_rt_mtile_info mtile;
   uint32_t tile_size_x, tile_size_y;
   uint32_t mtiles_x, mtiles_y;
   uint32_t num_tiles_x, num_tiles_y;
   uint32_t num_mtiles_x, num_mtiles_y;
   uint32_t max_num_mtiles;
   uint64_t tpc_size;
   uint64_t rgn_headers_size;
   uint32_t single_rgn_header_size;
   uint32_t version;
   uint32_t group_size;
   uint32_t cache_line_size;
   VkResult vk;

   /* ---- Macrotile info [ref pvr_arch_rt_mtile_info_init]. ---- */
   tile_size_x = PVR_GET_FEATURE_VALUE(dev_info, tile_size_x, 16U);
   tile_size_y = PVR_GET_FEATURE_VALUE(dev_info, tile_size_y, 16U);
   num_tiles_x = DIV_ROUND_UP(width, tile_size_x);
   num_tiles_y = DIV_ROUND_UP(height, tile_size_y);

   rogue_get_num_macrotiles_xy(dev_info, &mtiles_x, &mtiles_y);

   if (PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format)) {
      mtile.mtile_x1 = DIV_ROUND_UP(num_tiles_x, 8U) * 2U;
      mtile.mtile_y1 = DIV_ROUND_UP(num_tiles_y, 8U) * 2U;
      mtile.mtile_x2 = 0;
      mtile.mtile_y2 = 0;
      mtile.mtile_x3 = 0;
      mtile.mtile_y3 = 0;
      mtile.x_tile_max = ALIGN_POT(num_tiles_x, 2U) - 1U;
      mtile.y_tile_max = ALIGN_POT(num_tiles_y, 2U) - 1U;
   } else {
      mtile.mtile_x1 = ALIGN_POT(DIV_ROUND_UP(num_tiles_x, 4U), 4U);
      mtile.mtile_y1 = ALIGN_POT(DIV_ROUND_UP(num_tiles_y, 4U), 4U);
      mtile.mtile_x2 = mtile.mtile_x1 * 2U;
      mtile.mtile_y2 = mtile.mtile_y1 * 2U;
      mtile.mtile_x3 = mtile.mtile_x1 * 3U;
      mtile.mtile_y3 = mtile.mtile_y1 * 3U;
      mtile.x_tile_max = num_tiles_x - 1U;
      mtile.y_tile_max = num_tiles_y - 1U;
   }
   mtile.tile_size_x = tile_size_x;
   mtile.tile_size_y = tile_size_y;
   mtile.num_tiles_x = num_tiles_x;
   mtile.num_tiles_y = num_tiles_y;
   mtile.mtiles_x = mtiles_x;
   mtile.mtiles_y = mtiles_y;
   mtile.tiles_per_mtile_x = mtile.mtile_x1;
   mtile.tiles_per_mtile_y = mtile.mtile_y1;

   cache_line_size = pvr_get_slc_cache_line_size(dev_info);

   /* ---- TPC BO. ---- */
   num_mtiles_x = mtiles_x * mtile.tiles_per_mtile_x;
   num_mtiles_y = mtiles_y * mtile.tiles_per_mtile_y;
   max_num_mtiles = MAX2(util_next_power_of_two64(num_mtiles_x),
                         util_next_power_of_two64(num_mtiles_y));
   tpc_size = (uint64_t)max_num_mtiles * max_num_mtiles;

   if (PVR_FEATURE_VALUE(dev_info, simple_parameter_format_version, &version))
      version = 0;
   if (version == 2)
      tpc_size /= (2U * 2U);
   tpc_size *= ROGUE_TAIL_POINTER_SIZE;
   r->tpc_stride = 0;
   tpc_size = ALIGN_POT(tpc_size, ROGUE_TE_TPC_CACHE_LINE_SIZE);

   vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                     tpc_size, ROGUE_CR_TE_TPC_ADDR_BASE_ALIGNMENT,
                     &r->tpc_bo);
   if (vk != VK_SUCCESS)
      goto err_free;

   /* ---- MList BO (macrotile array size is 0 for SIPF cores). ---- */
   {
      uint32_t mlist_size =
         pvrgl_rt_get_mlist_size(r->global_fl, r->local_fl);
      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        mlist_size * 2U,
                        ROGUE_CR_PM_MTILE_ARRAY_BASE_ADDR_ALIGNMENT,
                        &r->mlist_bo);
      if (vk != VK_SUCCESS)
         goto err_tpc;
      r->mlist_size = mlist_size;
   }

   /* ---- Region headers BO. ---- */
   single_rgn_header_size = rogue_get_region_header_size(dev_info);
   if (PVR_FEATURE_VALUE(dev_info, simple_parameter_format_version, &version))
      version = 0;
   group_size = version == 2 ? 2U : 1U;
   num_mtiles_x = mtiles_x * mtile.tiles_per_mtile_x;
   num_mtiles_y = mtiles_y * mtile.tiles_per_mtile_y;

   rgn_headers_size = (uint64_t)(num_mtiles_x / group_size);
   rgn_headers_size *= (num_mtiles_y / group_size);
   rgn_headers_size *= single_rgn_header_size;

   if (PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format))
      rgn_headers_size =
         ALIGN_POT(rgn_headers_size, ROGUE_CR_TE_PSGREGION_ADDR_BASE_ALIGNMENT);

   r->rgn_headers_stride = rgn_headers_size;

   vk = pvrgl_upload(screen, screen->heaps->rgn_hdr_heap, NULL,
                     rgn_headers_size * 2U,
                     ROGUE_CR_TE_PSGREGION_ADDR_BASE_ALIGNMENT,
                     &r->rgn_hdr_bo);
   if (vk != VK_SUCCESS)
      goto err_mlist;

   /* ---- RT dataset create info. ---- */
   memset(&create_info, 0, sizeof(create_info));
   create_info.local_free_list = r->local_fl;
   create_info.width = width;
   create_info.height = height;
   create_info.samples = PVRGL_RT_SAMPLES;
   create_info.layers = PVRGL_RT_LAYERS;

   if (PVR_HAS_ENHANCEMENT(dev_info, 42307)) {
      float value;
      value = ROGUE_ISP_MERGE_LOWER_LIMIT_NUMERATOR / (float)width;
      create_info.isp_merge_lower_x = fui(value);
      value = ROGUE_ISP_MERGE_UPPER_LIMIT_NUMERATOR / (float)width;
      create_info.isp_merge_upper_x = fui(value);
      value = ROGUE_ISP_MERGE_LOWER_LIMIT_NUMERATOR / (float)height;
      create_info.isp_merge_lower_y = fui(value);
      value = ROGUE_ISP_MERGE_UPPER_LIMIT_NUMERATOR / (float)height;
      create_info.isp_merge_upper_y = fui(value);
      value = ((float)width * ROGUE_ISP_MERGE_SCALE_FACTOR) /
              (ROGUE_ISP_MERGE_UPPER_LIMIT_NUMERATOR -
               ROGUE_ISP_MERGE_LOWER_LIMIT_NUMERATOR);
      create_info.isp_merge_scale_x = fui(value);
      value = ((float)height * ROGUE_ISP_MERGE_SCALE_FACTOR) /
              (ROGUE_ISP_MERGE_UPPER_LIMIT_NUMERATOR -
               ROGUE_ISP_MERGE_LOWER_LIMIT_NUMERATOR);
      create_info.isp_merge_scale_y = fui(value);
   }

   create_info.vheap_table_dev_addr.addr = r->vheap_rtc_bo.dev_addr;
   create_info.rtc_dev_addr.addr = 0; /* layers == 1 -> no RTC */
   create_info.tpc_dev_addr.addr = r->tpc_bo.dev_addr;
   create_info.tpc_stride = r->tpc_stride;
   create_info.tpc_size = tpc_size;
   create_info.rt_datas[0].pm_mlist_dev_addr.addr = r->mlist_bo.dev_addr;
   create_info.rt_datas[0].macrotile_array_dev_addr.addr = 0;
   create_info.rt_datas[0].rgn_header_dev_addr.addr = r->rgn_hdr_bo.dev_addr;
   create_info.rt_datas[1].pm_mlist_dev_addr.addr =
      r->mlist_bo.dev_addr + r->mlist_size;
   create_info.rt_datas[1].macrotile_array_dev_addr.addr = 0;
   create_info.rt_datas[1].rgn_header_dev_addr.addr =
      r->rgn_hdr_bo.dev_addr + rgn_headers_size;

   /* rgn_header_size: number of region headers for SIPF. */
   create_info.rgn_header_size =
      (num_mtiles_x / group_size) * (num_mtiles_y / group_size);

   vk = screen->ws->ops->render_target_dataset_create(
      screen->ws, &create_info, dev_info, &r->rt_dataset);
   if (vk != VK_SUCCESS)
      goto err_rgn;

   /* ---- ISP scissor BO (size-dependent). ---- */
   {
      uint32_t scissor[2] = { 0 };
      pvr_csb_pack (&scissor[0], IPF_SCISSOR_WORD_0, w0) {
         w0.scw0_xmax = width;
         w0.scw0_xmin = 0;
      }
      pvr_csb_pack (&scissor[1], IPF_SCISSOR_WORD_1, w1) {
         w1.scw1_ymax = height;
         w1.scw1_ymin = 0;
      }
      vk = pvrgl_upload(screen, screen->heaps->general_heap, scissor,
                        sizeof(scissor), cache_line_size, &r->scissor_bo);
      if (vk != VK_SUCCESS)
         goto err_dataset;
   }

   mesa_logi("pvrgl: dataset %ux%u ready (fl=%llu/%u)",
             width, height,
             (unsigned long long)runtime_info->min_free_list_size,
             PVRGL_GLOBAL_FL_INITIAL);
   return VK_SUCCESS;

err_dataset:
   screen->ws->ops->render_target_dataset_destroy(r->rt_dataset);
   r->rt_dataset = NULL;
err_rgn:
   pvrgl_bo_free(screen, &r->rgn_hdr_bo);
err_mlist:
   pvrgl_bo_free(screen, &r->mlist_bo);
err_tpc:
   pvrgl_bo_free(screen, &r->tpc_bo);
err_free:
   return vk;
}

static VkResult
pvrgl_render_bind_target(struct pvrgl_render *r, uint32_t width, uint32_t height)
{
   struct pvrgl_screen *screen = r->screen;
   VkResult vk;

   if (r->rt_dataset && r->tgt_w == width && r->tgt_h == height)
      return VK_SUCCESS;

   if (r->rt_dataset) {
      screen->ws->ops->render_target_dataset_destroy(r->rt_dataset);
      r->rt_dataset = NULL;
      pvrgl_bo_free(screen, &r->scissor_bo);
      pvrgl_bo_free(screen, &r->rgn_hdr_bo);
      pvrgl_bo_free(screen, &r->mlist_bo);
      pvrgl_bo_free(screen, &r->tpc_bo);
   }

   vk = pvrgl_render_dataset_init(r, width, height);
   if (vk != VK_SUCCESS)
      return vk;

   r->tgt_w = width;
   r->tgt_h = height;
   return VK_SUCCESS;
}

#define PVRGL_PDS_TASK_PROGRAM_SIZE 256U

/* ---- Context-switch program staging (upstream pvr_gpu_upload_pds
 * semantics with pvrgl_upload: [data | pad | code] in one pds-heap BO,
 * offsets heap-relative bytes, sizes dwords). ---- */
static VkResult
pvrgl_pds_prog_upload(struct pvrgl_screen *screen,
                      const uint32_t *data, uint32_t data_size_dw,
                      uint32_t data_align,
                      const uint32_t *code, uint32_t code_size_dw,
                      uint32_t code_align,
                      uint64_t min_align,
                      struct pvr_pds_upload *up, struct pvrgl_bo *bo_out)
{
   const size_t data_size = (size_t)data_size_dw * 4;
   const size_t code_size = (size_t)code_size_dw * 4;
   const uint64_t data_aligned = ALIGN_POT(data_size, data_align);
   const uint64_t code_aligned = ALIGN_POT(code_size, code_align);
   const uint32_t code_off = ALIGN_POT(data_aligned, code_align);
   const uint64_t bo_align = MAX2(min_align, data_align);
   const uint64_t bo_size = code ? (code_off + code_aligned) : data_aligned;
   uint32_t *stage;
   VkResult vk;

   stage = calloc(1, bo_size);
   if (!stage)
      return VK_ERROR_OUT_OF_HOST_MEMORY;

   if (data)
      memcpy(stage, data, data_size);
   if (code)
      memcpy((uint8_t *)stage + code_off, code, code_size);

   vk = pvrgl_upload(screen, screen->heaps->pds_heap, stage,
                     bo_size, bo_align, bo_out);
   free(stage);
   if (vk != VK_SUCCESS)
      return vk;

   up->data_offset = bo_out->heap_offset;
   up->data_size = data_aligned / 4;
   up->code_offset = bo_out->heap_offset + code_off;
   up->code_size = code_aligned / 4;
   return VK_SUCCESS;
}

/* Upstream pvr_pds_ctx_sr_program_setup() [pvr_arch_job_context.c:281]. */
static void
pvrgl_ctx_sr_setup(uint64_t usc_program_upload_offset, uint8_t usc_temps,
                   uint64_t sr_addr,
                   struct pvr_pds_shared_storing_program *program_out)
{
   *program_out = (struct pvr_pds_shared_storing_program){
      .cc_enable = false,
      .doutw_control = {
         .dest_store = PDS_UNIFIED_STORE,
         .num_const64 = 2,
         .doutw_data = {
            [0] = sr_addr,
            [1] = sr_addr + ROGUE_LLS_SHARED_REGS_RESERVE_SIZE,
         },
         .last_instruction = false,
      },
   };

   pvr_pds_setup_doutu(&program_out->usc_task.usc_task_control,
                       usc_program_upload_offset, usc_temps,
                       ROGUE_PDSINST_DOUTU_SAMPLE_RATE_INSTANCE, false);
}

/* Upstream pvr_rogue_get_vdmctrl_pds_state_words() [pvr_arch_job_context.c]. */
static void
pvrgl_vdmctrl_pds_state_words(const struct pvr_pds_upload *pds_program,
                              enum ROGUE_VDMCTRL_USC_TARGET usc_target,
                              uint8_t usc_unified_size,
                              uint32_t *state0_out, uint32_t *state1_out)
{
   pvr_csb_pack (state0_out, VDMCTRL_PDS_STATE0, state) {
      const uint32_t pds_data_size = PVR_DW_TO_BYTES(pds_program->data_size);

      state.dm_target = ROGUE_VDMCTRL_DM_TARGET_VDM;
      state.usc_target = usc_target;
      state.usc_common_size = 0;
      state.usc_unified_size = usc_unified_size;
      state.pds_temp_size = 0;
      state.pds_data_size =
         pds_data_size / ROGUE_VDMCTRL_PDS_STATE0_PDS_DATA_SIZE_UNIT_SIZE;
   }

   pvr_csb_pack (state1_out, VDMCTRL_PDS_STATE1, state) {
      state.pds_data_addr = PVR_DEV_ADDR(pds_program->data_offset);
      state.sd_type = ROGUE_VDMCTRL_SD_TYPE_PDS;
      state.sd_next_type = ROGUE_VDMCTRL_SD_TYPE_PDS;
   }
}

VkResult
pvrgl_render_init(struct pvrgl_screen *screen, struct pvrgl_render **out)
{
   const struct pvr_device_info *dev_info = screen->dev_info;
   const struct pvr_device_runtime_info *runtime_info = screen->runtime_info;
   struct pvrgl_render *r;
   uint32_t cache_line_size;
   VkResult vk;

   r = calloc(1, sizeof(*r));
   if (!r)
      return VK_ERROR_OUT_OF_HOST_MEMORY;
   r->screen = screen;

   /* ---- Global free list. ---- */
   {
      struct pvr_winsys_vma *fl_vma = NULL;
      struct pvrgl_bo fl_bo;
      uint32_t max_pages =
         PVRGL_GLOBAL_FL_MAX >> ROGUE_BIF_PM_PHYSICAL_PAGE_SHIFT;
      uint32_t fl_size = ALIGN_POT(max_pages * 4U, 64U * 1024U);

      vk = pvrgl_upload_flags(screen, screen->heaps->general_heap, NULL,
                              fl_size, 64U * 1024U,
                              PVR_WINSYS_BO_FLAG_GPU_UNCACHED |
                                 PVR_WINSYS_BO_FLAG_PM_FW_PROTECT,
                              &fl_bo, &fl_vma);
      if (vk != VK_SUCCESS)
         goto err_free;

      vk = screen->ws->ops->free_list_create(
         screen->ws, fl_vma,
         PVRGL_GLOBAL_FL_INITIAL >> ROGUE_BIF_PM_PHYSICAL_PAGE_SHIFT,
         max_pages,
         PVRGL_GLOBAL_FL_GROW >> ROGUE_BIF_PM_PHYSICAL_PAGE_SHIFT,
         PVRGL_GLOBAL_FL_GROW_THRESHOLD, NULL, &r->global_fl);
      if (vk != VK_SUCCESS) {
         pvrgl_bo_free(screen, &fl_bo);
         goto err_free;
      }
      /* Keep the BO alive for the life of the free list. */
      r->global_fl_bo = fl_bo;
   }

   /* ---- Local free list (child of global, fixed min size). ---- */
   {
      struct pvr_winsys_vma *fl_vma = NULL;
      struct pvrgl_bo fl_bo;
      uint64_t local_size =
         align64(runtime_info->min_free_list_size, 64U * 1024U);
      uint32_t min_pages =
         local_size >> ROGUE_BIF_PM_PHYSICAL_PAGE_SHIFT;
      uint32_t fl_size = ALIGN_POT(MAX2(min_pages, 1U) * 4U, 64U * 1024U);

      vk = pvrgl_upload_flags(screen, screen->heaps->general_heap, NULL,
                              fl_size, 64U * 1024U,
                              PVR_WINSYS_BO_FLAG_GPU_UNCACHED |
                                 PVR_WINSYS_BO_FLAG_PM_FW_PROTECT,
                              &fl_bo, &fl_vma);
      if (vk != VK_SUCCESS)
         goto err_global_fl;

      vk = screen->ws->ops->free_list_create(
         screen->ws, fl_vma, min_pages, min_pages, 0, 0, r->global_fl,
         &r->local_fl);
      if (vk != VK_SUCCESS) {
         pvrgl_bo_free(screen, &fl_bo);
         goto err_global_fl;
      }
      r->local_fl_bo = fl_bo;
   }

   cache_line_size = pvr_get_slc_cache_line_size(dev_info);

   /* ---- VHEAP + RTC BO. ---- */
   {
      uint64_t vheap_size = ROGUE_CR_PM_VHEAP_TABLE_SIZE *
                            ROGUE_PM_VHEAP_ENTRY_SIZE;
      uint64_t align =
         MAX2(ROGUE_CR_PM_VHEAP_TABLE_BASE_ADDR_ALIGNMENT,
              ROGUE_CR_TA_RTC_ADDR_BASE_ALIGNMENT);
      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        vheap_size, align, &r->vheap_rtc_bo);
      if (vk != VK_SUCCESS)
         goto err_local_fl;
   }

   /* ---- VDM callstack BO + RENDER context. ---- */
   {
      struct pvr_winsys_render_ctx_create_info rctx_info;

      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        sizeof(uint64_t) * PVRGL_VDM_CALLSTACK_MAX_DEPTH,
                        ROGUE_CR_VDM_CALL_STACK_POINTER_ADDR_ALIGNMENT,
                        &r->vdm_callstack_bo);
      if (vk != VK_SUCCESS)
         goto err_vheap;

      /* ---- Context-switch LLS buffers + PDS store/resume programs. ---- */
      const pco_precomp_data *sr_store_pre =
         (const pco_precomp_data *)pco_usclib_common[CS_STORE_SR_1024_COMMON];
      const pco_precomp_data *sr_load_pre =
         (const pco_precomp_data *)pco_usclib_common[CS_LOAD_SR_256_COMMON];
      uint64_t usc_store_off, usc_load_off;

      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        ROGUE_LLS_VDM_CONTEXT_RESUME_BUFFER_SIZE,
                        ROGUE_LLS_VDM_CONTEXT_RESUME_BUFFER_ALIGNMENT,
                        &r->vdm_state_bo);
      if (vk != VK_SUCCESS)
         goto err_callstack;

      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        ROGUE_LLS_TA_STATE_BUFFER_SIZE,
                        ROGUE_LLS_TA_STATE_BUFFER_ALIGNMENT,
                        &r->geom_state_bo);
      if (vk != VK_SUCCESS)
         goto err_vdm_state;

      vk = pvrgl_upload(screen, screen->heaps->usc_heap,
                        sr_store_pre->binary,
                        sr_store_pre->size_dwords * sizeof(uint32_t),
                        cache_line_size, &r->usc_store_bo);
      if (vk != VK_SUCCESS)
         goto err_geom_state;

      vk = pvrgl_upload(screen, screen->heaps->usc_heap,
                        sr_load_pre->binary,
                        sr_load_pre->size_dwords * sizeof(uint32_t),
                        cache_line_size, &r->usc_load_bo);
      if (vk != VK_SUCCESS)
         goto err_usc_store;

      usc_store_off = r->usc_store_bo.dev_addr -
                      screen->heaps->usc_heap->base_addr.addr;
      usc_load_off = r->usc_load_bo.dev_addr -
                     screen->heaps->usc_heap->base_addr.addr;

      vk = pvrgl_upload(screen, screen->heaps->pds_heap, NULL,
                        ROGUE_LLS_USC_SHARED_REGS_BUFFER_SIZE +
                           ROGUE_LLS_SHARED_REGS_RESERVE_SIZE,
                        cache_line_size, &r->sr_store_load_bo);
      if (vk != VK_SUCCESS)
         goto err_usc_load;

      vk = pvrgl_upload(screen, screen->heaps->pds_heap, NULL,
                        ROGUE_LLS_PDS_PERSISTENT_TEMPS_BUFFER_SIZE,
                        ROGUE_LLS_PDS_PERSISTENT_TEMPS_BUFFER_ALIGNMENT,
                        &r->pt_store_resume_bo);
      if (vk != VK_SUCCESS)
         goto err_sr_state;

      /* PT store (stream_out_terminate). */
      {
         struct pvr_pds_stream_out_terminate_program program = { 0 };
         uint32_t *staging, *code;
         size_t staging_size;

         program.pds_persistent_temp_size_to_store =
            ROGUE_LLS_PDS_PERSISTENT_TEMPS_BUFFER_SIZE / 4;
         program.dev_address_for_storing_persistent_temp =
            r->pt_store_resume_bo.dev_addr;

         pvr_pds_generate_stream_out_terminate_program(
            &program, NULL, PDS_GENERATE_SIZES, dev_info);

         staging_size = (program.stream_out_terminate_pds_data_size +
                         program.stream_out_terminate_pds_code_size) *
                        sizeof(*staging);
         staging = calloc(1, staging_size);
         if (!staging) {
            vk = VK_ERROR_OUT_OF_HOST_MEMORY;
            goto err_pt_state;
         }
         code = pvr_pds_generate_stream_out_terminate_program(
            &program, staging, PDS_GENERATE_DATA_SEGMENT, dev_info);
         pvr_pds_generate_stream_out_terminate_program(
            &program, code, PDS_GENERATE_CODE_SEGMENT, dev_info);

         vk = pvrgl_pds_prog_upload(
            screen, staging, program.stream_out_terminate_pds_data_size,
            ROGUE_TA_STATE_STREAM_OUT1_PDS_DATA_SIZE_UNIT_SIZE,
            code, program.stream_out_terminate_pds_code_size,
            ROGUE_TA_STATE_STREAM_OUT1_PDS_DATA_SIZE_UNIT_SIZE,
            cache_line_size, &r->pt_store_up, &r->pt_store_prog_bo);
         free(staging);
         if (vk != VK_SUCCESS)
            goto err_pt_state;
      }

      /* PT resume (stream_out_init). */
      {
         struct pvr_pds_stream_out_init_program program = { 0 };
         uint32_t *staging, *code;
         size_t staging_size;

         program.num_buffers = 1;
         program.pds_buffer_data_size[0] =
            ROGUE_LLS_PDS_PERSISTENT_TEMPS_BUFFER_SIZE / 4;
         program.dev_address_for_buffer_data[0] =
            r->pt_store_resume_bo.dev_addr;

         pvr_pds_generate_stream_out_init_program(
            &program, NULL, false, PDS_GENERATE_SIZES, dev_info);

         staging_size = (program.stream_out_init_pds_data_size +
                         program.stream_out_init_pds_code_size) *
                        sizeof(*staging);
         staging = calloc(1, staging_size);
         if (!staging) {
            vk = VK_ERROR_OUT_OF_HOST_MEMORY;
            goto err_pt_store;
         }
         code = pvr_pds_generate_stream_out_init_program(
            &program, staging, false, PDS_GENERATE_DATA_SEGMENT, dev_info);
         pvr_pds_generate_stream_out_init_program(
            &program, code, false, PDS_GENERATE_CODE_SEGMENT, dev_info);

         vk = pvrgl_pds_prog_upload(
            screen, staging, program.stream_out_init_pds_data_size,
            ROGUE_TA_STATE_STREAM_OUT1_PDS_DATA_SIZE_UNIT_SIZE,
            code, program.stream_out_init_pds_code_size,
            ROGUE_TA_STATE_STREAM_OUT1_PDS_DATA_SIZE_UNIT_SIZE,
            cache_line_size, &r->pt_resume_up, &r->pt_resume_prog_bo);
         free(staging);
         if (vk != VK_SUCCESS)
            goto err_pt_store;
      }

      /* SR store/load PDS programs (DOUTU-kick the USC store/load blobs). */
      {
         struct pvr_pds_shared_storing_program program;
         uint32_t staging[PVRGL_PDS_TASK_PROGRAM_SIZE / 4U] = { 0 };
         uint32_t code_off;

         /* BXM-4-64 MC1: single core (the core_count>1 path is a
          * pvr_finishme upstream too). */
         pvrgl_ctx_sr_setup(usc_store_off, sr_store_pre->temps,
                            r->sr_store_load_bo.dev_addr, &program);
         pvr_pds_generate_shared_storing_program(
            &program, staging, PDS_GENERATE_DATA_SEGMENT, dev_info);
         code_off = ALIGN_POT(
            program.data_size,
            ROGUE_VDMCTRL_PDS_STATE1_PDS_DATA_ADDR_ALIGNMENT / 4U);
         pvr_pds_generate_shared_storing_program(
            &program, staging + code_off, PDS_GENERATE_CODE_SEGMENT, dev_info);

         vk = pvrgl_pds_prog_upload(
            screen, staging, program.data_size,
            ROGUE_VDMCTRL_PDS_STATE1_PDS_DATA_ADDR_ALIGNMENT,
            staging + code_off, program.code_size,
            ROGUE_VDMCTRL_PDS_STATE2_PDS_CODE_ADDR_ALIGNMENT,
            cache_line_size, &r->sr_store_up, &r->sr_store_prog_bo);
         if (vk != VK_SUCCESS)
            goto err_pt_resume;

         memset(staging, 0, sizeof(staging));
         pvrgl_ctx_sr_setup(usc_load_off, sr_load_pre->temps,
                            r->sr_store_load_bo.dev_addr, &program);
         pvr_pds_generate_shared_storing_program(
            &program, staging, PDS_GENERATE_DATA_SEGMENT, dev_info);
         code_off = ALIGN_POT(
            program.data_size,
            ROGUE_VDMCTRL_PDS_STATE1_PDS_DATA_ADDR_ALIGNMENT / 4U);
         pvr_pds_generate_shared_storing_program(
            &program, staging + code_off, PDS_GENERATE_CODE_SEGMENT, dev_info);

         vk = pvrgl_pds_prog_upload(
            screen, staging, program.data_size,
            ROGUE_VDMCTRL_PDS_STATE1_PDS_DATA_ADDR_ALIGNMENT,
            staging + code_off, program.code_size,
            ROGUE_VDMCTRL_PDS_STATE2_PDS_CODE_ADDR_ALIGNMENT,
            cache_line_size, &r->sr_load_up, &r->sr_load_prog_bo);
         if (vk != VK_SUCCESS)
            goto err_sr_store;
      }

      /* ---- Context priority + callstack address (must be set, not left
       * uninitialized — kernel rejects CREATE_CONTEXT with garbage). ---- */
      rctx_info.priority = 0;
      rctx_info.vdm_callstack_addr = PVR_DEV_ADDR(r->vdm_callstack_bo.dev_addr);

      /* ---- Fill the winsys static state (upstream
       * pvr_render_ctx_ws_static_state_init). ---- */
      {
         const uint8_t usc_unified_size =
            DIV_ROUND_UP(64, ROGUE_VDMCTRL_PDS_STATE0_USC_UNIFIED_SIZE_UNIT_SIZE);
         pvr_csb_pack (&rctx_info.static_state.rogue.vdm_ctx_state_base_addr,
                       CR_VDM_CONTEXT_STATE_BASE, base) {
            base.addr = PVR_DEV_ADDR(r->vdm_state_bo.dev_addr);
         }
         pvr_csb_pack (&rctx_info.static_state.rogue.geom_ctx_state_base_addr,
                       CR_TA_CONTEXT_STATE_BASE, base) {
            base.addr = PVR_DEV_ADDR(r->geom_state_bo.dev_addr);
         }

         for (uint32_t i = 0; i < 2; i++) {
            uint64_t *q = &rctx_info.static_state.rogue.geom_state[i].vdm_ctx_store_task0;
            uint32_t *d = &rctx_info.static_state.rogue.geom_state[i].vdm_ctx_store_task1;

            pvr_csb_pack (q, CR_VDM_CONTEXT_STORE_TASK0, task0) {
               pvrgl_vdmctrl_pds_state_words(&r->sr_store_up,
                                             ROGUE_VDMCTRL_USC_TARGET_ANY,
                                             usc_unified_size,
                                             &task0.pds_state0,
                                             &task0.pds_state1);
            }
            pvr_csb_pack (d, CR_VDM_CONTEXT_STORE_TASK1, task1) {
               pvr_csb_pack (&task1.pds_state2, VDMCTRL_PDS_STATE2, state) {
                  state.pds_code_addr =
                     PVR_DEV_ADDR(r->sr_store_up.code_offset);
               }
            }
            q = &rctx_info.static_state.rogue.geom_state[i].vdm_ctx_store_task2;
            pvr_csb_pack (q, CR_VDM_CONTEXT_STORE_TASK2, task2) {
               pvr_csb_pack (&task2.stream_out1, TA_STATE_STREAM_OUT1, so1) {
                  so1.sync = true;
                  so1.pds_data_size =
                     PVR_DW_TO_BYTES(r->pt_store_up.data_size) /
                     ROGUE_TA_STATE_STREAM_OUT1_PDS_DATA_SIZE_UNIT_SIZE;
                  so1.pds_temp_size = 0;
               }
               pvr_csb_pack (&task2.stream_out2, TA_STATE_STREAM_OUT2, so2) {
                  so2.pds_data_addr =
                     PVR_DEV_ADDR(r->pt_store_up.data_offset);
               }
            }

            q = &rctx_info.static_state.rogue.geom_state[i].vdm_ctx_resume_task0;
            pvr_csb_pack (q, CR_VDM_CONTEXT_RESUME_TASK0, task0) {
               pvrgl_vdmctrl_pds_state_words(&r->sr_load_up,
                                             ROGUE_VDMCTRL_USC_TARGET_ALL,
                                             usc_unified_size,
                                             &task0.pds_state0,
                                             &task0.pds_state1);
            }
            d = &rctx_info.static_state.rogue.geom_state[i].vdm_ctx_resume_task1;
            pvr_csb_pack (d, CR_VDM_CONTEXT_RESUME_TASK1, task1) {
               pvr_csb_pack (&task1.pds_state2, VDMCTRL_PDS_STATE2, state) {
                  state.pds_code_addr =
                     PVR_DEV_ADDR(r->sr_load_up.code_offset);
               }
            }
            q = &rctx_info.static_state.rogue.geom_state[i].vdm_ctx_resume_task2;
            pvr_csb_pack (q, CR_VDM_CONTEXT_RESUME_TASK2, task2) {
               pvr_csb_pack (&task2.stream_out1, TA_STATE_STREAM_OUT1, so1) {
                  so1.sync = true;
                  so1.pds_data_size =
                     PVR_DW_TO_BYTES(r->pt_resume_up.data_size) /
                     ROGUE_TA_STATE_STREAM_OUT1_PDS_DATA_SIZE_UNIT_SIZE;
                  so1.pds_temp_size = 0;
               }
               pvr_csb_pack (&task2.stream_out2, TA_STATE_STREAM_OUT2, so2) {
                  so2.pds_data_addr =
                     PVR_DEV_ADDR(r->pt_resume_up.data_offset);
               }
            }
         }
      }

      vk = screen->ws->ops->render_ctx_create(screen->ws, &rctx_info,
                                              dev_info, &r->rctx);
      if (vk != VK_SUCCESS)
         goto err_callstack;
   }

   /* ---- Aux BOs (size-independent). ---- */
   {
      uint32_t terminate;
      pvr_csb_pack (&terminate, VDMCTRL_STREAM_TERMINATE, x);
      vk = pvrgl_upload(screen, screen->heaps->general_heap, &terminate,
                        sizeof(terminate) + 16U, 16U, &r->ctrl_stream_bo);
      if (vk != VK_SUCCESS)
         goto err_rctx;

      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        4096U, cache_line_size, &r->border_colour_bo);
      if (vk != VK_SUCCESS)
         goto err_ctrl;

      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        64U, cache_line_size, &r->depth_bias_bo);
      if (vk != VK_SUCCESS)
         goto err_border;
   }

   mesa_logi("pvrgl: render init ok (ctx=%p)", (void *)r->rctx);

   /* BG-object clear chain — failure is non-fatal (stream falls back to
    * zero bgnd, current behavior) but log loudly. */
   vk = pvrgl_render_bg_clear_init(r);
   if (vk != VK_SUCCESS)
      mesa_logw("pvrgl: bg-clear init failed vk=%d (bgnd stays zero)", vk);
   else
      mesa_logi("pvrgl: bg-clear init ok");

   /* ORDER EXPERIMENT: create the dataset before first submit, matching
    * the pre-refactor init order (dataset existed at rctx-create time). */
   vk = pvrgl_render_dataset_init(r, PVRGL_RT_WIDTH, PVRGL_RT_HEIGHT);
   if (vk != VK_SUCCESS)
      goto err_bias;
   r->tgt_w = PVRGL_RT_WIDTH;
   r->tgt_h = PVRGL_RT_HEIGHT;

   *out = r;
   return VK_SUCCESS;

err_bias:
   pvrgl_bo_free(screen, &r->depth_bias_bo);
err_border:
   pvrgl_bo_free(screen, &r->border_colour_bo);
err_ctrl:
   pvrgl_bo_free(screen, &r->ctrl_stream_bo);
err_rctx:
   screen->ws->ops->render_ctx_destroy(r->rctx);
err_sr_store:
   pvrgl_bo_free(screen, &r->sr_store_prog_bo);
err_pt_resume:
   pvrgl_bo_free(screen, &r->pt_resume_prog_bo);
err_pt_store:
   pvrgl_bo_free(screen, &r->pt_store_prog_bo);
err_pt_state:
   pvrgl_bo_free(screen, &r->pt_store_resume_bo);
err_sr_state:
   pvrgl_bo_free(screen, &r->sr_store_load_bo);
err_usc_load:
   pvrgl_bo_free(screen, &r->usc_load_bo);
err_usc_store:
   pvrgl_bo_free(screen, &r->usc_store_bo);
err_geom_state:
   pvrgl_bo_free(screen, &r->geom_state_bo);
err_vdm_state:
   pvrgl_bo_free(screen, &r->vdm_state_bo);
err_callstack:
   pvrgl_bo_free(screen, &r->vdm_callstack_bo);
err_vheap:
   pvrgl_bo_free(screen, &r->vheap_rtc_bo);
err_local_fl:
   screen->ws->ops->free_list_destroy(r->local_fl);
   pvrgl_bo_free(screen, &r->local_fl_bo);
err_global_fl:
   screen->ws->ops->free_list_destroy(r->global_fl);
   pvrgl_bo_free(screen, &r->global_fl_bo);
err_free:
   free(r);
   return vk;
}

void
pvrgl_render_fini(struct pvrgl_render *r)
{
   struct pvrgl_screen *screen = r->screen;

   pvrgl_bo_free(screen, &r->bg_const_bo);
   pvrgl_bo_free(screen, &r->bg_pds_tex_bo);
   pvrgl_bo_free(screen, &r->bg_pds_unitex_bo);
   pvrgl_bo_free(screen, &r->bg_pds_frag_bo);
   pvrgl_bo_free(screen, &r->bg_usc_bo);
   pvrgl_bo_free(screen, &r->event_pds_bo);
   pvrgl_bo_free(screen, &r->depth_bias_bo);
   pvrgl_bo_free(screen, &r->scissor_bo);
   pvrgl_bo_free(screen, &r->border_colour_bo);
   pvrgl_bo_free(screen, &r->ctrl_stream_bo);
   pvrgl_bo_free(screen, &r->sr_load_prog_bo);
   pvrgl_bo_free(screen, &r->sr_store_prog_bo);
   pvrgl_bo_free(screen, &r->pt_resume_prog_bo);
   pvrgl_bo_free(screen, &r->pt_store_prog_bo);
   pvrgl_bo_free(screen, &r->pt_store_resume_bo);
   pvrgl_bo_free(screen, &r->sr_store_load_bo);
   pvrgl_bo_free(screen, &r->usc_load_bo);
   pvrgl_bo_free(screen, &r->usc_store_bo);
   pvrgl_bo_free(screen, &r->geom_state_bo);
   pvrgl_bo_free(screen, &r->vdm_state_bo);
   screen->ws->ops->render_ctx_destroy(r->rctx);
   pvrgl_bo_free(screen, &r->vdm_callstack_bo);
   if (r->rt_dataset)
      screen->ws->ops->render_target_dataset_destroy(r->rt_dataset);
   pvrgl_bo_free(screen, &r->rgn_hdr_bo);
   pvrgl_bo_free(screen, &r->mlist_bo);
   pvrgl_bo_free(screen, &r->tpc_bo);
   pvrgl_bo_free(screen, &r->vheap_rtc_bo);
   screen->ws->ops->free_list_destroy(r->local_fl);
   pvrgl_bo_free(screen, &r->local_fl_bo);
   screen->ws->ops->free_list_destroy(r->global_fl);
   pvrgl_bo_free(screen, &r->global_fl_bo);
   free(r);
}

/* ---- Render submit (geometry + fragment jobs). ---- */

static void
pvrgl_geom_stream_init(struct pvrgl_render *r,
                       struct pvr_winsys_geometry_state *state)
{
   const struct pvr_device_info *dev_info = r->screen->dev_info;
   uint32_t *stream_ptr = (uint32_t *)state->fw_stream;
   uint32_t *stream_len_ptr = stream_ptr;

   stream_ptr += pvr_cmd_length(KMD_STREAM_HDR);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_VDM_CTRL_STREAM_BASE, value) {
      value.addr = PVR_DEV_ADDR(r->ctrl_stream_bo.dev_addr);
   }
   stream_ptr += pvr_cmd_length(CR_VDM_CTRL_STREAM_BASE);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_TPU_BORDER_COLOUR_TABLE_VDM,
                 value) {
      value.border_colour_table_address =
         PVR_DEV_ADDR(r->border_colour_bo.dev_addr);
   }
   stream_ptr += pvr_cmd_length(CR_TPU_BORDER_COLOUR_TABLE_VDM);

   pvr_csb_pack (stream_ptr, CR_PPP_CTRL, value) {
      value.wclampen = true;
      value.fixed_point_format = 1;
   }
   stream_ptr += pvr_cmd_length(CR_PPP_CTRL);

   pvr_csb_pack (stream_ptr, CR_TE_PSG, value) {
      value.completeonterminate = true;
      value.region_stride =
         r->rgn_headers_stride / ROGUE_CR_TE_PSG_REGION_STRIDE_UNIT_SIZE;
      value.forcenewstate = false;
   }
   stream_ptr += pvr_cmd_length(CR_TE_PSG);

   pvr_csb_pack (stream_ptr, VDMCTRL_PDS_STATE0, value) {
      value.usc_common_size = 0;
   }
   stream_ptr += pvr_cmd_length(VDMCTRL_PDS_STATE0);

   pvr_csb_pack (stream_ptr, KMD_STREAM_VIEW_IDX, value) {
      value.idx = 0;
   }
   stream_ptr += pvr_cmd_length(KMD_STREAM_VIEW_IDX);

   state->fw_stream_len = (uint8_t *)stream_ptr - (uint8_t *)state->fw_stream;
   assert(state->fw_stream_len <= ARRAY_SIZE(state->fw_stream));

   pvr_csb_pack ((uint64_t *)stream_len_ptr, KMD_STREAM_HDR, value) {
      value.length = state->fw_stream_len;
   }

   (void)dev_info;
   mesa_logi("pvrgl: geom stream len=%u", state->fw_stream_len);
}

static void
pvrgl_frag_stream_init(struct pvrgl_render *r,
                       struct pvr_winsys_fragment_state *state,
                       const struct pvrgl_bo *rt_bo,
                       VkFormat rt_format,
                       uint32_t width, uint32_t height,
                       uint32_t clear_dword)
{
   const struct pvr_device_info *dev_info = r->screen->dev_info;
   /* BXM-4-64 MC1: the kernel's own feature query reports
    * gpu_multicore_support=1 (PVRDBG frag_state mc=1, 2026-08-31). The
    * kernel frag-stream defs (pvr_stream_defs.c) gate isp_oclqry_stride
    * and execute_count on PVR_FEATURE_GPU_MULTICORE_SUPPORT, so they MUST
    * be emitted or pvr_stream_process bounds-checks the stream short ->
    * EINVAL (J11, instrumented-module proof). The 2026-08-27 note
    * claiming kernel-truth multicore=false was drawn from the TQ
    * defs (transfer stream has no such fields) and is superseded. */
   const bool multicore = true;
   uint32_t isp_tiles_in_flight = 0;
   uint32_t code_off = 0;
   uint32_t usc_pixel_output_ctrl = 0;
   uint32_t event_data_size = 0;
   VkResult vk_frag;
   struct pvr_pbe_surf_params surf_params;
   struct pvr_pbe_render_params render_params;
   uint32_t pbe_words[ROGUE_NUM_PBESTATE_STATE_WORDS];
   uint32_t *stream_ptr = (uint32_t *)state->fw_stream;
   uint32_t *stream_len_ptr = stream_ptr;

   stream_ptr += pvr_cmd_length(KMD_STREAM_HDR);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_ISP_SCISSOR_BASE, value) {
      value.addr = PVR_DEV_ADDR(r->scissor_bo.dev_addr);
   }
   stream_ptr += pvr_cmd_length(CR_ISP_SCISSOR_BASE);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_ISP_DBIAS_BASE, value) {
      value.addr = PVR_DEV_ADDR(r->depth_bias_bo.dev_addr);
   }
   stream_ptr += pvr_cmd_length(CR_ISP_DBIAS_BASE);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_ISP_OCLQRY_BASE, value) {
      value.addr = PVR_DEV_ADDR_INVALID;
   }
   stream_ptr += pvr_cmd_length(CR_ISP_OCLQRY_BASE);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_ISP_ZLSCTL, value) {
      value.zloadformat = ROGUE_CR_ZLS_FORMAT_TYPE_F32Z;
      value.zstoreformat = ROGUE_CR_ZLS_FORMAT_TYPE_F32Z;
      value.forcezload = false;
      value.forcezstore = false;
      value.zonlyrender = false;
   }
   stream_ptr += pvr_cmd_length(CR_ISP_ZLSCTL);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_ISP_ZLOAD_BASE, value);
   stream_ptr += pvr_cmd_length(CR_ISP_ZLOAD_BASE);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_ISP_STENCIL_LOAD_BASE, value);
   stream_ptr += pvr_cmd_length(CR_ISP_STENCIL_LOAD_BASE);

   /* ---- PBE words [ref pvr_arch_job_common.c pvr_arch_pbe_pack_state]. */
   memset(&surf_params, 0, sizeof(surf_params));
   memset(&render_params, 0, sizeof(render_params));
   {
      /* pvr_get_format_swizzle() is not in the pvrgl link set; B8G8R8A8 ==
       * {Z,Y,X,W} = {2,1,0,3} (verified against upstream in M2). */
      surf_params.swizzle[0] = 2; /* B <- source Z */
      surf_params.swizzle[1] = 1; /* G <- source Y */
      surf_params.swizzle[2] = 0; /* R <- source X */
      surf_params.swizzle[3] = 3; /* A <- source W */

      surf_params.is_normalized =
         pvr_vk_format_is_fully_normalized(rt_format);
      surf_params.nr_components = 4U;

      pvr_arch_pbe_get_src_format_and_gamma(
         rt_format, PVR_PBE_GAMMA_NONE, false,
         &surf_params.source_format, &surf_params.gamma);
      surf_params.source_format =
         ROGUE_PBESTATE_SOURCE_FORMAT_8_PER_CHANNEL;
      surf_params.pbe_packmode = pvr_arch_get_pbe_packmode(rt_format);

      surf_params.addr.addr = rt_bo->dev_addr;
      surf_params.mem_layout = PVR_MEMLAYOUT_LINEAR;
      surf_params.stride = width * 4U;
      surf_params.depth = 1U;
      surf_params.width = width;
      surf_params.height = height;
      surf_params.z_only_render = false;
      surf_params.down_scale = false;

      memset(&render_params, 0, sizeof(render_params));
      render_params.min_x_clip = 0U;
      render_params.min_y_clip = 0U;
      render_params.max_x_clip = width - 1U;
      render_params.max_y_clip = height - 1U;
      render_params.source_start = PVR_PBE_STARTPOS_BIT0;
      render_params.slice = 0U;
      render_params.mrt_index = 0U;

      /* Zero the full 192B pbe region first (pack_state only writes 3 u64s). */
      memset(stream_ptr, 0,
             PVR_MAX_COLOR_ATTACHMENTS * ROGUE_NUM_PBESTATE_REG_WORDS *
                DWORDS_PER_U64 * sizeof(uint32_t));

      pvr_arch_pbe_pack_state(dev_info, &surf_params, &render_params,
                              pbe_words, (uint64_t *)stream_ptr);

      /* Kernel expects the FULL pbe_word[8][3] array (192B) — PVR_STREAM_DEF_ARRAY
       * consumes sizeof(regs.pbe_word). Upstream memcpys job->pbe_reg_words
       * (8 x ROGUE_NUM_PBESTATE_REG_WORDS x u64), MRT0 packed, others zero.
       * Without the full array the kernel stream parse runs out of data -> EINVAL.
       * Verified 2026-08-27 (submit dump + kernel pvr_stream_defs.c). */
      stream_ptr += PVR_MAX_COLOR_ATTACHMENTS * ROGUE_NUM_PBESTATE_REG_WORDS *
                    DWORDS_PER_U64;
   }

   /* ---- Pixel-event PDS program (EOT kicker) [TQ-path port, proven
    * 2026-08-24 with real TQ pixels; ref pvr_arch_cmd_buffer.c]. At tile
    * end the FW runs this PDS program: it emits the PBE state words into
    * USC shared registers (usc_sr_size dwords) and DOUTUs the USC EOT
    * program (shared_words=true -> EOT reads those SRs). With
    * const_size=0 / EVENT_PIXEL_PDS_DATA=0 the FW executes nothing and
    * the EOT never fires -> RT stays zero (the render-submit-passed-
    * no-pixels symptom). The emit words are THIS submit's pbe_words. */
   {
      struct pvr_pds_event_program event_program;
      struct pvrgl_tq *tq = r->screen->tq_priv;
      const struct pvrgl_bo *eot_bo = pvrgl_tq_eot_bo(tq, 0);
      const uint32_t eot_temps = pvrgl_tq_eot_temps(tq, 0);
      uint32_t *staging;
      VkResult vk_frag;

      if (!eot_bo) {
         mesa_logw("pvrgl: render EVPDS no EOT program (TQ not ready)");
      } else {
         mesa_logi("pvrgl: render EVPDS eot_bo dev=%llx heap=%llx event_pd dev=%llx heap=%llx temps=%u",
                    (unsigned long long)eot_bo->dev_addr,
                    (unsigned long long)eot_bo->heap_offset,
                    (unsigned long long)r->event_pds_bo.dev_addr,
                    (unsigned long long)r->event_pds_bo.heap_offset,
                    eot_temps);

         /* Allocate the event_pds_bo FIRST so we know its dev_addr.
          * pvr_pds_setup_doutu must be called with the event_pds_bo's
          * dev_addr + code_off as the DOUTU execution_address, NOT
          * eot_bo->heap_offset. The TQ EOT BO's heap_offset (0x1000)
          * is the wrong address — the DOUTU must execute the EOT PDS
          * program from the event_pds_bo code segment. */
         {
            if (r->event_pds_bo.bo)
               pvrgl_bo_free(r->screen, &r->event_pds_bo);

            const uint32_t est_size = 64; /* upper bound for EOT program */
            vk_frag = pvrgl_upload(r->screen,
                                   r->screen->heaps->pds_heap,
                                   NULL, est_size, 16, &r->event_pds_bo);
            if (vk_frag != VK_SUCCESS) {
               mesa_logw("pvrgl: render EVPDS alloc failed %d (EOT dead)", vk_frag);
            } else {
               /* Set up sizes FIRST to get data_size/code_size,
                * then calculate code_off, THEN set up DOUTU with
                * the correct code-segment execution address. */
               memset(&event_program, 0, sizeof(event_program));
               event_program.emit_words = pbe_words;
               event_program.num_emit_word_pairs = 1U;

               /* Sizes must come BEFORE pvr_pds_setup_doutu so we
                * can calculate code_off for the execution address. */
               pvr_pds_set_sizes_pixel_event(&event_program, dev_info);
               event_data_size = event_program.data_size;

               code_off = ALIGN_POT(event_program.data_size * 4,
                                      ROGUE_CR_EVENT_PIXEL_PDS_CODE_ADDR_ALIGNMENT);

               /* DOUTU execution_address = the USC EOT program (on the USC
                * heap), NOT the pixel-event PDS program's code segment.
                * The DOUTU kicks the USC; the USC expects a USC program,
                * so pointing it at PDS code makes the USC execute garbage
                * -> zero RT pixels (the render-path "submit accepted, no
                * pixels" symptom). The TQ path uses eot_bo->heap_offset
                * for exactly this field and paints real pixels; the render
                * path must match. CR_EVENT_PIXEL_PDS_DATA/CODE are separate
                * fields (below) and DO take heap-relative PDS offsets — do
                * not conflate the two. */
               pvr_pds_setup_doutu(&event_program.task_control,
                                     eot_bo->heap_offset,
                                     eot_temps,
                                     ROGUE_PDSINST_DOUTU_SAMPLE_RATE_INSTANCE,
                                     false);

               staging = calloc(event_program.code_size + event_program.data_size, 4);
               if (staging) {
                  pvr_pds_generate_pixel_event_data_segment(&event_program, staging, dev_info);
                  pvr_pds_generate_pixel_event_code_segment(
                     &event_program, staging + event_program.data_size, dev_info);

                  /* Copy data+code into the already-allocated BO */
                  memcpy((uint8_t *)r->event_pds_bo.bo->map,
                         staging,
                         event_program.data_size * 4);
                  memcpy((uint8_t *)r->event_pds_bo.bo->map + code_off,
                         staging + event_program.data_size * 4,
                         event_program.code_size * 4);

                  mesa_logi("pvrgl: render EVPDS fixed dev_addr=%llx+0x%x dsize=%u csize=%u code_off=0x%x emit_pairs=%u",
                             (unsigned long long)r->event_pds_bo.dev_addr, code_off,
                             event_program.data_size, event_program.code_size,
                             code_off, event_program.num_emit_word_pairs);
               } else {
                  mesa_logw("pvrgl: render EVPDS staging alloc failed (EOT dead)");
               }
               free(staging);
            }
         }
      }
   }

   /* Tiles-in-flight + USC_PIXEL_OUTPUT_CTRL [upstream pvr_arch_job_render.c
    * :928 — pixel_ctl feeds CR_USC_PIXEL_OUTPUT_CTRL, tiles bits OR into
    * CR_ISP_CTL]. Our previous zero here starved the USC SR allocation
    * signal alongside the dead event program. */
   pvr_arch_setup_tiles_in_flight(dev_info,
                                  r->screen->runtime_info,
                                  ROGUE_CR_ISP_AA_MODE_TYPE_AA_NONE,
                                  1U /* usc_pixel_width: 1 out reg/pixel */,
                                  false,
                                  0,
                                  &isp_tiles_in_flight,
                                  &usc_pixel_output_ctrl);

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_TPU_BORDER_COLOUR_TABLE_PDM,
                 value) {
      value.border_colour_table_address =
         PVR_DEV_ADDR(r->border_colour_bo.dev_addr);
   }
   stream_ptr += pvr_cmd_length(CR_TPU_BORDER_COLOUR_TABLE_PDM);

   /* CR_PDS_BGRND0/1/3: bg-object clear (load-op) program pointers —
    * built once in pvrgl_render_bg_clear_init(). 3 x u64. Zeros here =
    * no bgnd program -> ISP never runs the bg task -> empty tiles stay
    * unwritten regardless of process_empty_tiles. */
   if (r->bg_pds_frag_bo.bo) {
      memcpy(stream_ptr, r->bgnd_reg_values, sizeof(r->bgnd_reg_values));
   } else {
      memset(stream_ptr, 0, 3U * DWORDS_PER_U64 * sizeof(uint32_t));
   }
   stream_ptr += 3U * DWORDS_PER_U64;
   /* PR bgnd: same values (upstream fills both for load-op clears). */
   if (r->bg_pds_frag_bo.bo) {
      memcpy(stream_ptr, r->bgnd_reg_values, sizeof(r->bgnd_reg_values));
   } else {
      memset(stream_ptr, 0, 3U * DWORDS_PER_U64 * sizeof(uint32_t));
   }
   stream_ptr += 3U * DWORDS_PER_U64;

   /* USC clear registers: kernel expects the FULL
    * usc_clear_register[ROGUE_MAXIMUM_OUTPUT_REGISTERS_PER_PIXEL=8] array
    * (8 x u32 = 32B) — PVR_STREAM_DEF_ARRAY consumes sizeof(regs.usc_clear_register).
    * kmd_stream.xml: usc_clear_register size=256 bits. pvrgl emitted only 4
    * (16B) -> kernel stream parse ran out of data -> EINVAL. Reg0 carries the
    * clear color (0xFF0000FF = opaque red in B8G8R8A8 dword packing); a
    * working pipeline must paint non-zero pixels, zero regs would make a
    * live pipeline indistinguishable from a dead one. */
   {
      uint32_t i;
      for (i = 0; i < 8U; i++) {
         pvr_csb_pack (stream_ptr, CR_USC_CLEAR_REGISTER, reg) {
            reg.val = (i == 0U) ? clear_dword : 0;
         }
         stream_ptr += pvr_cmd_length(CR_USC_CLEAR_REGISTER);
      }
   }

   pvr_csb_pack (stream_ptr, CR_USC_PIXEL_OUTPUT_CTRL, reg) {
      (void)reg;
   }
   *stream_ptr = usc_pixel_output_ctrl;
   stream_ptr += pvr_cmd_length(CR_USC_PIXEL_OUTPUT_CTRL);

   pvr_csb_pack (stream_ptr, CR_ISP_BGOBJDEPTH, value) {
      value.value = 0;
   }
   stream_ptr += pvr_cmd_length(CR_ISP_BGOBJDEPTH);

   pvr_csb_pack (stream_ptr, CR_ISP_BGOBJVALS, value) {
      /* Upstream full-clear: enable_bg_tag = !!color_init_count (true when
       * there are color clears) [pvr_arch_cmd_buffer.c:3433]. */
      value.enablebgtag = true;
      value.mask = true;
      value.stencil = 0;
   }
   stream_ptr += pvr_cmd_length(CR_ISP_BGOBJVALS);

   pvr_csb_pack (stream_ptr, CR_ISP_AA, value) {
      value.mode = ROGUE_CR_ISP_AA_MODE_TYPE_AA_NONE;
   }
   stream_ptr += pvr_cmd_length(CR_ISP_AA);

   pvr_csb_pack (stream_ptr, CR_ISP_CTL, value) {
      value.sample_pos = true;
      /* Clear-with-no-geometry: upstream sets process_empty_tiles=true for
       * clear sub-commands (pvr_arch_cmd_buffer.c:1698). With zero prims,
       * false makes the ISP skip every tile -> EOT never writes -> zero RT. */
      value.process_empty_tiles = true;
      if (multicore)
         value.skip_init_hdrs = true;
   }
   /* Tiles-in-flight bits live in CR_ISP_CTL [TQ-path pattern]. */
   *stream_ptr |= isp_tiles_in_flight;
   stream_ptr += pvr_cmd_length(CR_ISP_CTL);

   pvr_csb_pack (stream_ptr, CR_EVENT_PIXEL_PDS_INFO, value) {
      value.temp_stride = 0;
      value.const_size =
         DIV_ROUND_UP(event_data_size,
                      ROGUE_CR_EVENT_PIXEL_PDS_INFO_CONST_SIZE_UNIT_SIZE);
      value.usc_sr_size =
         DIV_ROUND_UP(1U * PVR_STATE_PBE_DWORDS,
                      ROGUE_CR_EVENT_PIXEL_PDS_INFO_USC_SR_SIZE_UNIT_SIZE);
   }
   stream_ptr += pvr_cmd_length(CR_EVENT_PIXEL_PDS_INFO);

   pvr_csb_pack (stream_ptr, KMD_STREAM_VIEW_IDX, value) {
      value.idx = 0;
   }
   stream_ptr += pvr_cmd_length(KMD_STREAM_VIEW_IDX);

   pvr_csb_pack (stream_ptr, CR_EVENT_PIXEL_PDS_DATA, value) {
      /* PDS task data addr is a 28-bit heap offset (shift=4),
       * NOT the full device address — same as the TQ path.
       * Passing dev_addr truncated to garbage causes FW jump fault. */
      value.addr = PVR_DEV_ADDR(r->event_pds_bo.heap_offset);
   }
   stream_ptr += pvr_cmd_length(CR_EVENT_PIXEL_PDS_DATA);

   pvr_csb_pack (stream_ptr, CR_EVENT_PIXEL_PDS_CODE, value) {
      /* Code segment addr is a 28-bit heap offset (shift=4).
       * code_off is the byte offset of the code segment within the BO. */
      value.addr = PVR_DEV_ADDR(r->event_pds_bo.heap_offset + code_off);
   }
   stream_ptr += pvr_cmd_length(CR_EVENT_PIXEL_PDS_CODE);

   if (multicore) {
      *stream_ptr = 0; /* isp_oclqry_stride */
      stream_ptr++;
   }

   *stream_ptr = 0; /* zls_stride */
   stream_ptr++;
   *stream_ptr = 0; /* sls_stride */
   stream_ptr++;

   if (multicore) {
      *stream_ptr = 0; /* execute_count */
      stream_ptr++;
   }

   state->fw_stream_len = (uint8_t *)stream_ptr - (uint8_t *)state->fw_stream;
   assert(state->fw_stream_len <= ARRAY_SIZE(state->fw_stream));

   pvr_csb_pack ((uint64_t *)stream_len_ptr, KMD_STREAM_HDR, value) {
      value.length = state->fw_stream_len;
   }

   mesa_logi("pvrgl: frag stream len=%u multicore=%d",
             state->fw_stream_len, multicore ? 1 : 0);
}

VkResult
pvrgl_render_submit(struct pvrgl_render *r,
                    const struct pvrgl_bo *rt_bo,
                    VkFormat rt_format,
                    uint32_t width, uint32_t height,
                    uint32_t clear_dword)
{
   struct pvr_winsys_render_submit_info submit_info;
   VkResult vk;

   vk = pvrgl_render_bind_target(r, width, height);
   if (vk != VK_SUCCESS)
      return vk;

   /* Update the bgnd clear-color const BO — the FW's PDS DOUTD program
    * re-reads it at every fragment-job kickoff. */
   if (r->bg_const_bo.bo && r->bg_const_bo.bo->map)
      memcpy(r->bg_const_bo.bo->map, &clear_dword, sizeof(clear_dword));

   memset(&submit_info, 0, sizeof(submit_info));
   submit_info.rt_dataset = r->rt_dataset;
   submit_info.rt_data_idx = 0;
   submit_info.frame_num = 0;
   submit_info.job_num = 0;
   submit_info.has_fragment_job = true;

   submit_info.geometry.flags.is_first_geometry = true;
   submit_info.geometry.flags.is_last_geometry = true;
   submit_info.geometry.flags.use_single_core = false;
   submit_info.geometry.wait = NULL;

   submit_info.fragment.flags.has_depth_buffer = false;
   submit_info.fragment.flags.has_stencil_buffer = false;
   submit_info.fragment.wait = NULL;
   submit_info.fragment_pr.wait = NULL;

   pvrgl_geom_stream_init(r, &submit_info.geometry);
   pvrgl_frag_stream_init(r, &submit_info.fragment, rt_bo, rt_format,
                          width, height, clear_dword);

   /* The winsys always submits a partial-render (PR) fragment job from
    * fragment_pr — give it a valid copy of the fragment stream (with no
    * geometry-generated PRs it simply performs nothing). */
   submit_info.fragment_pr = submit_info.fragment;
   submit_info.fragment_pr.wait = NULL;

   vk = r->screen->ws->ops->render_submit(
      r->rctx, &submit_info, r->screen->dev_info, NULL, NULL);
   if (vk != VK_SUCCESS)
      mesa_logw("pvrgl: render_submit failed %d", vk);
   else
      mesa_logi("pvrgl: render_submit ok");

   return vk;
}

/* Env-guarded self test (PVRGL_RENDER_TEST=1): init render infra, allocate a
 * render-target BO, submit an empty-geometry job pair, tear down. */
VkResult
pvrgl_render_selftest(struct pvrgl_screen *screen)
{
   struct pvrgl_render *r;
   struct pvrgl_bo rt_bo;
   VkResult vk;

   vk = pvrgl_render_init(screen, &r);
   if (vk != VK_SUCCESS)
      return vk;

   vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                     PVRGL_RT_WIDTH * PVRGL_RT_HEIGHT * 4U, 4096U, &rt_bo);
   if (vk != VK_SUCCESS)
      goto out_fini;

   vk = pvrgl_render_submit(r, &rt_bo, VK_FORMAT_B8G8R8A8_UNORM,
                            PVRGL_RT_WIDTH, PVRGL_RT_HEIGHT, 0xFF0000FFu);
   if (vk == VK_SUCCESS) {
      /* Pixel verdict: the FW executes asynchronously — poll the RT map
       * for the first non-zero dword for up to 2s, then report position
       * and value. All-zero after the window = EOT/PBE still dead. */
      volatile const uint32_t *pix = (volatile const uint32_t *)rt_bo.bo->map;
      const size_t n = (size_t)PVRGL_RT_WIDTH * PVRGL_RT_HEIGHT;
      unsigned spin;
      bool nonzero = false;

      for (spin = 0; spin < 200 && !nonzero; spin++) {
         for (size_t i = 0; i < n; i++) {
            if (pix[i]) {
               mesa_logi("pvrgl: RENDER PIXELS %08x at (%zu,%zu) off=%zu",
                         pix[i], i % PVRGL_RT_WIDTH, i / PVRGL_RT_WIDTH, i);
               nonzero = true;
               break;
            }
         }
         if (!nonzero)
            usleep(10000);
      }
      if (!nonzero)
         mesa_logw("pvrgl: RENDER PIXELS all zero after 2s");
   }

   pvrgl_bo_free(screen, &rt_bo);
out_fini:
   pvrgl_render_fini(r);
   return vk;
}

/* ---- Production clear entry (called from pvrgl_clear.c). ---- */

#define PVRGL_CLEAR_WIDTH_MAX  16384u
#define PVRGL_CLEAR_HEIGHT_MAX 16384u

static uint8_t
pvrgl_u8fix(float v)
{
   float c = v < 0.0f ? 0.0f : (v > 1.0f ? 1.0f : v);
   return (uint8_t)(c * 255.0f + 0.5f);
}

/* Pack RGBA-float clear color into the accum-format dword the bgnd USC
 * const + usc_clear_register0 expect [ref pvr_pack_clear_color,
 * U8U8U8U8 normalized branch]. */
static VkResult
pvrgl_pack_clear_dword(enum pipe_format fmt, const float f[4],
                       uint32_t *out)
{
   switch (fmt) {
   case PIPE_FORMAT_BGRA8888_UNORM:
   case PIPE_FORMAT_B8G8R8X8_UNORM:
      /* accum order B,G,R,A */
      *out = (uint32_t)pvrgl_u8fix(f[2]) |
             ((uint32_t)pvrgl_u8fix(f[1]) << 8) |
             ((uint32_t)pvrgl_u8fix(f[0]) << 16) |
             ((uint32_t)pvrgl_u8fix(f[3]) << 24);
      return VK_SUCCESS;
   case PIPE_FORMAT_RGBA8888_UNORM:
   case PIPE_FORMAT_R8G8B8X8_UNORM:
      *out = (uint32_t)pvrgl_u8fix(f[0]) |
             ((uint32_t)pvrgl_u8fix(f[1]) << 8) |
             ((uint32_t)pvrgl_u8fix(f[2]) << 16) |
             ((uint32_t)pvrgl_u8fix(f[3]) << 24);
      return VK_SUCCESS;
   default:
      return VK_ERROR_FORMAT_NOT_SUPPORTED;
   }
}

VkResult
pvrgl_render_clear(struct pvrgl_screen *screen, struct pipe_resource *res,
                   const float color[4])
{
   struct pvrgl_resource *pres = pvrgl_resource(res);
   struct pvrgl_bo tmp;
   VkFormat vkf;
   uint32_t clear_dword;
   VkResult vk;

   if (!pres || !pres->bo)
      return VK_ERROR_INVALID_DEVICE_ADDRESS_EXT;

   switch (res->format) {
   case PIPE_FORMAT_BGRA8888_UNORM:
   case PIPE_FORMAT_B8G8R8X8_UNORM:
      vkf = VK_FORMAT_B8G8R8A8_UNORM;
      break;
   case PIPE_FORMAT_RGBA8888_UNORM:
   case PIPE_FORMAT_R8G8B8X8_UNORM:
      vkf = VK_FORMAT_R8G8B8A8_UNORM;
      break;
   default:
      return VK_ERROR_FORMAT_NOT_SUPPORTED;
   }

   vk = pvrgl_pack_clear_dword(res->format, color, &clear_dword);
   if (vk != VK_SUCCESS)
      return vk;

   if (res->width0 == 0 || res->height0 == 0 ||
       res->width0 > PVRGL_CLEAR_WIDTH_MAX ||
       res->height0 > PVRGL_CLEAR_HEIGHT_MAX)
      return VK_ERROR_INVALID_DEVICE_ADDRESS_EXT;

   if (!screen->render_priv) {
      vk = pvrgl_render_init(screen, &screen->render_priv);
      if (vk != VK_SUCCESS) {
         screen->render_priv = NULL;
         return vk;
      }
   }

   /* Adapt the resource's BO into a pvrgl_bo view (heap_offset is only
    * needed for uploads; the frag stream uses dev_addr). */
   memset(&tmp, 0, sizeof(tmp));
   tmp.bo = pres->bo;
   tmp.vma = pres->vma;
   tmp.dev_addr = pres->dev_addr;

   return pvrgl_render_submit(screen->render_priv, &tmp, vkf,
                              res->width0, res->height0, clear_dword);
}
