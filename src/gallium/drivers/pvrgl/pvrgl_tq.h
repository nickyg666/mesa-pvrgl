/* pvrgl_tq.h — transfer-queue hardware clear backend. */
#ifndef PVRGL_TQ_H
#define PVRGL_TQ_H

#include <vulkan/vulkan.h>

#include <stdint.h>

struct pvrgl_screen;
struct pvrgl_resource;
struct pvrgl_tq;

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
