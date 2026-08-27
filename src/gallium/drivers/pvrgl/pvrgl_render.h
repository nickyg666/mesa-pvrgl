/* pvrgl_render.h — M3 hardware render path (HWRT dataset + RENDER ctx). */
#ifndef PVRGL_RENDER_H
#define PVRGL_RENDER_H

#include <vulkan/vulkan.h>

#include <stdint.h>

struct pvrgl_screen;
struct pvrgl_render;
struct pvrgl_bo;

VkResult
pvrgl_render_init(struct pvrgl_screen *screen, struct pvrgl_render **out);

void
pvrgl_render_fini(struct pvrgl_render *r);

/* Submit a GEOMETRY + FRAGMENT job pair against the render context.
 * P1: empty geometry (terminate-only ctrl stream) — proves the render
 * pipeline accepts the HWRT dataset + context + streams. */
VkResult
pvrgl_render_test_submit(struct pvrgl_render *r,
                         const struct pvrgl_bo *rt_bo,
                         VkFormat rt_format);

/* Env-guarded (PVRGL_RENDER_TEST=1) full render-path smoke test. */
VkResult
pvrgl_render_selftest(struct pvrgl_screen *screen);

#endif /* PVRGL_RENDER_H */
