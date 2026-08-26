/* pvrgl_state.c — minimal state-tracker hooks. */
#include "pvrgl_context.h"
#include "pvrgl_resource.h"
#include "pvrgl_state.h"
#include "pvrgl_clear.h"

#include "util/u_inlines.h"
#include "util/format/u_format.h"
#include "util/log.h"

static void
pvrgl_set_framebuffer_state(struct pipe_context *pctx,
                            const struct pipe_framebuffer_state *fb)
{
   struct pvrgl_context *ctx = (struct pvrgl_context *)pctx;
   struct pipe_resource *new_res =
      (fb && fb->nr_cbufs > 0) ? fb->cbufs[0].texture : NULL;

   if (new_res)
      pipe_reference(NULL, &new_res->reference);
   pipe_resource_reference(&ctx->color_res, NULL);
   ctx->color_res = new_res;
}

static void
pvrgl_set_viewport_states(struct pipe_context *pctx,
                          unsigned start_slot,
                          unsigned num_viewports,
                          const struct pipe_viewport_state *states)
{
}

static void
pvrgl_set_scissor_states(struct pipe_context *pctx,
                         unsigned start_slot,
                         unsigned num_scissors,
                         const struct pipe_scissor_state *states)
{
}

/* CPU fallback blit: both surfaces are BO-backed and CPU-mappable, so a
 * straightforward copy covers the staging blits ReadPixels needs (M2). */
static void
pvrgl_blit(struct pipe_context *pctx, const struct pipe_blit_info *info)
{
   if (!info->src.resource || !info->dst.resource)
      return;

   const unsigned bs = util_format_get_blocksize(info->src.format);
   if (bs != util_format_get_blocksize(info->dst.format) ||
       info->src.box.width != info->dst.box.width ||
       info->src.box.height != info->dst.box.height) {
      mesa_logw("pvrgl: blit dropped: src=%s(%ux%u@%u,%u bs%u) dst=%s(%ux%u@%u,%u bs%u) mask=%x filter=%d",
                util_format_name(info->src.format),
                info->src.box.width, info->src.box.height,
                info->src.box.x, info->src.box.y, bs,
                util_format_name(info->dst.format),
                info->dst.box.width, info->dst.box.height,
                info->dst.box.x, info->dst.box.y,
                util_format_get_blocksize(info->dst.format),
                info->mask, info->filter);
      return;
   }

   const bool src_bgra =
      info->src.format == PIPE_FORMAT_BGRA8888_UNORM ||
      info->src.format == PIPE_FORMAT_BGRX8888_UNORM;
   const bool dst_bgra =
      info->dst.format == PIPE_FORMAT_BGRA8888_UNORM ||
      info->dst.format == PIPE_FORMAT_BGRX8888_UNORM;
   const bool swap_rb = (src_bgra != dst_bgra);

   struct pipe_transfer *src_tx, *dst_tx;
   uint8_t *src_map = pctx->texture_map(pctx, info->src.resource, 0,
                                        PIPE_MAP_READ, &info->src.box,
                                        &src_tx);
   uint8_t *dst_map = pctx->texture_map(pctx, info->dst.resource, 0,
                                        PIPE_MAP_WRITE, &info->dst.box,
                                        &dst_tx);
   if (!src_map || !dst_map) {
      mesa_logw("pvrgl: blit map failed");
      goto out;
   }

   const unsigned w = info->src.box.width;
   for (int y = 0; y < info->src.box.height; y++) {
      uint8_t *s = src_map + (unsigned)y * src_tx->stride;
      uint8_t *d = dst_map + (unsigned)y * dst_tx->stride;
      if (!swap_rb) {
         memcpy(d, s, (size_t)w * bs);
      } else {
         for (unsigned x = 0; x < w; x++) {
            d[x * 4 + 0] = s[x * 4 + 2];
            d[x * 4 + 1] = s[x * 4 + 1];
            d[x * 4 + 2] = s[x * 4 + 0];
            d[x * 4 + 3] = s[x * 4 + 3];
         }
      }
   }

out:
   if (dst_map)
      pctx->texture_unmap(pctx, dst_tx);
   if (src_map)
      pctx->texture_unmap(pctx, src_tx);
}

/* Minimal shader-state stubs: the state tracker compiles fixed-function
 * programs (e.g. for glReadPixels) and needs create/delete to survive.
 * No execution path exists yet — bind is a no-op until M3. */
#define PVRGL_SHADER_STATE_STUB(stage)                                        \
   static void *                                                              \
   pvrgl_create_##stage##_state(struct pipe_context *pctx,                    \
                                const struct pipe_shader_state *ss)           \
   {                                                                          \
      return (void *)1;                                                       \
   }                                                                          \
   static void                                                                \
   pvrgl_bind_##stage##_state(struct pipe_context *pctx, void *state)         \
   {                                                                          \
   }                                                                          \
   static void                                                                \
   pvrgl_delete_##stage##_state(struct pipe_context *pctx, void *state)       \
   {                                                                          \
   }

PVRGL_SHADER_STATE_STUB(vs)
PVRGL_SHADER_STATE_STUB(tcs)
PVRGL_SHADER_STATE_STUB(tes)
PVRGL_SHADER_STATE_STUB(gs)
PVRGL_SHADER_STATE_STUB(fs)

static void *
pvrgl_create_compute_state(struct pipe_context *pctx,
                           const struct pipe_compute_state *cs)
{
   return (void *)1;
}

static void
pvrgl_bind_compute_state(struct pipe_context *pctx, void *state)
{
}

static void
pvrgl_delete_compute_state(struct pipe_context *pctx, void *state)
{
}

void
pvrgl_context_init_state_functions(struct pipe_context *pctx)
{
   pctx->set_framebuffer_state = pvrgl_set_framebuffer_state;
   pctx->set_viewport_states = pvrgl_set_viewport_states;
   pctx->set_scissor_states = pvrgl_set_scissor_states;
   pctx->clear = pvrgl_clear;
   pctx->blit = pvrgl_blit;

   pctx->create_vs_state = pvrgl_create_vs_state;
   pctx->bind_vs_state = pvrgl_bind_vs_state;
   pctx->delete_vs_state = pvrgl_delete_vs_state;
   pctx->create_tcs_state = pvrgl_create_tcs_state;
   pctx->bind_tcs_state = pvrgl_bind_tcs_state;
   pctx->delete_tcs_state = pvrgl_delete_tcs_state;
   pctx->create_tes_state = pvrgl_create_tes_state;
   pctx->bind_tes_state = pvrgl_bind_tes_state;
   pctx->delete_tes_state = pvrgl_delete_tes_state;
   pctx->create_gs_state = pvrgl_create_gs_state;
   pctx->bind_gs_state = pvrgl_bind_gs_state;
   pctx->delete_gs_state = pvrgl_delete_gs_state;
   pctx->create_fs_state = pvrgl_create_fs_state;
   pctx->bind_fs_state = pvrgl_bind_fs_state;
   pctx->delete_fs_state = pvrgl_delete_fs_state;
   pctx->create_compute_state = pvrgl_create_compute_state;
   pctx->bind_compute_state = pvrgl_bind_compute_state;
   pctx->delete_compute_state = pvrgl_delete_compute_state;
}
