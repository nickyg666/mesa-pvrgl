/* pvrgl_state.c — minimal state-tracker hooks. */
#include "pvrgl_context.h"
#include "pvrgl_resource.h"
#include "pvrgl_state.h"
#include "pvrgl_clear.h"

#include "util/u_inlines.h"
#include "util/u_math.h"
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
   mesa_logi("pvrgl: blit src=%p dst=%p srcfmt=%s dstfmt=%s sbox=%dx%d@%d,%d",
             info->src.resource, info->dst.resource,
             util_format_name(info->src.format),
             util_format_name(info->dst.format),
             info->src.box.width, info->src.box.height,
             info->src.box.x, info->src.box.y);
   if (!info->src.resource || !info->dst.resource)
      return;

   const int sw = info->src.box.width, sh = info->src.box.height;
   const unsigned bs = util_format_get_blocksize(info->src.format);
   if (bs != util_format_get_blocksize(info->dst.format) ||
       abs(sw) != abs(info->dst.box.width) ||
       abs(sh) != abs(info->dst.box.height) ||
       sw == 0 || sh == 0 || info->dst.box.width < 0 ||
       info->dst.box.height < 0) {
      mesa_logw("pvrgl: blit dropped: src=%s(%dx%d@%d,%u bs%u) dst=%s(%dx%d@%d,%u bs%u) mask=%x filter=%d",
                util_format_name(info->src.format),
                sw, sh, info->src.box.x, info->src.box.y, bs,
                util_format_name(info->dst.format),
                info->dst.box.width, info->dst.box.height,
                info->dst.box.x, info->dst.box.y,
                util_format_get_blocksize(info->dst.format),
                info->mask, info->filter);
      return;
   }
   /* Signed src boxes (gallium: negative w/h = flip, legal for src).
    * Src row/col for dst index j: h>0 -> base+j ; h<0 -> base-1-j. */
   const unsigned w = (unsigned)abs(sw), h = (unsigned)abs(sh);
   const bool flip_x = sw < 0, flip_y = sh < 0;

   const bool src_bgra =
      info->src.format == PIPE_FORMAT_BGRA8888_UNORM ||
      info->src.format == PIPE_FORMAT_BGRX8888_UNORM;
   const bool dst_bgra =
      info->dst.format == PIPE_FORMAT_BGRA8888_UNORM ||
      info->dst.format == PIPE_FORMAT_BGRX8888_UNORM;
   const bool swap_rb = (src_bgra != dst_bgra);

   /* Twiddled source surfaces (TQ hw clear writes Morton order) need
    * per-pixel de-twiddle. Mirrors usclib Twiddle2D: common bits interleave
    * y-even/x-odd, then remaining x bits, then remaining y bits. Works for
    * ANY box: Morton offsets are absolute in the surface, and src_map is
    * box-relative, so back out the box offset to reach the BO base. */
   struct pvrgl_resource *src_pres = pvrgl_resource(info->src.resource);
   const bool src_twiddled = src_pres->twiddled;
   mesa_logi("pvrgl: blit src=%p twiddled=%d box=%dx%d filter=%d",
             info->src.resource, src_twiddled,
             info->src.box.width, info->src.box.height, info->filter);
   uint32_t tw_xbits = 0, tw_ybits = 0, tw_common_bits = 0;
   if (src_twiddled) {
      if (bs != 4) {
         mesa_logw("pvrgl: blit from twiddled surface only supports 32bpp");
         return;
      }
      tw_xbits = util_logbase2(src_pres->base.width0);
      tw_ybits = util_logbase2(src_pres->base.height0);
      tw_common_bits = MIN2(tw_xbits, tw_ybits);
   }

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

   uint8_t *src_base = src_map -
      ((size_t)info->src.box.y * (size_t)src_tx->stride +
       (size_t)info->src.box.x * 4);
   if (src_twiddled) {
      /* DEBUG: raw BO dump — what did the TQ clear actually write? */
      if (debug_get_bool_option("PVRGL_DUMP_SRC", false)) {
         const uint32_t *raw = (const uint32_t *)src_base;
         unsigned red = 0, other = 0;
         mesa_logi("pvrgl: SRC BO dump (first 64 u32, red=0xff0000ff):");
         for (unsigned i = 0; i < 64; i += 8) {
            mesa_logi("  [%3u] %08x %08x %08x %08x %08x %08x %08x %08x",
                      i, raw[i], raw[i+1], raw[i+2], raw[i+3],
                      raw[i+4], raw[i+5], raw[i+6], raw[i+7]);
         }
         for (unsigned i = 0; i < 16384; i++) {
            if (raw[i] == 0xff0000ffu) red++;
            else if (raw[i] != 0) other++;
         }
         mesa_logi("  total: red=%u nonred_nonzero=%u (of 16384)", red, other);
      }
      for (unsigned y = 0; y < h; y++) {
         uint8_t *d = dst_map + (unsigned)y * dst_tx->stride;
         for (unsigned x = 0; x < w; x++) {
            const uint32_t ux = flip_x
               ? (uint32_t)(info->src.box.x - 1 - (int)x)
               : (uint32_t)(info->src.box.x + (int)x);
            const uint32_t uy = flip_y
               ? (uint32_t)(info->src.box.y - 1 - (int)y)
               : (uint32_t)(info->src.box.y + (int)y);
            uint32_t off = 0;
            for (unsigned b = 0; b < tw_common_bits; b++) {
               off |= ((uy >> b) & 1u) << (2u * b);
               off |= ((ux >> b) & 1u) << (2u * b + 1u);
            }
            for (unsigned b = tw_common_bits; b < tw_xbits; b++)
               off |= ((ux >> b) & 1u) << (tw_common_bits + b);
            for (unsigned b = tw_common_bits; b < tw_ybits; b++)
               off |= ((uy >> b) & 1u) << (tw_common_bits + b);
            const uint8_t *s = src_base + (size_t)off * 4;
            if (!swap_rb) {
               memcpy(d + x * 4, s, 4);
            } else {
               d[x * 4 + 0] = s[2];
               d[x * 4 + 1] = s[1];
               d[x * 4 + 2] = s[0];
               d[x * 4 + 3] = s[3];
            }
         }
      }
      goto out;
   }
   for (unsigned y = 0; y < h; y++) {
      const int src_row = flip_y
         ? info->src.box.y - 1 - (int)y
         : info->src.box.y + (int)y;
      uint8_t *s = src_base + (size_t)src_row * src_tx->stride;
      uint8_t *d = dst_map + (unsigned)y * dst_tx->stride;
      if (!swap_rb) {
         memcpy(d, s, (size_t)w * bs);
      } else {
         for (unsigned x = 0; x < w; x++) {
            const unsigned sx = flip_x ? w - 1 - x : x;
            d[x * 4 + 0] = s[sx * 4 + 2];
            d[x * 4 + 1] = s[sx * 4 + 1];
            d[x * 4 + 2] = s[sx * 4 + 0];
            d[x * 4 + 3] = s[sx * 4 + 3];
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
