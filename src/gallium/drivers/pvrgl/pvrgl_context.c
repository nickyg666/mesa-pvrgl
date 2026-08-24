/* pvrgl_context.c — pipe_context implementation. */
#include "pvrgl_context.h"
#include "pvrgl_resource.h"
#include "pvrgl_state.h"

#include "util/u_memory.h"
#include "util/u_inlines.h"

static void
pvrgl_flush(struct pipe_context *pctx, struct pipe_fence_handle **fence,
            unsigned flags)
{
   /* M2: submissions are synchronous for now; nothing to do. */
   if (fence)
      *fence = NULL;
}

static void
pvrgl_destroy(struct pipe_context *pctx)
{
   struct pvrgl_context *ctx = (struct pvrgl_context *)pctx;

   FREE(ctx);
}

struct pipe_context *
pvrgl_create_context(struct pipe_screen *pscreen, void *priv, unsigned flags)
{
   struct pvrgl_screen *screen = (struct pvrgl_screen *)pscreen;
   struct pvrgl_context *ctx;

   if (!screen->winsys_ok)
      return NULL;

   ctx = CALLOC_STRUCT(pvrgl_context);
   if (!ctx)
      return NULL;

   ctx->screen = screen;

   ctx->base.screen = pscreen;
   ctx->base.priv = priv;
   ctx->base.destroy = pvrgl_destroy;
   ctx->base.flush = pvrgl_flush;

   pvrgl_context_init_resource_functions(&ctx->base);
   pvrgl_context_init_state_functions(&ctx->base);

   return &ctx->base;
}
