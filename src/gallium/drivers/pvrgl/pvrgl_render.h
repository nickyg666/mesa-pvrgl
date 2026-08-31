/* pvrgl_render.h — M3 hardware render path (HWRT dataset + RENDER ctx). */
#ifndef PVRGL_RENDER_H
#define PVRGL_RENDER_H

#include <vulkan/vulkan.h>

#include <stdint.h>

struct pvrgl_screen;
struct pvrgl_render;
struct pvrgl_bo;
struct pipe_resource;

VkResult
pvrgl_render_init(struct pvrgl_screen *screen, struct pvrgl_render **out);

void
pvrgl_render_fini(struct pvrgl_render *r);

/* Submit a GEOMETRY + FRAGMENT bg-clear job pair against the render
 * context at (width, height). Binds (and caches) a matching HWRT dataset
 * and rewrites the bgnd clear-color const BO before submitting. */
VkResult
pvrgl_render_submit(struct pvrgl_render *r,
                    const struct pvrgl_bo *rt_bo,
                    VkFormat rt_format,
                    uint32_t width, uint32_t height,
                    uint32_t clear_dword);

/* Production clear: pack RGBA-float color for res->format, bind target,
 * submit. Returns VK_ERROR_FORMAT_NOT_SUPPORTED for formats the render
 * path can't pack (caller falls back to the TQ path). */
VkResult
pvrgl_render_clear(struct pvrgl_screen *screen, struct pipe_resource *res,
                   const float color[4]);

/* Env-guarded (PVRGL_RENDER_TEST=1) full render-path smoke test. */
VkResult
pvrgl_render_selftest(struct pvrgl_screen *screen);

#endif /* PVRGL_RENDER_H */
