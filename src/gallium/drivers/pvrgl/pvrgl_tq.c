/* pvrgl_tq.c — transfer-queue (TQ) hardware clear backend.
 *
 * Faithful port of the imagination Vulkan driver's TQ fill/clear path
 * (src/imagination/vulkan/pvr_arch_job_transfer.c @ 26.3.0-devel) to
 * Gallium types. Reference line numbers refer to that file.
 */
#include "pvrgl_tq.h"

#include <math.h>
#include <stdint.h>

#include "util/u_memory.h"
#include "util/u_math.h"
#include "util/log.h"

#include "imagination/vulkan/winsys/pvr_winsys.h"
#include "imagination/vulkan/pvr_job_common.h"
#include "imagination/vulkan/pvr_usc.h"
#include "imagination/vulkan/pds/pvr_pds.h"
#include "imagination/vulkan/pvr_csb.h"
#include "imagination/common/pvr_device_info.h"
#include "imagination/include/hwdef/pvr_hw_utils.h"

#include "pco_uscgen_programs.h"

#include "pvrgl_screen.h"
#include "pvrgl_resource.h"

#ifndef PVR_DW_TO_BYTES
#define PVR_DW_TO_BYTES(dw) ((dw) * 4)
#endif

/* Minimal stand-in for the vulkan driver's pvr_transfer_3d_state. */
struct pvrgl_tq_state {
   struct pvr_winsys_transfer_regs regs;

   uint32_t pds_temps;
   uint32_t uniform_data_size;
   uint32_t tex_state_data_size;
   uint32_t coeff_data_size;
   uint32_t usc_coeff_regs;
   uint32_t common_ptr;

   uint32_t pds_shader_task_offset;
   uint32_t uni_tex_code_offset;
   uint32_t tex_state_data_offset;
   uint32_t pds_coeff_task_offset;

   uint32_t msaa_multiplier;
   uint32_t usc_pixel_width;

   uint32_t origin_x_in_tiles;
   uint32_t origin_y_in_tiles;
   uint32_t width_in_tiles;
   uint32_t height_in_tiles;
};

/* ------------------------------------------------------------------ */
/* Upload helpers                                                      */
/* ------------------------------------------------------------------ */

struct pvrgl_bo {
   struct pvr_winsys_bo *bo;
   struct pvr_winsys_vma *vma;
   uint64_t heap_offset;
   /* Full device address (heap base + offset) as returned by vma_map. */
   uint64_t dev_addr;
};

static VkResult
pvrgl_upload(struct pvrgl_screen *screen,
             struct pvr_winsys_heap *heap,
             const void *data,
             uint32_t size,
             uint32_t align,
             struct pvrgl_bo *out)
{
   const uint32_t page = 4096;
   const uint32_t alloc_size = align64(MAX2(size, page), page);
   VkResult vk;

   memset(out, 0, sizeof(*out));

   vk = screen->ws->ops->buffer_create(screen->ws,
                                       alloc_size,
                                       page,
                                       PVR_WINSYS_BO_TYPE_GPU,
                                       PVR_WINSYS_BO_FLAG_CPU_ACCESS,
                                       &out->bo);
   if (vk != VK_SUCCESS)
      return vk;

   vk = screen->ws->ops->heap_alloc(heap, alloc_size, page, &out->vma);
   if (vk != VK_SUCCESS)
      goto err_bo;

   {
      pvr_dev_addr_t addr;
      vk = screen->ws->ops->vma_map(out->vma, out->bo, 0, alloc_size, &addr);
      if (vk != VK_SUCCESS)
         goto err_vma;
      out->heap_offset = addr.addr - heap->base_addr.addr;
      out->dev_addr = addr.addr;
   }

   vk = screen->ws->ops->buffer_map(out->bo, NULL);
   if (vk != VK_SUCCESS)
      goto err_vma;

   /* New GEM BOs are zeroed by the kernel; copy payload when given. */
   if (data)
      memcpy(out->bo->map, data, size);

   {
      const char *hname = "?";
      if (screen->heaps->general_heap == heap)
         hname = "general";
      else if (screen->heaps->pds_heap == heap)
         hname = "pds";
      else if (screen->heaps->usc_heap == heap)
         hname = "usc";
      else if (screen->heaps->transfer_frag_heap == heap)
         hname = "tfrag";
      mesa_logi("pvrgl: alloc heap=%s size=%u dev_addr=0x%llx heap_offset=0x%llx",
                hname, size,
                (unsigned long long)out->dev_addr,
                (unsigned long long)out->heap_offset);
   }

   return VK_SUCCESS;

err_vma:
   screen->ws->ops->heap_free(out->vma);
err_bo:
   screen->ws->ops->buffer_destroy(out->bo);
   return vk;
}

static void
pvrgl_bo_free(struct pvrgl_screen *screen, struct pvrgl_bo *gbo)
{
   if (!gbo->bo)
      return;

   if (gbo->bo->map)
      screen->ws->ops->buffer_unmap(gbo->bo, false);
   if (gbo->vma) {
      screen->ws->ops->vma_unmap(gbo->vma);
      screen->ws->ops->heap_free(gbo->vma);
   }
   screen->ws->ops->buffer_destroy(gbo->bo);
   memset(gbo, 0, sizeof(*gbo));
}

/* ------------------------------------------------------------------ */
/* TQ context                                                          */
/* ------------------------------------------------------------------ */

struct pvrgl_tq {
   pco_ctx *pco_ctx;

   /* Per-RT-count EOT programs (index = rt_count - 1), on usc heap. */
   struct {
      struct pvrgl_bo bo;
      uint32_t temps;
   } eot[PVR_TRANSFER_MAX_RENDER_TARGETS];

   /* NOP program (USC blob + PDS kicker) for TA_STATE_PDS_SHADERBASE. */
   struct {
      struct pvrgl_bo usc;
      struct pvrgl_bo pds;
   } nop;
};

static VkResult
pvrgl_tq_upload_eot(struct pvrgl_screen *screen,
                    unsigned rt_count,
                    struct pvrgl_tq *tq)
{
   const unsigned state_regs[PVR_TRANSFER_MAX_RENDER_TARGETS] = {
      0, PVR_STATE_PBE_DWORDS, 2 * PVR_STATE_PBE_DWORDS,
   };
   struct pvr_eot_props props = {
      .emit_count = rt_count,
      .shared_words = true,
      .msaa_samples = 1,
      .num_output_regs = 4,
      .tile_buffer_addrs = { 0 },
   };
   const uint32_t cache_line =
      pvr_get_slc_cache_line_size(screen->dev_info);
   pco_shader *eot;
   VkResult vk;

