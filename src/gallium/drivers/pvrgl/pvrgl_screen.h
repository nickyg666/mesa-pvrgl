/* pvrgl_screen.h — internal screen structure for the PowerVR Gallium driver.
 *
 * pvrgl talks to the mainline powervr DRM kernel driver through the shared
 * imagination winsys layer (src/imagination/vulkan/winsys), the same code
 * path the Vulkan driver uses — no Vulkan runtime objects involved.
 */
#ifndef PVRGL_SCREEN_H
#define PVRGL_SCREEN_H

#include "pipe/p_screen.h"
#include "pipe/p_state.h"

#include <stdint.h>

/* Forward decls to avoid pulling vulkan headers into every consumer. */
struct pvr_winsys;
struct pvr_winsys_transfer_ctx;
struct pvr_winsys_heaps;
struct pvr_device_info;
struct pvr_device_runtime_info;
struct pvrgl_tq;
struct pvrgl_render;

struct pvrgl_screen {
   struct pipe_screen base;
   int fd;
   char driver_name[64];

   /* Winsys (shared with imagination vulkan driver). */
   struct pvr_winsys *ws;
   struct pvr_device_info *dev_info;
   struct pvr_device_runtime_info *runtime_info;
   struct pvr_winsys_heaps *heaps;

   /* Transfer (TQ) context: used for clears / blits / PBE ops. */
   struct pvr_winsys_transfer_ctx *tctx;
   struct pvrgl_tq *tq_priv;
   struct pvrgl_render *render_priv;

   bool winsys_ok;
};

struct pipe_context *
pvrgl_create_context(struct pipe_screen *pscreen, void *priv, unsigned flags);

#endif /* PVRGL_SCREEN_H */
