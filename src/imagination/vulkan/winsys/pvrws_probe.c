/* pvrws_probe.c — standalone imagination-winsys probe for the powervr DRM
 * kernel driver. Answers the M1-open question: does TRANSFER_FRAG context
 * creation succeed without the full Vulkan driver init sequence?
 *
 * Build: wired into vulkan/meson.build when with_gallium_pvrgl.
 * Run:   sudo ./pvrws_probe /dev/dri/renderD128
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <vulkan/vulkan.h>

#include "pvr_winsys.h"
#include "pvr_device_info.h"

#include "vk_alloc.h"

int
main(int argc, char **argv)
{
   const VkAllocationCallbacks *alloc = vk_default_allocator();
   const char *path = argc > 1 ? argv[1] : "/dev/dri/renderD128";
   struct pvr_winsys *ws = NULL;

   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);

   struct pvr_device_info *dev_info;
   struct pvr_device_runtime_info *runtime_info;
   struct pvr_winsys_heaps *heaps;
   struct pvr_winsys_transfer_ctx *tctx = NULL;
   struct pvr_winsys_bo *bo = NULL;
   struct pvr_winsys_vma *vma = NULL;
   VkResult res;
   int fail = 0;

#define CHECK(step, cond)                                                    \
   do {                                                                      \
      printf("PROBE %-28s %s\n", step, (cond) ? "PASS" : "FAIL");            \
      if (!(cond))                                                           \
         fail = 1;                                                           \
   } while (0)

   dev_info = calloc(1, sizeof(*dev_info));
   runtime_info = calloc(1, sizeof(*runtime_info));
   heaps = calloc(1, sizeof(*heaps));
   if (!dev_info || !runtime_info || !heaps)
      return 2;

   res = pvr_winsys_create(path, NULL, false, alloc, &ws);
   CHECK("open+winsys_create", res == VK_SUCCESS && ws);
   if (!ws)
      return fail ? 1 : 3;

   printf("PROBE page_size                 %u\n", (unsigned)ws->page_size);

   res = ws->ops->device_info_init(ws, dev_info, runtime_info);
   CHECK("device_info_init", res == VK_SUCCESS);
   if (res == VK_SUCCESS)
      printf("PROBE cores                    %u\n", runtime_info->core_count);

   ws->ops->get_heaps_info(ws, heaps);
   {
      const struct {
         const char *name;
         struct pvr_winsys_heap *h;
      } hs[] = {
         { "general", heaps->general_heap },
         { "pds", heaps->pds_heap },
         { "rgn_hdr", heaps->rgn_hdr_heap },
         { "transfer_frag", heaps->transfer_frag_heap },
         { "usc", heaps->usc_heap },
         { "vis_test", heaps->vis_test_heap },
      };
      for (unsigned i = 0; i < ARRAY_SIZE(hs); i++) {
         if (hs[i].h)
            printf("PROBE heap %-16s base=0x%llx size=0x%llx\n",
                   hs[i].name,
                   (unsigned long long)hs[i].h->base_addr.addr,
                   (unsigned long long)hs[i].h->size);
      }
      CHECK("heaps_enumerated", heaps->general_heap && heaps->transfer_frag_heap);
   }

   /* ---- The M1 blocker question -------------------------------------- */
   res = ws->ops->transfer_ctx_create(
      ws,
      &(struct pvr_winsys_transfer_ctx_create_info){
         .priority = PVR_WINSYS_CTX_PRIORITY_MEDIUM,
      },
      &tctx);
   CHECK("transfer_ctx_create(TQ)", res == VK_SUCCESS && tctx);
   if (res != VK_SUCCESS)
      printf("PROBE transfer_ctx_create VkResult=%d\n", res);

   /* ---- BO + VMA + CPU map round-trip -------------------------------- */
   res = ws->ops->buffer_create(ws, 4096, 4096,
                                PVR_WINSYS_BO_TYPE_GPU,
                                PVR_WINSYS_BO_FLAG_CPU_ACCESS, &bo);
   CHECK("buffer_create", res == VK_SUCCESS && bo);

   res = ws->ops->heap_alloc(heaps->general_heap, 4096, 4096, &vma);
   CHECK("heap_alloc(general)", res == VK_SUCCESS && vma);

   if (bo && vma) {
      pvr_dev_addr_t addr;

      res = ws->ops->vma_map(vma, bo, 0, 4096, &addr);
      CHECK("vma_map", res == VK_SUCCESS);
      if (res == VK_SUCCESS) {
         res = ws->ops->buffer_map(bo, NULL);
         CHECK("buffer_map(CPU)", res == VK_SUCCESS && bo->map);
         if (bo->map) {
            memset(bo->map, 0x5A, 256);
            CHECK("cpu_rw_roundtrip",
                  ((volatile uint8_t *)bo->map)[255] == 0x5A);
         }
         printf("PROBE dev_addr                0x%llx\n",
                (unsigned long long)addr.addr);
         ws->ops->buffer_unmap(bo, false);
      }
   }

   /* ---- Cleanup ------------------------------------------------------- */
   if (vma) {
      ws->ops->vma_unmap(vma);
      ws->ops->heap_free(vma);
   }
   if (bo)
      ws->ops->buffer_destroy(bo);
   if (tctx)
      ws->ops->transfer_ctx_destroy(tctx);
   pvr_winsys_destroy(ws);

   printf("PROBE SUMMARY                  %s\n", fail ? "FAIL" : "ALL-PASS");
   return fail ? 1 : 0;
}
