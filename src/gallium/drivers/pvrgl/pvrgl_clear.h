/* pvrgl_clear.h */
#ifndef PVRGL_CLEAR_H
#define PVRGL_CLEAR_H

#include "pipe/p_context.h"
#include "pipe/p_defines.h"

void
pvrgl_clear(struct pipe_context *pctx, unsigned buffers, unsigned width,
            uint8_t viewport_scissor,
            const struct pipe_scissor_state *scissor_state,
            const union pipe_color_union *color, double depth,
            unsigned stencil);

#endif /* PVRGL_CLEAR_H */
