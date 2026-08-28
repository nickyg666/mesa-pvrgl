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

#include "hwdef/rogue_hw_defs.h"
#include "hwdef/rogue_hw_utils.h"
#include "pvr_csb.h"
#include "pvr_csb_enum_helpers.h"
#include "pvr_device_info.h"
#include "pvr_formats.h"
#include "pvr_job_common.h"
#include "pvr_job_render.h"
#include "pvr_winsys.h"
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
   struct pvrgl_bo scissor_bo;        /* one full-RT IPF scissor entry. */
   struct pvrgl_bo depth_bias_bo;     /* one zeroed entry. */
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

VkResult
pvrgl_render_init(struct pvrgl_screen *screen, struct pvrgl_render **out)
{
   const struct pvr_device_info *dev_info = screen->dev_info;
   const struct pvr_device_runtime_info *runtime_info = screen->runtime_info;
   struct pvr_winsys_rt_dataset_create_info create_info;
   struct pvrgl_render *r;
   struct pvr_rt_mtile_info mtile;
   uint32_t tile_size_x, tile_size_y;
   uint32_t mtiles_x, mtiles_y;
   uint32_t num_tiles_x, num_tiles_y;
   uint32_t num_mtiles_x, num_mtiles_y;
   uint32_t max_num_mtiles;
   uint32_t cache_line_size;
   uint64_t vheap_size;
   uint64_t tpc_size;
   uint64_t rgn_headers_size;
   uint32_t single_rgn_header_size;
   uint32_t version;
   uint32_t group_size;
   VkResult vk;

   r = calloc(1, sizeof(*r));
   if (!r)
      return VK_ERROR_OUT_OF_HOST_MEMORY;
   r->screen = screen;

   /* ---- Macrotile info [ref pvr_arch_rt_mtile_info_init]. ---- */
   tile_size_x = PVR_GET_FEATURE_VALUE(dev_info, tile_size_x, 16U);
   tile_size_y = PVR_GET_FEATURE_VALUE(dev_info, tile_size_y, 16U);
   num_tiles_x = DIV_ROUND_UP(PVRGL_RT_WIDTH, tile_size_x);
   num_tiles_y = DIV_ROUND_UP(PVRGL_RT_HEIGHT, tile_size_y);

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
      mesa_logi("pvrgl: render init step global_fl vk=%d", vk);
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
      /* Kernel requires page counts aligned to FREE_LIST_ALIGNMENT (4 pages);
       * mesa aligns the byte size to the SLC-based size alignment (64KB)
       * before converting to pages. */
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
      mesa_logi("pvrgl: render init step local_fl vk=%d", vk);
      if (vk != VK_SUCCESS) {
         pvrgl_bo_free(screen, &fl_bo);
         goto err_global_fl;
      }
      r->local_fl_bo = fl_bo;
   }

   cache_line_size = pvr_get_slc_cache_line_size(dev_info);

   /* ---- VHEAP + RTC BO. ---- */
   vheap_size = ROGUE_CR_PM_VHEAP_TABLE_SIZE * ROGUE_PM_VHEAP_ENTRY_SIZE;
   {
      uint64_t align =
         MAX2(ROGUE_CR_PM_VHEAP_TABLE_BASE_ADDR_ALIGNMENT,
              ROGUE_CR_TA_RTC_ADDR_BASE_ALIGNMENT);
      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        vheap_size, align, &r->vheap_rtc_bo);
      if (vk != VK_SUCCESS)
         goto err_local_fl;
   }

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
      goto err_vheap;

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
   create_info.width = PVRGL_RT_WIDTH;
   create_info.height = PVRGL_RT_HEIGHT;
   create_info.samples = PVRGL_RT_SAMPLES;
   create_info.layers = PVRGL_RT_LAYERS;

   if (PVR_HAS_ENHANCEMENT(dev_info, 42307)) {
      float value;
      value = ROGUE_ISP_MERGE_LOWER_LIMIT_NUMERATOR / (float)PVRGL_RT_WIDTH;
      create_info.isp_merge_lower_x = fui(value);
      value = ROGUE_ISP_MERGE_UPPER_LIMIT_NUMERATOR / (float)PVRGL_RT_WIDTH;
      create_info.isp_merge_upper_x = fui(value);
      value = ROGUE_ISP_MERGE_LOWER_LIMIT_NUMERATOR / (float)PVRGL_RT_HEIGHT;
      create_info.isp_merge_lower_y = fui(value);
      value = ROGUE_ISP_MERGE_UPPER_LIMIT_NUMERATOR / (float)PVRGL_RT_HEIGHT;
      create_info.isp_merge_upper_y = fui(value);
      value = ((float)PVRGL_RT_WIDTH * ROGUE_ISP_MERGE_SCALE_FACTOR) /
              (ROGUE_ISP_MERGE_UPPER_LIMIT_NUMERATOR -
               ROGUE_ISP_MERGE_LOWER_LIMIT_NUMERATOR);
      create_info.isp_merge_scale_x = fui(value);
      value = ((float)PVRGL_RT_HEIGHT * ROGUE_ISP_MERGE_SCALE_FACTOR) /
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
   mesa_logi("pvrgl: render init step rt_dataset vk=%d", vk);
   if (vk != VK_SUCCESS)
      goto err_rgn;

   /* ---- VDM callstack BO + RENDER context. ---- */
   {
      struct pvr_winsys_render_ctx_create_info rctx_info;

      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        sizeof(uint64_t) * PVRGL_VDM_CALLSTACK_MAX_DEPTH,
                        ROGUE_CR_VDM_CALL_STACK_POINTER_ADDR_ALIGNMENT,
                        &r->vdm_callstack_bo);
      if (vk != VK_SUCCESS)
         goto err_rt_dataset;

      memset(&rctx_info, 0, sizeof(rctx_info));
      rctx_info.priority = PVR_WINSYS_CTX_PRIORITY_MEDIUM;
      rctx_info.vdm_callstack_addr.addr = r->vdm_callstack_bo.dev_addr;
      /* Minimal static state: kernel only bounds-checks; single-shot jobs
       * never trigger context switch/resume. */
      rctx_info.static_state.rogue.vdm_ctx_state_base_addr = 0;
      rctx_info.static_state.rogue.geom_ctx_state_base_addr = 0;

      vk = screen->ws->ops->render_ctx_create(screen->ws, &rctx_info,
                                              dev_info, &r->rctx);
      mesa_logi("pvrgl: render init step rctx vk=%d", vk);
      if (vk != VK_SUCCESS)
         goto err_callstack;
   }

   /* ---- Aux BOs. ---- */
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

      {
         uint32_t scissor[2] = { 0 };
         pvr_csb_pack (&scissor[0], IPF_SCISSOR_WORD_0, w0) {
            w0.scw0_xmax = PVRGL_RT_WIDTH;
            w0.scw0_xmin = 0;
         }
         pvr_csb_pack (&scissor[1], IPF_SCISSOR_WORD_1, w1) {
            w1.scw1_ymax = PVRGL_RT_HEIGHT;
            w1.scw1_ymin = 0;
         }
         vk = pvrgl_upload(screen, screen->heaps->general_heap, scissor,
                           sizeof(scissor), cache_line_size, &r->scissor_bo);
         if (vk != VK_SUCCESS)
            goto err_border;
      }

      vk = pvrgl_upload(screen, screen->heaps->general_heap, NULL,
                        64U, cache_line_size, &r->depth_bias_bo);
      if (vk != VK_SUCCESS)
         goto err_scissor;
   }

   mesa_logi("pvrgl: render init ok (rt=%ux%u fl=%llu/%u rctx=%p)",
             PVRGL_RT_WIDTH, PVRGL_RT_HEIGHT,
             (unsigned long long)runtime_info->min_free_list_size,
             PVRGL_GLOBAL_FL_INITIAL, (void *)r->rctx);

   *out = r;
   return VK_SUCCESS;

