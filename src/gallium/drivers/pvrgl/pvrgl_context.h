/* pvrgl_context.h — pipe_context for the PowerVR Gallium driver. */
#ifndef PVRGL_CONTEXT_H
#define PVRGL_CONTEXT_H

#include "pipe/p_context.h"
#include "pvrgl_screen.h"

struct pvrgl_context {
   struct pipe_context base;
   struct pvrgl_screen *screen;

   /* Bound color surface for M2 clears. */
   struct pipe_resource *color_res;
};

#endif /* PVRGL_CONTEXT_H */