   props.state_regs = state_regs;

   eot = pvr_usc_eot(tq->pco_ctx, &props, screen->dev_info);
   if (!eot)
      return VK_ERROR_UNKNOWN;

   vk = pvrgl_upload(screen,
                     screen->heaps->usc_heap,
                     pco_shader_binary_data(eot),
                     pco_shader_binary_size(eot),
                     cache_line,
                     &tq->eot[rt_count - 1].bo);
   tq->eot[rt_count - 1].temps = pco_shader_data(eot)->common.temps;
   {
      /* Dump EOT binary for comparison with upstream-generated program. */
      const uint32_t *bin = (const uint32_t *)pco_shader_binary_data(eot);
      size_t nw = pco_shader_binary_size(eot) / 4;
      char hx[512]; size_t off = 0;
      for (size_t i = 0; i < nw && off < sizeof(hx) - 12; i++)
         off += snprintf(hx + off, sizeof(hx) - off, "%08x ", bin[i]);
      mesa_logi("pvrgl: EOT%d size=%u temps=%u words=%u %s",
                rt_count, (unsigned)pco_shader_binary_size(eot),
                (unsigned)pco_shader_data(eot)->common.temps, (unsigned)nw, hx);
   }
   ralloc_free(eot);

   return vk;
}

static VkResult
pvrgl_tq_upload_nop(struct pvrgl_screen *screen, struct pvrgl_tq *tq)
{
   const uint32_t cache_line =
      pvr_get_slc_cache_line_size(screen->dev_info);
   const pco_precomp_data *precomp =
      (const pco_precomp_data *)pco_usclib_common[FS_NOP_COMMON];
   struct pvr_pds_kickusc_program program = { 0 };
   uint32_t staging[512];
   VkResult vk;

   vk = pvrgl_upload(screen,
                     screen->heaps->usc_heap,
                     precomp->binary,
                     precomp->size_dwords * sizeof(uint32_t),
                     cache_line,
                     &tq->nop.usc);
   if (vk != VK_SUCCESS)
      return vk;

   pvr_pds_setup_doutu(&program.usc_task_control,
                       tq->nop.usc.heap_offset,
                       precomp->temps,
                       ROGUE_PDSINST_DOUTU_SAMPLE_RATE_INSTANCE,
                       false);
   pvr_pds_set_sizes_pixel_shader(&program);

   assert((program.code_size + program.data_size) * 4 <= sizeof(staging));
   pvr_pds_generate_pixel_shader_program(&program, staging);

   return pvrgl_upload(screen,
                       screen->heaps->general_heap,
                       staging,
                       (program.code_size + program.data_size) * 4,
                       16,
                       &tq->nop.pds);
}

VkResult
pvrgl_tq_init(struct pvrgl_screen *screen, struct pvrgl_tq **tq_out)
{
   struct pvrgl_tq *tq;
   VkResult vk;

   tq = CALLOC_STRUCT(pvrgl_tq);
   if (!tq)
      return VK_ERROR_OUT_OF_HOST_MEMORY;

   tq->pco_ctx = pco_ctx_create(screen->dev_info, screen->runtime_info, NULL);
   if (!tq->pco_ctx) {
      FREE(tq);
      return VK_ERROR_INITIALIZATION_FAILED;
   }

   for (unsigned i = 0; i < ARRAY_SIZE(tq->eot); i++) {
      vk = pvrgl_tq_upload_eot(screen, i + 1, tq);
      if (vk != VK_SUCCESS)
         goto err;
   }

   vk = pvrgl_tq_upload_nop(screen, tq);
   if (vk != VK_SUCCESS)
      goto err;

   mesa_logi("pvrgl: TQ ready (EOT x%u + nop program uploaded)",
             (unsigned)ARRAY_SIZE(tq->eot));

   *tq_out = tq;
   return VK_SUCCESS;

err:
   for (unsigned i = 0; i < ARRAY_SIZE(tq->eot); i++)
      pvrgl_bo_free(screen, &tq->eot[i].bo);
   pvrgl_bo_free(screen, &tq->nop.usc);
   pvrgl_bo_free(screen, &tq->nop.pds);
   ralloc_free(tq->pco_ctx);
   FREE(tq);
   return vk;
}

void
pvrgl_tq_finish(struct pvrgl_screen *screen, struct pvrgl_tq *tq)
{
   if (!tq)
      return;

   for (unsigned i = 0; i < ARRAY_SIZE(tq->eot); i++)
      pvrgl_bo_free(screen, &tq->eot[i].bo);
   pvrgl_bo_free(screen, &tq->nop.usc);
   pvrgl_bo_free(screen, &tq->nop.pds);
   ralloc_free(tq->pco_ctx);
   FREE(tq);
}

/* ------------------------------------------------------------------ */
/* Clear color packing — U8U8U8U8 normalized [ref :2372].              */
/* ------------------------------------------------------------------ */

static uint32_t
pvrgl_float_to_ufixed(float f, int bits)
{
   float scaled = f * ((1 << bits) - 1);
   long v = lroundf(fmaxf(fminf(scaled, (float)((1 << bits) - 1)), 0.0f));
   return (uint32_t)v;
}

static void
pvrgl_pack_clear_color_u8(const float color[4], uint32_t pkd[4])
{
   pkd[0] = pvrgl_float_to_ufixed(color[0], 8) |
            (pvrgl_float_to_ufixed(color[1], 8) << 8) |
            (pvrgl_float_to_ufixed(color[2], 8) << 16) |
            (pvrgl_float_to_ufixed(color[3], 8) << 24);
   pkd[1] = pkd[2] = pkd[3] = 0;
}

/* ------------------------------------------------------------------ */
/* Primitive block writer [ref :3865-4005].                            */
/* ------------------------------------------------------------------ */