err_scissor:
   pvrgl_bo_free(screen, &r->scissor_bo);
err_border:
   pvrgl_bo_free(screen, &r->border_colour_bo);
err_ctrl:
   pvrgl_bo_free(screen, &r->ctrl_stream_bo);
err_rctx:
   screen->ws->ops->render_ctx_destroy(r->rctx);
err_callstack:
   pvrgl_bo_free(screen, &r->vdm_callstack_bo);
err_rt_dataset:
   screen->ws->ops->render_target_dataset_destroy(r->rt_dataset);
err_rgn:
   pvrgl_bo_free(screen, &r->rgn_hdr_bo);
err_mlist:
   pvrgl_bo_free(screen, &r->mlist_bo);
err_tpc:
   pvrgl_bo_free(screen, &r->tpc_bo);
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

   pvrgl_bo_free(screen, &r->depth_bias_bo);
   pvrgl_bo_free(screen, &r->scissor_bo);
   pvrgl_bo_free(screen, &r->border_colour_bo);
   pvrgl_bo_free(screen, &r->ctrl_stream_bo);
   screen->ws->ops->render_ctx_destroy(r->rctx);
   pvrgl_bo_free(screen, &r->vdm_callstack_bo);
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
                       VkFormat rt_format)
{
   const struct pvr_device_info *dev_info = r->screen->dev_info;
   /* BXM-4-64 MC1 has NO gpu_multicore_support — mesa's feature table wrongly
    * claims it (upstream FIXME). Emitting the multicore-gated fields
    * (isp_oclqry_stride/execute_count) makes the kernel stream parse reject
    * with EINVAL (trailing data). Kernel truth: pvr_stream_defs.c gates them
    * on PVR_FEATURE_GPU_MULTICORE_SUPPORT, which is false for this part.
    * Verified 2026-08-27: full submit dump shows 200B stream vs kernel's
    * 192B expected. */
   const bool multicore = false;
   (void)dev_info;
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
      surf_params.stride = PVRGL_RT_WIDTH * 4U;
      surf_params.depth = 1U;
      surf_params.width = PVRGL_RT_WIDTH;
      surf_params.height = PVRGL_RT_HEIGHT;
      surf_params.z_only_render = false;
      surf_params.down_scale = false;

      memset(&render_params, 0, sizeof(render_params));
      render_params.min_x_clip = 0U;
      render_params.min_y_clip = 0U;
      render_params.max_x_clip = PVRGL_RT_WIDTH - 1U;
      render_params.max_y_clip = PVRGL_RT_HEIGHT - 1U;
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

   pvr_csb_pack ((uint64_t *)stream_ptr, CR_TPU_BORDER_COLOUR_TABLE_PDM,
                 value) {
      value.border_colour_table_address =
         PVR_DEV_ADDR(r->border_colour_bo.dev_addr);
   }
   stream_ptr += pvr_cmd_length(CR_TPU_BORDER_COLOUR_TABLE_PDM);

   /* CR_PDS_BGRND0/1/3: zero (no load-op; USC clear regs handle the clear).
    * 3 x u64. */
   memset(stream_ptr, 0, 3U * DWORDS_PER_U64 * sizeof(uint32_t));
   stream_ptr += 3U * DWORDS_PER_U64;
   /* PR bgnd: another 3 x u64. */
   memset(stream_ptr, 0, 3U * DWORDS_PER_U64 * sizeof(uint32_t));
   stream_ptr += 3U * DWORDS_PER_U64;

   /* USC clear registers: kernel expects the FULL
    * usc_clear_register[ROGUE_MAXIMUM_OUTPUT_REGISTERS_PER_PIXEL=8] array
    * (8 x u32 = 32B) — PVR_STREAM_DEF_ARRAY consumes sizeof(regs.usc_clear_register).
    * kmd_stream.xml: usc_clear_register size=256 bits. pvrgl emitted only 4
    * (16B) -> kernel stream parse ran out of data -> EINVAL. Zero all 8
    * (P1: no color clear via render yet). */
   {
      uint32_t i;
      for (i = 0; i < 8U; i++) {
         pvr_csb_pack (stream_ptr, CR_USC_CLEAR_REGISTER, reg) {
            reg.val = 0;
         }
         stream_ptr += pvr_cmd_length(CR_USC_CLEAR_REGISTER);
      }
   }

   *stream_ptr = 0; /* USC_PIXEL_OUTPUT_CTRL */
   stream_ptr += pvr_cmd_length(CR_USC_PIXEL_OUTPUT_CTRL);

   pvr_csb_pack (stream_ptr, CR_ISP_BGOBJDEPTH, value) {
      value.value = 0;
   }
   stream_ptr += pvr_cmd_length(CR_ISP_BGOBJDEPTH);

   pvr_csb_pack (stream_ptr, CR_ISP_BGOBJVALS, value) {
      value.enablebgtag = false;
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
      value.process_empty_tiles = false;
      if (multicore)
         value.skip_init_hdrs = true;
   }
   stream_ptr += pvr_cmd_length(CR_ISP_CTL);

   pvr_csb_pack (stream_ptr, CR_EVENT_PIXEL_PDS_INFO, value) {
      value.const_size = 0;
      value.temp_stride = 0;
      value.usc_sr_size = 1;
   }
   stream_ptr += pvr_cmd_length(CR_EVENT_PIXEL_PDS_INFO);

   pvr_csb_pack (stream_ptr, KMD_STREAM_VIEW_IDX, value) {
      value.idx = 0;
   }
   stream_ptr += pvr_cmd_length(KMD_STREAM_VIEW_IDX);

   pvr_csb_pack (stream_ptr, CR_EVENT_PIXEL_PDS_DATA, value) {
      value.addr = PVR_DEV_ADDR(0U);
   }
   stream_ptr += pvr_cmd_length(CR_EVENT_PIXEL_PDS_DATA);

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
pvrgl_render_test_submit(struct pvrgl_render *r,
                         const struct pvrgl_bo *rt_bo,
                         VkFormat rt_format)
{
   struct pvr_winsys_render_submit_info submit_info;
   VkResult vk;

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
   pvrgl_frag_stream_init(r, &submit_info.fragment, rt_bo, rt_format);

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

   vk = pvrgl_render_test_submit(r, &rt_bo, VK_FORMAT_B8G8R8A8_UNORM);

   pvrgl_bo_free(screen, &rt_bo);
out_fini:
   pvrgl_render_fini(r);
   return vk;
}
