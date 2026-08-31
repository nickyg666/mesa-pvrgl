/* pvrgl_clear.c — clear implementation.
 *
 * M2: full-surface hardware clear through the transfer queue. The bound
 * color surface (set via set_framebuffer_state) is cleared by a FILL TQ
 * job; completion is observed by polling the BO CPU map.
 */
#include "pvrgl_clear.h"
#include "pvrgl_context.h"
#include "pvrgl_resource.h"
#include "pvrgl_tq.h"
#include "pvrgl_render.h"

#include <vulkan/vulkan.h>

#include "util/log.h"

void
pvrgl_clear(struct pipe_context *pctx, unsigned buffers, unsigned width,
            uint8_t viewport_scissor,
            const struct pipe_scissor_state *scissor_state,
            const union pipe_color_union *color, double depth,
            unsigned stencil)
{
   struct pvrgl_context *ctx = (struct pvrgl_context *)pctx;
   static bool warned_no_fb = false;

   if (!(buffers & PIPE_CLEAR_COLOR0))
      return;

   if (!ctx->color_res) {
      if (!warned_no_fb) {
         mesa_logw("pvrgl: clear with no bound color surface (ignored)");
         warned_no_fb = true;
      }
      return;
   }

   mesa_logi("pvrgl: clear r=%.3f g=%.3f b=%.3f a=%.3f -> dev_addr=0x%llx",
             color->f[0], color->f[1], color->f[2], color->f[3],
             (unsigned long long)pvrgl_resource(ctx->color_res)->dev_addr);

   /* Native render path (HW bgnd clear) for 8888 formats; TQ fill
    * fallback for everything else. NOTE: the render path is still M3-WIP
    * (submits accepted, EOT paints nothing) — keep it opt-in until it
    * produces pixels. */
   static bool render_clear_on = false;
   static bool checked = false;
   if (!checked) {
      render_clear_on = getenv("PVRGL_RENDER_CLEAR") != NULL;
      checked = true;
   }

   if (render_clear_on &&
       pvrgl_render_clear(ctx->screen, ctx->color_res, color->f) ==
          VK_SUCCESS)
      return;

   pvrgl_tq_clear_surface(ctx->screen, pvrgl_resource(ctx->color_res),
                          color->f);
}
