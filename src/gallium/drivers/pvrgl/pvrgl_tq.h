/* pvrgl_tq.h — transfer-queue hardware clear backend + shared BO helpers. */
#ifndef PVRGL_TQ_H
#define PVRGL_TQ_H

#include <vulkan/vulkan.h>

#include <stdint.h>

struct pvrgl_screen;
struct pvrgl_resource;
struct pvrgl_tq;
struct pvr_winsys_heap;
struct pvr_winsys_vma;

/* Shared GPU BO wrapper: winsys bo + vma + full device address. */
struct pvrgl_bo {
   struct pvr_winsys_bo *bo;
   struct pvr_winsys_vma *vma;
   uint64_t heap_offset;
   /* Full device address (heap base + offset) as returned by vma_map. */
   uint64_t dev_addr;
};

/* Allocate + map a BO on `heap` (optionally copying `data`). `flags` are
 * PVR_WINSYS_BO_FLAG_*; `vma_out` optionally returns the vma (needed for
 * free_list_create). */
VkResult
pvrgl_upload_flags(struct pvrgl_screen *screen,
                   struct pvr_winsys_heap *heap,
                   const void *data,
                   uint32_t size,
                   uint32_t align,
                   uint32_t flags,
                   struct pvrgl_bo *out,
                   struct pvr_winsys_vma **vma_out);

VkResult
pvrgl_upload(struct pvrgl_screen *screen,
             struct pvr_winsys_heap *heap,
             const void *data,
             uint32_t size,
             uint32_t align,
             struct pvrgl_bo *out);

void
pvrgl_bo_free(struct pvrgl_screen *screen, struct pvrgl_bo *gbo);

VkResult
pvrgl_tq_init(struct pvrgl_screen *screen, struct pvrgl_tq **tq_out);

void
pvrgl_tq_finish(struct pvrgl_screen *screen, struct pvrgl_tq *tq);

/* Submit a full-surface TQ fill/clear of `dst` with `color` (RGBA floats).
 * Asynchronous: caller observes completion by polling the BO CPU map.
 */
VkResult
pvrgl_tq_clear_surface(struct pvrgl_screen *screen,
                       struct pvrgl_resource *dst,
                       const float color[4]);

#endif /* PVRGL_TQ_H */