static uint32_t
pvrgl_prim_block_size(const struct pvr_device_info *dev_info,
                      uint32_t num_mappings)
{
   const bool sipf = PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format);
   const uint32_t num_isp_vertices = num_mappings * 4U;
   uint32_t idx_dw, isp_state_dw, pds_state_dw, vertex_dw;

   if (sipf) {
      idx_dw = ALIGN_POT(num_mappings, 2U);
      isp_state_dw = 4U;
      pds_state_dw = 8U;
      vertex_dw = num_isp_vertices * 2U; /* SIPF vertex word = 8B */
   } else {
      idx_dw = num_mappings + DIV_ROUND_UP(num_mappings, 2U);
      isp_state_dw = 5U;
      pds_state_dw = 7U;
      vertex_dw = DIV_ROUND_UP(num_isp_vertices * 10U, 4U);
   }

   return PVR_DW_TO_BYTES(idx_dw + isp_state_dw + pds_state_dw + vertex_dw);
}

static void
pvrgl_write_prim_block_fill(const struct pvr_device_info *dev_info,
                            struct pvrgl_tq_state *state,
                            int32_t x0, int32_t y0,
                            int32_t width, int32_t height,
                            uint32_t **cs_ptr_out)
{
   const bool sipf = PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format);
   const bool sipf2 =
      PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format_v2);
   uint32_t *cs_ptr = *cs_ptr_out;
   const uint32_t num_isp_vertices = 4U;

   /* ---- ISP state block [ref :3425]. ---- */
   if (sipf2) {
      pvr_csb_pack ((uint64_t *)cs_ptr, IPF_VERTEX_FORMAT_WORD_SIPF2, fmt) {
         fmt.vf_isp_state_size =
            pvr_cmd_length(TA_STATE_ISPCTL) + pvr_cmd_length(TA_STATE_ISPA);
         fmt.vf_tsp_vtx_raw = true;
         fmt.vf_isp_vtx_raw = true;
         fmt.vf_varying_vertex_bits = 0U;
         fmt.vf_primitive_total = (num_isp_vertices / 2U) - 1U;
         fmt.vf_vertex_total = num_isp_vertices - 1U;
      }
      cs_ptr += pvr_cmd_length(IPF_VERTEX_FORMAT_WORD_SIPF2);
   }

   pvr_csb_pack (cs_ptr, TA_STATE_ISPCTL, ispctl);
   cs_ptr += pvr_cmd_length(TA_STATE_ISPCTL);

   pvr_csb_pack (cs_ptr, TA_STATE_ISPA, ispa) {
      ispa.objtype = ROGUE_TA_OBJTYPE_TRIANGLE;
      ispa.passtype = ROGUE_TA_PASSTYPE_OPAQUE;
      ispa.dcmpmode = ROGUE_TA_CMPMODE_ALWAYS;
      ispa.dwritedisable = true;
   }
   cs_ptr += pvr_cmd_length(TA_STATE_ISPA);

   if (!sipf2) {
      pvr_csb_pack (cs_ptr, IPF_COMPRESSION_SIZE_WORD, word) {
         word.cs_isp_comp_table_size = 0U;
         word.cs_tsp_comp_format_size = 0U;
         word.cs_tsp_comp_table_size = 0U;
         word.cs_tsp_comp_vertex_size = 0U;
      }
      cs_ptr += pvr_cmd_length(IPF_COMPRESSION_SIZE_WORD);

      pvr_csb_pack (cs_ptr, IPF_ISP_COMPRESSION_WORD_0, w0) {
         w0.cf_isp_comp_fmt_x0 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
         w0.cf_isp_comp_fmt_x1 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
         w0.cf_isp_comp_fmt_x2 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
         w0.cf_isp_comp_fmt_y0 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
         w0.cf_isp_comp_fmt_y1 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
         w0.cf_isp_comp_fmt_y2 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
         w0.cf_isp_comp_fmt_z0 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
         w0.cf_isp_comp_fmt_z1 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
      }
      cs_ptr += pvr_cmd_length(IPF_ISP_COMPRESSION_WORD_0);

      pvr_csb_pack (cs_ptr, IPF_ISP_COMPRESSION_WORD_1, w1) {
         w1.vf_prim_msaa = 0U;
         w1.vf_prim_id_pres = 0U;
         w1.vf_vertex_clipped = 0U;
         w1.vf_vertex_total = num_isp_vertices - 1U;
         w1.cf_isp_comp_fmt_z3 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
         w1.cf_isp_comp_fmt_z2 = ROGUE_IPF_COMPRESSION_FORMAT_RAW_BYTE;
      }
      cs_ptr += pvr_cmd_length(IPF_ISP_COMPRESSION_WORD_1);
   }

   /* ---- Index block [ref :3513] for one mapping (two triangles). ---- */
   if (sipf) {
      pvr_csb_pack ((uint64_t *)cs_ptr, IPF_INDEX_DATA_WORDS_SIPF, iw) {
         iw.ix_triangle3_index_2 = 5U;
         iw.ix_triangle3_index_1 = 6U;
         iw.ix_triangle3_index_0 = 7U;
         iw.ix_triangle2_index_2 = 6U;
         iw.ix_triangle2_index_1 = 5U;
         iw.ix_triangle2_index_0 = 4U;
         iw.ix_triangle1_index_2 = 1U;
         iw.ix_triangle1_index_1 = 2U;
         iw.ix_triangle1_index_0 = 3U;
         iw.ix_triangle0_index_2 = 2U;
         iw.ix_triangle0_index_1 = 1U;
         iw.ix_triangle0_index_0 = 0U;
      }
      cs_ptr += pvr_cmd_length(IPF_INDEX_DATA_WORDS_SIPF);
   } else {
      /* Exact upstream even-iteration pattern for num_mappings = 1:
       * first word fully written, second word partially written and left
       * for a would-be odd iteration; BO memory is zeroed by the kernel.
       */
      pvr_csb_pack (cs_ptr, IPF_INDEX_DATA, w) {
         w.ix_index0_0 = 0U;
         w.ix_index0_1 = 1U;
         w.ix_index0_2 = 2U;
         w.ix_index1_0 = 3U;
      }
      cs_ptr += pvr_cmd_length(IPF_INDEX_DATA);

      pvr_csb_pack (cs_ptr, IPF_INDEX_DATA, w) {
         w.ix_index0_0 = 2U;
         w.ix_index0_1 = 1U;
      }
      /* Odd-count tail: advance without completing the pair [ref :3599]. */
      cs_ptr++;
   }

   /* ---- ISP vertices [ref :3651]: full-surface quad, biased 24-bit. --- */
   {
      bool bias = true;
      uint32_t top, bottom, left, right;

      if (PVR_HAS_FEATURE(dev_info, screen_size8K))
         bias = state->width_in_tiles <= 256U && state->height_in_tiles <= 256U;

      top = (uint32_t)(y0 + (bias ? ROGUE_IPF_ISP_VERTEX_XY_BIAS_VALUE : 0));
      bottom = (uint32_t)(y0 + height +
                          (bias ? ROGUE_IPF_ISP_VERTEX_XY_BIAS_VALUE : 0));
      left = (uint32_t)(x0 + (bias ? ROGUE_IPF_ISP_VERTEX_XY_BIAS_VALUE : 0));
      right = (uint32_t)(x0 + width +
                         (bias ? ROGUE_IPF_ISP_VERTEX_XY_BIAS_VALUE : 0));

      if (sipf) {
         pvr_csb_pack ((uint64_t *)cs_ptr, IPF_ISP_VERTEX_WORD_SIPF, v) {
            v.y = top;    v.x = left;
         }
         cs_ptr += pvr_cmd_length(IPF_ISP_VERTEX_WORD_SIPF);
         pvr_csb_pack ((uint64_t *)cs_ptr, IPF_ISP_VERTEX_WORD_SIPF, v) {
            v.y = top;    v.x = right;
         }
         cs_ptr += pvr_cmd_length(IPF_ISP_VERTEX_WORD_SIPF);
         pvr_csb_pack ((uint64_t *)cs_ptr, IPF_ISP_VERTEX_WORD_SIPF, v) {
            v.y = bottom; v.x = left;
         }
         cs_ptr += pvr_cmd_length(IPF_ISP_VERTEX_WORD_SIPF);
         pvr_csb_pack ((uint64_t *)cs_ptr, IPF_ISP_VERTEX_WORD_SIPF, v) {
            v.y = bottom; v.x = right;
         }
         cs_ptr += pvr_cmd_length(IPF_ISP_VERTEX_WORD_SIPF);
      } else {
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_0, w0) {
            w0.x0 = left;
            w0.y0 = top & 0xFF;
         }
         cs_ptr++;
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_1, w1) {
            w1.y0 = top >> ROGUE_IPF_ISP_VERTEX_WORD_1_Y0_SHIFT;
         }
         cs_ptr++;
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_2, w2) {
            w2.x1 = right & 0xFFFF;
            w2.z0 = 0U;
         }
         cs_ptr++;
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_3, w3) {
            w3.x1 = right >> ROGUE_IPF_ISP_VERTEX_WORD_3_X1_SHIFT;
            w3.y1 = top;
         }
         cs_ptr++;
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_4, w4) {
            w4.z1 = 0U;
         }
         cs_ptr++;

         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_0, w0) {
            w0.x0 = left;
            w0.y0 = bottom & 0xFF;
         }
         cs_ptr++;
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_1, w1) {
            w1.y0 = bottom >> ROGUE_IPF_ISP_VERTEX_WORD_1_Y0_SHIFT;
         }
         cs_ptr++;
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_2, w2) {
            w2.x1 = right & 0xFFFF;
            w2.z0 = 0U;
         }
         cs_ptr++;
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_3, w3) {
            w3.x1 = right >> ROGUE_IPF_ISP_VERTEX_WORD_3_X1_SHIFT;
            w3.y1 = bottom;
         }
         cs_ptr++;
         pvr_csb_pack (cs_ptr, IPF_ISP_VERTEX_WORD_4, w4) {
            w4.z1 = 0U;
         }
         cs_ptr++;
      }
   }

   /* ---- PDS state block [ref :3350]. ---- */
   pvr_csb_pack (cs_ptr, TA_STATE_PDS_SHADERBASE, shader_base) {
      shader_base.addr = PVR_DEV_ADDR(state->pds_shader_task_offset);
   }
   cs_ptr++;

   pvr_csb_pack (cs_ptr, TA_STATE_PDS_TEXUNICODEBASE, tex_base) {
      tex_base.addr = PVR_DEV_ADDR(state->uni_tex_code_offset);
   }
   cs_ptr++;

   pvr_csb_pack (cs_ptr, TA_STATE_PDS_SIZEINFO1, info1) {
      info1.pds_uniformsize =
         state->uniform_data_size /
         ROGUE_TA_STATE_PDS_SIZEINFO1_PDS_UNIFORMSIZE_UNIT_SIZE;
      info1.pds_texturestatesize =
         state->tex_state_data_size /
         ROGUE_TA_STATE_PDS_SIZEINFO1_PDS_TEXTURESTATESIZE_UNIT_SIZE;
      info1.pds_varyingsize =
         state->coeff_data_size /
         ROGUE_TA_STATE_PDS_SIZEINFO1_PDS_VARYINGSIZE_UNIT_SIZE;
      info1.usc_varyingsize =
         ALIGN_POT(state->usc_coeff_regs,
                   ROGUE_TA_STATE_PDS_SIZEINFO1_USC_VARYINGSIZE_UNIT_SIZE) /
         ROGUE_TA_STATE_PDS_SIZEINFO1_USC_VARYINGSIZE_UNIT_SIZE;
      info1.pds_tempsize =
         ALIGN_POT(state->pds_temps,
                   ROGUE_TA_STATE_PDS_SIZEINFO1_PDS_TEMPSIZE_UNIT_SIZE) /
         ROGUE_TA_STATE_PDS_SIZEINFO1_PDS_TEMPSIZE_UNIT_SIZE;
   }
   cs_ptr++;

   pvr_csb_pack (cs_ptr, TA_STATE_PDS_VARYINGBASE, base) {
      base.addr = PVR_DEV_ADDR(state->pds_coeff_task_offset);
   }
   cs_ptr++;

   pvr_csb_pack (cs_ptr, TA_STATE_PDS_TEXTUREDATABASE, base) {
      base.addr = PVR_DEV_ADDR(state->tex_state_data_offset);
   }
   cs_ptr++;

   pvr_csb_pack (cs_ptr, TA_STATE_PDS_UNIFORMDATABASE, base) {
      base.addr = PVR_DEV_ADDR(0U);
   }
   cs_ptr++;

   pvr_csb_pack (cs_ptr, TA_STATE_PDS_SIZEINFO2, info) {
      info.usc_sharedsize =
         ALIGN_POT(state->common_ptr,
                   ROGUE_TA_STATE_PDS_SIZEINFO2_USC_SHAREDSIZE_UNIT_SIZE) /
         ROGUE_TA_STATE_PDS_SIZEINFO2_USC_SHAREDSIZE_UNIT_SIZE;
      info.pds_tri_merge_disable = !PVR_HAS_ENHANCEMENT(dev_info, 42307);
      info.pds_batchnum = 0U;
   }
   cs_ptr++;

   if (sipf)
      cs_ptr++; /* realign to 64 bits */


   *cs_ptr_out = cs_ptr;
}

