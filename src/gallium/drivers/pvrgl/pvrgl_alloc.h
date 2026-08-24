/* pvrgl_alloc.h — allocation callbacks for non-Vulkan users of the
 * imagination winsys (pvrgl gallium driver, pvrws_probe).
 */
#ifndef PVRGL_ALLOC_H
#define PVRGL_ALLOC_H

#include "vk_alloc.h"

/* The winsys requires real VkAllocationCallbacks (NULL crashes in
 * vk_zalloc); mesa's runtime provides a libc-backed default allocator.
 */
#define PVRGL_ALLOC_CALLBACKS vk_default_allocator()

#endif /* PVRGL_ALLOC_H */
