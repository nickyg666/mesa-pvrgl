/* pvrgl_resource.c — resources backed by winsys BOs + VMA mappings.
 *
 * M2-prep: every resource gets a kernel BO (CPU-accessible), a GPU VMA in
 * the general heap, and therefore a device address the TQ/PBE can target.
 */
#include "pvrgl_screen.h"
#include "pvrgl_resource.h"
#include "pvrgl_context.h"

#include "pipe/p_context.h"
#include "util/u_memory.h"
#include "util/format/u_format.h"
#include "util/u_math.h"
#include "util/log.h"

#include "imagination/vulkan/winsys/pvr_winsys.h"

struct pvrgl_resource *
pvrgl_resource(struct pipe_resource *res)
{
   return (struct pvrgl_resource *)res;
}

static struct pipe_resource *
pvrgl_resource_create(struct pipe_screen *pscreen,
                      const struct pipe_resource *tmpl)
{
   struct pvrgl_screen *screen = (struct pvrgl_screen *)pscreen;
   struct pvrgl_resource *res;
   VkResult vk;

   if (!screen->winsys_ok)
      return NULL;

   res = CALLOC_STRUCT(pvrgl_resource);
   if (!res)
      return NULL;

   res->base = *tmpl;
   res->base.screen = pscreen;
   p_atomic_set(&res->base.reference.count, 1);

   const uint64_t size = (tmpl->target == PIPE_BUFFER)
      ? (uint64_t)tmpl->width0
      : ((uint64_t)tmpl->height0 *
         util_format_get_stride(tmpl->format, tmpl->width0));

   vk = screen->ws->ops->buffer_create(screen->ws,
                                       align64(size ? size : 4096, 4096),
                                       4096,
                                       PVR_WINSYS_BO_TYPE_GPU,
                                       PVR_WINSYS_BO_FLAG_CPU_ACCESS,
                                       &res->bo);
   if (vk != VK_SUCCESS) {
      mesa_logw("pvrgl: buffer_create failed: %d", vk);
      goto err_free;
   }

   vk = screen->ws->ops->heap_alloc(screen->heaps->general_heap,
                                    align64(size ? size : 4096, 4096),
                                    4096,
                                    &res->vma);
   if (vk != VK_SUCCESS) {
      mesa_logw("pvrgl: heap_alloc failed: %d", vk);
      goto err_bo;
   }

   {
      pvr_dev_addr_t addr;
      vk = screen->ws->ops->vma_map(res->vma, res->bo, 0,
                                    align64(size ? size : 4096, 4096),
                                    &addr);
      if (vk != VK_SUCCESS) {
         mesa_logw("pvrgl: vma_map failed: %d", vk);
         goto err_vma;
      }
      res->dev_addr = addr.addr;
   }

   if (tmpl->target == PIPE_BUFFER)
      res->stride = 0;
   else
      res->stride = util_format_get_stride(tmpl->format, tmpl->width0);

   mesa_logi("pvrgl: resource %s size=%llu dev_addr=0x%llx",
             tmpl->target == PIPE_BUFFER ? "buf" : "tex",
             (unsigned long long)size, (unsigned long long)res->dev_addr);

   return &res->base;

err_vma:
   screen->ws->ops->heap_free(res->vma);
err_bo:
   screen->ws->ops->buffer_destroy(res->bo);
err_free:
   FREE(res);
   return NULL;
}

static void
pvrgl_resource_destroy(struct pipe_screen *pscreen,
                       struct pipe_resource *pres)
{
   struct pvrgl_screen *screen = (struct pvrgl_screen *)pscreen;
   struct pvrgl_resource *res = pvrgl_resource(pres);

   if (res->vma) {
      screen->ws->ops->vma_unmap(res->vma);
      screen->ws->ops->heap_free(res->vma);
   }
   if (res->bo)
      screen->ws->ops->buffer_destroy(res->bo);
   FREE(res);
}

/* ---- transfers (CPU mapping) ---------------------------------------- */

struct pvrgl_transfer {
   struct pipe_transfer base;
};

static void *
pvrgl_transfer_map(struct pipe_context *pctx,
                   struct pipe_resource *pres,
                   unsigned level,
                   unsigned usage,
                   const struct pipe_box *box,
                   struct pipe_transfer **ptx)
{
   struct pvrgl_screen *screen = (struct pvrgl_screen *)pctx->screen;
   struct pvrgl_resource *res = pvrgl_resource(pres);
   struct pvrgl_transfer *tx;
   VkResult vk;

   tx = CALLOC_STRUCT(pvrgl_transfer);
   if (!tx)
      return NULL;

   if (!res->bo->map) {
      vk = screen->ws->ops->buffer_map(res->bo, NULL);
      if (vk != VK_SUCCESS) {
         FREE(tx);
         return NULL;
      }
   }

   {
      const unsigned bpp = util_format_get_blocksize(pres->format);
      tx->base.resource = pres;
      tx->base.level = level;
      tx->base.box = *box;
      tx->base.stride = pres->target == PIPE_BUFFER
         ? 0 : util_format_get_stride(pres->format, pres->width0);
      tx->base.layer_stride = pres->target == PIPE_BUFFER
         ? 0 : (uint64_t)tx->base.stride * pres->height0;

      uint8_t *map = res->bo->map;
      if (pres->target == PIPE_BUFFER) {
         map += box->x;
      } else {
         map += box->y * tx->base.stride + box->x * bpp;
      }

      *ptx = &tx->base;
      return map;
   }
}

static void
pvrgl_transfer_unmap(struct pipe_context *pctx, struct pipe_transfer *ptx)
{
   struct pvrgl_transfer *tx = (struct pvrgl_transfer *)ptx;
   FREE(tx);
}

void
pvrgl_context_init_resource_functions(struct pipe_context *pctx)
{
   pctx->buffer_map = pvrgl_transfer_map;
   pctx->buffer_unmap = pvrgl_transfer_unmap;
   pctx->texture_map = pvrgl_transfer_map;
   pctx->texture_unmap = pvrgl_transfer_unmap;
   pctx->transfer_flush_region = NULL;
   pctx->buffer_subdata = NULL;
   pctx->texture_subdata = NULL;
}

void
pvrgl_screen_init_resource_functions(struct pipe_screen *pscreen)
{
   pscreen->resource_create = pvrgl_resource_create;
   pscreen->resource_destroy = pvrgl_resource_destroy;
}