/* Background-object regs [ref :651] — zero offsets for the clear path. */
static inline void
pvrgl_setup_hwbg_object(struct pvrgl_tq_state *state)
{
   struct pvr_winsys_transfer_regs *regs = &state->regs;

   pvr_csb_pack (&regs->pds_bgnd0_base, CR_PDS_BGRND0_BASE, reg) {
      reg.shader_addr = PVR_DEV_ADDR(state->pds_shader_task_offset);
      reg.texunicode_addr = PVR_DEV_ADDR(state->uni_tex_code_offset);
   }

   pvr_csb_pack (&regs->pds_bgnd1_base, CR_PDS_BGRND1_BASE, reg) {
      reg.texturedata_addr = PVR_DEV_ADDR(state->tex_state_data_offset);
   }

   pvr_csb_pack (&regs->pds_bgnd3_sizeinfo, CR_PDS_BGRND3_SIZEINFO, reg) {
      reg.usc_sharedsize =
         DIV_ROUND_UP(state->common_ptr,
                      ROGUE_CR_PDS_BGRND3_SIZEINFO_USC_SHAREDSIZE_UNIT_SIZE);
      reg.pds_uniformsize =
         state->uniform_data_size /
         ROGUE_CR_PDS_BGRND3_SIZEINFO_PDS_UNIFORMSIZE_UNIT_SIZE;
      reg.pds_texturestatesize =
         state->tex_state_data_size /
         ROGUE_CR_PDS_BGRND3_SIZEINFO_PDS_TEXTURESTATESIZE_UNIT_SIZE;
      reg.pds_tempsize =
         DIV_ROUND_UP(state->pds_temps,
                      ROGUE_CR_PDS_BGRND3_SIZEINFO_PDS_TEMPSIZE_UNIT_SIZE);
   }
}

