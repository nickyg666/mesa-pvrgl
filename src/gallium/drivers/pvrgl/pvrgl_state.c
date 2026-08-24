/* pvrgl_state.c — minimal state-tracker hooks. */
#include "pvrgl_context.h"
#include "pvrgl_resource.h"
#include "pvrgl_state.h"
#include "pvrgl_clear.h"

#include "util/u_inlines.h"

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

void
pvrgl_context_init_state_functions(struct pipe_context *pctx)
{
   pctx->set_framebuffer_state = pvrgl_set_framebuffer_state;
   pctx->set_viewport_states = pvrgl_set_viewport_states;
   pctx->set_scissor_states = pvrgl_set_scissor_states;
   pctx->clear = pvrgl_clear;
}
