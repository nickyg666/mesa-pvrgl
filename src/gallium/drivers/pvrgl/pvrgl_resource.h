/* pvrgl_resource.h — resources backed by winsys BOs + VMA mappings. */
#ifndef PVRGL_RESOURCE_H
#define PVRGL_RESOURCE_H

#include "pipe/p_state.h"

struct pvr_winsys_bo;
struct pvr_winsys_vma;

struct pvrgl_resource {
   struct pipe_resource base;

   struct pvr_winsys_bo *bo;
   struct pvr_winsys_vma *vma;
   uint64_t dev_addr;
   uint32_t stride; /* bytes per row for 2D */
};

struct pvrgl_resource *
pvrgl_resource(struct pipe_resource *res);

void
pvrgl_context_init_resource_functions(struct pipe_context *pctx);

void
pvrgl_screen_init_resource_functions(struct pipe_screen *pscreen);

#endif /* PVRGL_RESOURCE_H */