/* ------------------------------------------------------------------ */
/* Clear surface                                                       */
/* ------------------------------------------------------------------ */

VkResult
pvrgl_tq_clear_surface(struct pvrgl_screen *screen,
                       struct pvrgl_resource *dst,
                       const float color[4])
{
   struct pvrgl_tq *tq = screen->tq_priv;
   const struct pvr_device_info *dev_info = screen->dev_info;
   const bool sipf = PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format);
   const bool sipf2 =
      PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format_v2);
   struct pvr_winsys_transfer_submit_info submit_info;
   struct pvr_winsys_transfer_cmd *cmd;
   struct pvr_winsys_transfer_regs *regs;
   struct pvrgl_tq_state state;
   struct pvr_pbe_surf_params surf_params;
   struct pvr_pbe_render_params render_params;
   struct pvr_pds_event_program event_program;
   uint32_t pbe_words[ROGUE_NUM_PBESTATE_STATE_WORDS];
   uint32_t packed_color[4] = { 0 };
   struct pvrgl_bo event_pds_bo;
   struct pvrgl_bo cs_bo;
   uint32_t tile_x, tile_y;
   uint32_t code_off = 0;
   VkResult vk;

   memset(&event_pds_bo, 0, sizeof(event_pds_bo));
   memset(&cs_bo, 0, sizeof(cs_bo));
   memset(&state, 0, sizeof(state));

   tile_x = PVR_GET_FEATURE_VALUE(dev_info, tile_size_x, 32U);
   tile_y = PVR_GET_FEATURE_VALUE(dev_info, tile_size_y, 32U);

   pvrgl_pack_clear_color_u8(color, packed_color);

   state.msaa_multiplier = 0U;
   state.origin_x_in_tiles = 0U;
   state.origin_y_in_tiles = 0U;
   state.width_in_tiles = DIV_ROUND_UP(dst->base.width0, tile_x);
   state.height_in_tiles = DIV_ROUND_UP(dst->base.height0, tile_y);

   regs = &state.regs;

   /* ---- Clear regs [ref :2840 no-shader branch]. ---- */
   state.pds_temps = 0U;
   state.uniform_data_size = 0U;
   state.tex_state_data_size = 0U;

   pvr_csb_pack (&regs->isp_bgobjvals, CR_ISP_BGOBJVALS, reg);
   pvr_csb_pack (&regs->isp_aa, CR_ISP_AA, reg) {
      reg.mode = ROGUE_CR_ISP_AA_MODE_TYPE_AA_NONE;
   }

   pvr_csb_pack (&regs->usc_clear_register0, CR_USC_CLEAR_REGISTER, reg) {
      reg.val = packed_color[0U];
   }
   pvr_csb_pack (&regs->usc_clear_register1, CR_USC_CLEAR_REGISTER, reg) {
      reg.val = packed_color[1U];
   }
   pvr_csb_pack (&regs->usc_clear_register2, CR_USC_CLEAR_REGISTER, reg) {
      reg.val = packed_color[2U];
   }
   pvr_csb_pack (&regs->usc_clear_register3, CR_USC_CLEAR_REGISTER, reg) {
      reg.val = packed_color[3U];
   }

   /* No-shader clear: upstream (pvr_arch_job_transfer.c:2873-2875) zeroes
    * all PDS bases for the source_count==0 path — USC_SHAREDSIZE=0 in
    * pds_bgnd3_sizeinfo makes the FW ignore the PDS program entirely, and
    * the clear is performed purely via USC clear registers + ISP. */
   state.pds_shader_task_offset = 0U;
   state.uni_tex_code_offset = 0U;
   state.tex_state_data_offset = 0U;
   state.common_ptr = 0U;

   /* ---- Surface/render params → PBE words [ref :1244]. ---- */
   memset(&surf_params, 0, sizeof(surf_params));
   {
      /* Channel swizzle for BGRA memory: the PBE source is RGBA (clear
       * registers), so map B<-R, R<-B (upstream uses pvr_get_format_swizzle,
       * which is not linked into pvrgl; B8G8R8A8 == {Z,Y,X,W} = {2,1,0,3}). */
      surf_params.swizzle[0] = 2; /* B <- source Z (blue from red slot) */
      surf_params.swizzle[1] = 1; /* G <- source Y */
      surf_params.swizzle[2] = 0; /* R <- source X */
      surf_params.swizzle[3] = 3; /* A <- source W */

      surf_params.is_normalized = true;
      surf_params.nr_components = 4;

      pvr_arch_pbe_get_src_format_and_gamma(
         VK_FORMAT_B8G8R8A8_UNORM,
         PVR_PBE_GAMMA_NONE,
         false,
         &surf_params.source_format,
         &surf_params.gamma);

      /* Color fill of normalized 8888 uses an 8bpc source [ref :1070]. */
      surf_params.source_format = ROGUE_PBESTATE_SOURCE_FORMAT_8_PER_CHANNEL;
      surf_params.pbe_packmode = pvr_arch_get_pbe_packmode(
         VK_FORMAT_B8G8R8A8_UNORM);

      surf_params.addr.addr = dst->dev_addr;
      surf_params.mem_layout = PVR_MEMLAYOUT_LINEAR;
      surf_params.stride = dst->stride;
      surf_params.depth = 1U;
      surf_params.width = dst->base.width0;
      surf_params.height = dst->base.height0;
      surf_params.z_only_render = false;
      surf_params.down_scale = false;

      memset(&render_params, 0, sizeof(render_params));
      render_params.min_x_clip = 0U;
      render_params.min_y_clip = 0U;
      render_params.max_x_clip = dst->base.width0 ? dst->base.width0 - 1U : 0U;
      render_params.max_y_clip = dst->base.height0 ? dst->base.height0 - 1U
                                                   : 0U;
      render_params.source_start = PVR_PBE_STARTPOS_BIT0;
      render_params.slice = 0U;
      render_params.mrt_index = 0U;

      /* UU8888 pixel source = 1 USC output register per pixel. */
      state.usc_pixel_width = 1U;

      pvr_arch_pbe_pack_state(dev_info, &surf_params, &render_params,
                              pbe_words, &regs->pbe_wordx_mrty[0]);


   }

   /* ---- Pixel-event PDS program [ref :1152]. ---- */
   memset(&event_program, 0, sizeof(event_program));
   event_program.emit_words = pbe_words;
   event_program.num_emit_word_pairs = 1U;

   pvr_pds_setup_doutu(&event_program.task_control,
                       tq->eot[0].bo.heap_offset,
                       tq->eot[0].temps,
                       ROGUE_PDSINST_DOUTU_SAMPLE_RATE_INSTANCE,
                       false);

   pvr_pds_set_sizes_pixel_event(&event_program, dev_info);

   {
      uint32_t *staging =
         calloc(event_program.code_size + event_program.data_size, 4);
      if (!staging)
         return VK_ERROR_OUT_OF_HOST_MEMORY;

      pvr_pds_generate_pixel_event_data_segment(&event_program, staging,
                                                dev_info);
      pvr_pds_generate_pixel_event_code_segment(
         &event_program, staging + event_program.data_size, dev_info);

      {
         char hx[512]; size_t off = 0;
         size_t nw = (event_program.code_size + event_program.data_size);
         for (size_t i = 0; i < nw && off < sizeof(hx) - 12; i++)
            off += snprintf(hx + off, sizeof(hx) - off, "%08x ", staging[i]);
         mesa_logi("pvrgl: EVPDS dsize=%u csize=%u words=%u emit_pairs=%u %s",
                   event_program.data_size, event_program.code_size,
                   (unsigned)nw, event_program.num_emit_word_pairs, hx);
      }

      /* Event PDS program must live on the PDS code/data heap: the
       * EVENT_PIXEL_PDS_CODE/DATA addr fields are offsets relative to the
       * PDS heap base (upstream pvr_pds_upload uses device->suballoc_pds and
       * subtracts pds_heap->base_addr). General-heap offsets made the FW
       * fetch the event program from a bogus address -> context reset. */
      /* Code must start at a 16-byte-aligned offset: the
       * EVENT_PIXEL_PDS_CODE addr field is 28-bit with shift=4 (16-byte
       * address units), so an unaligned code offset truncates on the
       * FW side and it executes the tail of the data segment as code
       * (upstream pvr_gpu_upload_pds: code_offset = ALIGN_POT(data_size,
       * code_alignment)). */
      code_off =
         ALIGN_POT(event_program.data_size * 4,
                   ROGUE_CR_EVENT_PIXEL_PDS_CODE_ADDR_ALIGNMENT);
      vk = pvrgl_upload(screen,
                        screen->heaps->pds_heap,
                        staging,
                        (event_program.code_size + event_program.data_size) * 4,
                        16,
                        &event_pds_bo);
      free(staging);
      if (vk != VK_SUCCESS)
         return vk;

      /* Relocate the code segment to the aligned offset within the BO. */
      memcpy((uint8_t *)event_pds_bo.bo->map + code_off,
             (uint8_t *)event_pds_bo.bo->map + event_program.data_size * 4,
             event_program.code_size * 4);
      mesa_logi("pvrgl: EVPDS code_off=0x%x data_size=%u code_size=%u",
                code_off, event_program.data_size, event_program.code_size);
   }

   pvr_csb_pack (&regs->event_pixel_pds_info, CR_EVENT_PIXEL_PDS_INFO, reg) {
      reg.temp_stride = 0U;
      reg.const_size =
         DIV_ROUND_UP(event_program.data_size,
                      ROGUE_CR_EVENT_PIXEL_PDS_INFO_CONST_SIZE_UNIT_SIZE);
      reg.usc_sr_size =
         DIV_ROUND_UP(1 * PVR_STATE_PBE_DWORDS,
                      ROGUE_CR_EVENT_PIXEL_PDS_INFO_USC_SR_SIZE_UNIT_SIZE);
   }
   /* CR_EVENT_PIXEL_PDS_CODE/DATA addr fields are 28-bit OFFSETS (shift=4,
    * cr.xml: "This is an offset actually") — heap-relative like upstream's
    * pds_upload.data_offset. Passing the absolute dev_addr truncated to
    * garbage -> FW event-program jump fault -> FWCCB_CMD_CONTEXT_RESET
    * (0x2abc0069) -> job dies, no pixels. */
   pvr_csb_pack (&regs->event_pixel_pds_data, CR_EVENT_PIXEL_PDS_DATA, reg) {
      reg.addr = PVR_DEV_ADDR(event_pds_bo.heap_offset);
   }
   pvr_csb_pack (&regs->event_pixel_pds_code, CR_EVENT_PIXEL_PDS_CODE, reg) {
      reg.addr = PVR_DEV_ADDR(event_pds_bo.heap_offset + code_off);
   }

   pvrgl_setup_hwbg_object(&state);

   /* ---- ISP tiles [ref :1370]. ---- */
   {
      uint32_t isp_tiles_in_flight;

      pvr_csb_pack (&regs->isp_mtile_size, CR_ISP_MTILE_SIZE, reg) {
         reg.x = state.width_in_tiles;
         reg.y = state.height_in_tiles;
      }

      pvr_csb_pack (&regs->isp_render_origin, CR_ISP_RENDER_ORIGIN, reg) {
         reg.x = state.origin_x_in_tiles;
         reg.y = state.origin_y_in_tiles;
      }

      pvr_arch_setup_tiles_in_flight(dev_info,
                                     screen->runtime_info,
                                     ROGUE_CR_ISP_AA_MODE_TYPE_AA_NONE,
                                     state.usc_pixel_width,
                                     false,
                                     0,
                                     &isp_tiles_in_flight,
                                     &regs->usc_pixel_output_ctrl);

      pvr_csb_pack (&regs->isp_ctl, CR_ISP_CTL, reg) {
         reg.process_empty_tiles = true;
      }
      regs->isp_ctl |= isp_tiles_in_flight;

      pvr_csb_pack (&regs->isp_render, CR_ISP_RENDER, reg) {
         reg.mode_type = ROGUE_CR_ISP_RENDER_MODE_TYPE_FAST_SCALE;
      }
   }

   /* ---- Control stream [ref :4045, fill-only single mapping]. -------- */
   {
      const uint32_t prim_blk_bytes = pvrgl_prim_block_size(dev_info, 1U);
      const uint32_t term_bytes = sipf2 ? 4U
                                        : PVR_DW_TO_BYTES(
                                             pvr_cmd_length(IPF_CONTROL_STREAM));
      const uint32_t total_bytes = prim_blk_bytes + term_bytes + 16;
      uint32_t *cs_ptr, *blk_cs_ptr;

      vk = pvrgl_upload(screen,
                        screen->heaps->transfer_frag_heap,
                        NULL,
                        total_bytes,
                        8,
                        &cs_bo);
      if (vk != VK_SUCCESS)
         goto err_event_pds;

      cs_ptr = cs_bo.bo->map;
      blk_cs_ptr = cs_ptr;

      pvrgl_write_prim_block_fill(dev_info, &state,
                                  0, 0,
                                  dst->base.width0, dst->base.height0,
                                  &blk_cs_ptr);

      if (sipf2) {
         /* Byte granular terminate [ref :4546]. */
         uint8_t *bp = (uint8_t *)blk_cs_ptr;
         uint32_t tmp;

         pvr_csb_pack (&tmp, IPF_CONTROL_STREAM_TERMINATE_SIPF2, term);
         bp[(uintptr_t)bp & 3U] = tmp & 0xFF;
      } else {
         pvr_csb_pack (blk_cs_ptr, IPF_CONTROL_STREAM, word) {
            word.cs_type = ROGUE_IPF_CS_TYPE_TERM;
         }
      }

      /* FW addresses are heap-relative: subtract the heap base (upstream
       * pvr_arch_job_transfer.c:4143 does exactly this). Passing the absolute
       * device addr made the ISP read the control stream from a bogus
       * location -> clear silently wrote nothing. */
      pvr_csb_pack (&regs->isp_mtile_base, CR_ISP_MTILE_BASE, reg) {
         reg.addr = PVR_DEV_ADDR(cs_bo.dev_addr -
                                 screen->heaps->transfer_frag_heap->base_addr.addr);
      }

      if (sipf2 && PVR_HAS_FEATURE(dev_info, ipf_creq_pf)) {
         pvr_csb_pack (&regs->isp_rgn, CR_ISP_RGN_SIPF, isp_rgn) {
            isp_rgn.cs_size_ipf_creq_pf = 0U;
         }
      } else {
         pvr_csb_pack(&regs->isp_rgn, CR_ISP_RGN, isp_rgn);
      }
   }

   /* ---- Fragment screen [ref :3023]: the FW needs the render
    * dimensions in CR_FRAG_SCREEN or the ISP screen grid is degenerate
    * (xmax=ymax=0, sparse pixel output). ---- */
   if (PVR_HAS_FEATURE(dev_info, gpu_multicore_support)) {
      pvr_csb_pack (&regs->frag_screen, CR_FRAG_SCREEN, reg) {
         reg.xmax = dst->base.width0 ? dst->base.width0 - 1 : 0;
         reg.ymax = dst->base.height0 ? dst->base.height0 - 1 : 0;
      }
   }

   /* ---- fw stream pack [ref :5810]. ---- */
   cmd = &submit_info.cmds[0];
   memset(cmd, 0, sizeof(*cmd));
   {
      uint32_t *stream_ptr = (uint32_t *)cmd->fw_stream;

      stream_ptr += pvr_cmd_length(KMD_STREAM_HDR);

      memcpy(stream_ptr, &regs->pds_bgnd0_base, sizeof(regs->pds_bgnd0_base));
      stream_ptr += pvr_cmd_length(CR_PDS_BGRND0_BASE);
      memcpy(stream_ptr, &regs->pds_bgnd1_base, sizeof(regs->pds_bgnd1_base));
      stream_ptr += pvr_cmd_length(CR_PDS_BGRND1_BASE);
      memcpy(stream_ptr, &regs->pds_bgnd3_sizeinfo,
             sizeof(regs->pds_bgnd3_sizeinfo));
      stream_ptr += pvr_cmd_length(CR_PDS_BGRND3_SIZEINFO);
      memcpy(stream_ptr, &regs->isp_mtile_base, sizeof(regs->isp_mtile_base));
      stream_ptr += pvr_cmd_length(CR_ISP_MTILE_BASE);

      STATIC_ASSERT(ARRAY_SIZE(regs->pbe_wordx_mrty) == 9U);
      memcpy(stream_ptr, regs->pbe_wordx_mrty, sizeof(regs->pbe_wordx_mrty));
      stream_ptr += 9U * 2U;

      *stream_ptr++ = regs->isp_bgobjvals;
      *stream_ptr++ = regs->usc_pixel_output_ctrl;
      *stream_ptr++ = regs->usc_clear_register0;
      *stream_ptr++ = regs->usc_clear_register1;
      *stream_ptr++ = regs->usc_clear_register2;
      *stream_ptr++ = regs->usc_clear_register3;
      *stream_ptr++ = regs->isp_mtile_size;
      *stream_ptr++ = regs->isp_render_origin;
      *stream_ptr++ = regs->isp_ctl;
      *stream_ptr++ = regs->isp_aa;
      *stream_ptr++ = regs->event_pixel_pds_info;
      *stream_ptr++ = regs->event_pixel_pds_code;
      *stream_ptr++ = regs->event_pixel_pds_data;
      *stream_ptr++ = regs->isp_render;
      *stream_ptr++ = regs->isp_rgn;

      /* Kernel gates frag_screen on ITS OWN feature table (dev-query), and
       * mesa's dev_info mirrors that same table, so gating on the identical
       * feature macro keeps the packed stream length in lockstep with what
       * pvr_stream_process_1() will consume. (BXM-4-64 MC1 reports
       * gpu_multicore_support=1 -> kernel consumes frag_screen -> we must
       * emit it or the parse runs 4 bytes short -> EINVAL.) */
      if (PVR_HAS_FEATURE(dev_info, gpu_multicore_support)) {
         *stream_ptr++ = regs->frag_screen;
      }
      mesa_logi("pvrgl: feats multicore=%d xttop=%d sipf=%d sipf2=%d ipf_creq_pf=%d",
                PVR_HAS_FEATURE(dev_info, gpu_multicore_support),
                PVR_HAS_FEATURE(dev_info, xt_top_infrastructure),
                PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format),
                PVR_HAS_FEATURE(dev_info, simple_internal_parameter_format_v2),
                PVR_HAS_FEATURE(dev_info, ipf_creq_pf));

      cmd->fw_stream_len = (uint8_t *)stream_ptr - (uint8_t *)cmd->fw_stream;
      assert(cmd->fw_stream_len <= ARRAY_SIZE(cmd->fw_stream));

      /* KMD stream header [ref kernel pvr_stream_process]: first u32 is the
       * total stream length (header included), second u32 must be zero.
       * The parser validates main_stream_len >= 8 && <= stream_size. */
      {
         uint32_t *hdr32 = (uint32_t *)cmd->fw_stream;
         hdr32[0] = cmd->fw_stream_len;
         hdr32[1] = 0U;
         mesa_logi("pvrgl: TQ stream len=%u hdr=[%08x %08x %08x %08x]",
                   cmd->fw_stream_len, hdr32[0], hdr32[1], hdr32[2], hdr32[3]);
         /* Full stream hex dump for fault analysis. */
         {
            char hexbuf[1024];
            size_t off = 0;
            uint32_t *p = (uint32_t *)cmd->fw_stream;
            size_t nw = cmd->fw_stream_len / 4;
            for (size_t i = 0; i < nw && off < sizeof(hexbuf) - 12; i++)
               off += snprintf(hexbuf + off, sizeof(hexbuf) - off,
                               "%08x ", p[i]);
            hexbuf[off] = 0;
            mesa_logi("pvrgl: STREAM %s", hexbuf);
            mesa_logi("pvrgl: PBE pbe_words0=0x%08x pbe_words1=0x%08x",
                      pbe_words[0], pbe_words[1]);
            mesa_logi("pvrgl: PDS event dev=0x%llx off=0x%llx cs dev=0x%llx off=0x%llx eot0 dev=0x%llx off=0x%llx",
                      (unsigned long long)event_pds_bo.dev_addr,
                      (unsigned long long)event_pds_bo.heap_offset,
                      (unsigned long long)cs_bo.dev_addr,
                      (unsigned long long)cs_bo.heap_offset,
                      (unsigned long long)tq->eot[0].bo.dev_addr,
                      (unsigned long long)tq->eot[0].bo.heap_offset);
         }
      }
   }

   mesa_logi("pvrgl: REGS mtile_base=0x%llx mtile_size=0x%x rgn_origin=0x%x ctl=0x%x aa=0x%x",
            (unsigned long long)regs->isp_mtile_base,
            regs->isp_mtile_size, regs->isp_render_origin, regs->isp_ctl,
            regs->isp_aa);
   mesa_logi("pvrgl: REGS bgnd0=0x%llx bgnd1=0x%llx bgnd3=0x%llx",
            (unsigned long long)regs->pds_bgnd0_base,
            (unsigned long long)regs->pds_bgnd1_base,
            (unsigned long long)regs->pds_bgnd3_sizeinfo);
   mesa_logi("pvrgl: REGS pds_info=0x%x pds_code=0x%x pds_data=0x%x isp_render=0x%x",
            regs->event_pixel_pds_info, regs->event_pixel_pds_code,
            regs->event_pixel_pds_data, regs->isp_render);
   mesa_logi("pvrgl: REGS usc_pixout=0x%x bgobjvals=0x%x frag_screen=0x%x",
            regs->usc_pixel_output_ctrl, regs->isp_bgobjvals,
            regs->frag_screen);
   mesa_logi("pvrgl: MRY0=0x%llx MRY1=0x%llx MRY2=0x%llx",
            (unsigned long long)regs->pbe_wordx_mrty[0],
            (unsigned long long)regs->pbe_wordx_mrty[1],
            (unsigned long long)regs->pbe_wordx_mrty[2]);

   /* ---- Submit (async; caller verifies via CPU map polling). ---- */
   /* NOTE: no memset here — cmds[0] was fully populated above; zeroing the
    * struct now would wipe fw_stream_len and the packed stream. */
   submit_info.frame_num = 0U;
   submit_info.job_num = 0U;
   submit_info.wait = NULL;
   submit_info.cmd_count = 1U;

   vk = screen->ws->ops->transfer_submit(screen->tctx, &submit_info,
                                         dev_info, NULL);
   if (vk != VK_SUCCESS)
      mesa_logw("pvrgl: transfer_submit failed %d", vk);
   else
      mesa_logi("pvrgl: TQ clear submitted ok");

err_event_pds:
   /* Keep the BOs alive briefly on success so the async job's references
    * remain valid until the caller observes completion via its map poll.
    */
   if (vk == VK_SUCCESS) {
      /* Leaked deliberately until pvrgl_resource destroy path grows a
       * deferred-release queue; acceptable for M2 validation.
       */
      return VK_SUCCESS;
   }

   pvrgl_bo_free(screen, &cs_bo);
   pvrgl_bo_free(screen, &event_pds_bo);
   return vk;
}
