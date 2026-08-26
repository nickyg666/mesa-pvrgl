/* pvrgl_screen.c — pipe_screen for PowerVR BXM via mainline powervr DRM.
 *
 * M2: screen init establishes the full winsys state (device info, heaps,
 * transfer context) that M1 proved is required before any kernel object
 * creation succeeds.
 */
#include "pvrgl_screen.h"

#include <fcntl.h>
#include <unistd.h>
#include <xf86drm.h>

#include "util/u_debug.h"
#include "util/u_memory.h"
#include "util/u_inlines.h"
#include "util/os_file.h"
#include "util/u_screen.h"
#include "compiler/nir/nir.h"

#include "pvrgl_public.h"
#include "pvrgl_alloc.h"
#include "pvrgl_tq.h"
#include "pvrgl_resource.h"

#include "imagination/vulkan/winsys/pvr_winsys.h"
#include "imagination/common/pvr_device_info.h"
#include "vk_alloc.h"

/* Forward declarations */
static void pvrgl_destroy_screen(struct pipe_screen *pscreen);
static const char *pvrgl_get_name(struct pipe_screen *pscreen);
static uint64_t pvrgl_get_timestamp(struct pipe_screen *pscreen);
static struct pipe_context *pvrgl_context_create(
   struct pipe_screen *pscreen, void *priv, unsigned flags);
static bool pvrgl_is_format_supported(
   struct pipe_screen *pscreen, enum pipe_format format,
   enum pipe_texture_target target, unsigned sample_count,
   unsigned storage_sample_count, unsigned usage);

struct pipe_screen *
pvrgl_create_screen(int drm_fd)
{
   struct pvrgl_screen *screen;
   drmVersionPtr ver;

   screen = CALLOC_STRUCT(pvrgl_screen);
   if (!screen)
      return NULL;

   screen->fd = os_dupfd_cloexec(drm_fd); /* keep caller's fd untouched */
   screen->driver_name[0] = '\0';

   ver = drmGetVersion(drm_fd);
   if (ver) {
      snprintf(screen->driver_name, sizeof(screen->driver_name), "%s", ver->name);
      drmFreeVersion(ver);
   }

   /* ---- Winsys bring-up (the M1 lesson: all of this must happen in order) */
   {
      char path[128];
      VkResult res;

      const char *p = drmGetDeviceNameFromFd2(drm_fd);
      snprintf(path, sizeof(path), "%s", p ? p : "/dev/dri/renderD128");

      res = pvr_winsys_create(path, NULL, false,
                              PVRGL_ALLOC_CALLBACKS, &screen->ws);
      if (res != VK_SUCCESS || !screen->ws) {
         mesa_logw("pvrgl: pvr_winsys_create(%s) failed: %d", path, res);
         goto out_fail_winsys;
      }

      screen->dev_info = CALLOC_STRUCT(pvr_device_info);
      screen->runtime_info = CALLOC_STRUCT(pvr_device_runtime_info);
      screen->heaps = CALLOC_STRUCT(pvr_winsys_heaps);
      if (!screen->dev_info || !screen->runtime_info || !screen->heaps)
         goto out_fail_alloc;

      res = screen->ws->ops->device_info_init(screen->ws,
                                              screen->dev_info,
                                              screen->runtime_info);
      if (res != VK_SUCCESS) {
         mesa_logw("pvrgl: device_info_init failed: %d", res);
         goto out_fail_alloc;
      }

      screen->ws->ops->get_heaps_info(screen->ws, screen->heaps);

      res = screen->ws->ops->transfer_ctx_create(
         screen->ws,
         &(struct pvr_winsys_transfer_ctx_create_info){
            .priority = PVR_WINSYS_CTX_PRIORITY_MEDIUM,
         },
         &screen->tctx);
      if (res != VK_SUCCESS) {
         mesa_logw("pvrgl: transfer_ctx_create failed: %d", res);
         goto out_fail_alloc;
      }

      screen->winsys_ok = true;
      mesa_logi("pvrgl: winsys ready (page=%uK, heaps ok, TQ ctx ok)",
                (unsigned)(screen->ws->page_size >> 10));

      res = pvrgl_tq_init(screen, &screen->tq_priv);
      if (res != VK_SUCCESS) {
         mesa_logw("pvrgl: TQ init failed: %d", res);
         goto out_fail_alloc;
      }
   }

   /* Fill pipe_screen vtable */
   screen->base.destroy = pvrgl_destroy_screen;
   screen->base.get_name = pvrgl_get_name;
   screen->base.get_timestamp = pvrgl_get_timestamp;
   screen->base.context_create = pvrgl_context_create;
   screen->base.is_format_supported = pvrgl_is_format_supported;

   /* Caps: gallium-provided GL-2.1-era defaults + our overrides. */
   u_init_pipe_screen_caps(&screen->base, true /* accelerated */);
   {
      struct pipe_caps *caps = (struct pipe_caps *)&screen->base.caps;

      caps->npot_textures = true;
      /* ES2 renderable gate [version.c compute_version_es2]: */
      caps->blend_equation_separate = true;
      caps->max_texture_2d_size = 4096;
      caps->max_texture_3d_levels = 256;
      caps->max_texture_cube_levels = 14;
      caps->max_texture_array_layers = 256;
      caps->max_render_targets = 1;
      caps->constant_buffer_offset_alignment = 64;
      caps->texture_buffer_offset_alignment = 16;
      caps->max_vertex_streams = 4;
   }
   for (unsigned s = 0; s < MESA_SHADER_MESH_STAGES; s++) {
      struct pipe_shader_caps *sc =
         (struct pipe_shader_caps *)&screen->base.shader_caps[s];

      sc->max_instructions = 4096;
      sc->max_alu_instructions = 4096;
      sc->max_tex_instructions = 4096;
      sc->max_tex_indirections = 4096;
      sc->max_texture_samplers = 8;
      sc->max_shader_buffers = 0;
      sc->max_sampler_views = 8;
      sc->supported_irs = (1 << PIPE_SHADER_IR_NIR);
   }

   pvrgl_screen_init_resource_functions(&screen->base);

   {
      static const nir_shader_compiler_options pvrgl_nir_options = {
         .fdot_replicates = true,
         .lower_extract_byte = true,
         .lower_extract_word = true,
         .lower_insert_byte = true,
         .lower_insert_word = true,
         .lower_fdph = true,
         .lower_fmod = true,
         .lower_uniforms_to_ubo = true,
         .lower_cs_local_index_to_id = true,
         .max_unroll_iterations = 32,
      };
      for (unsigned s = 0; s < MESA_SHADER_MESH_STAGES; s++)
         screen->base.nir_options[s] = &pvrgl_nir_options;
   }

   mesa_logi("pvrgl: screen created ok");

   return &screen->base;

out_fail_alloc:
   pvrgl_tq_finish(screen, screen->tq_priv);
   if (screen->tctx && screen->ws)
      screen->ws->ops->transfer_ctx_destroy(screen->tctx);
   if (screen->ws)
      pvr_winsys_destroy(screen->ws);
out_fail_winsys:
   FREE(screen);
   return NULL;
}

static void
pvrgl_destroy_screen(struct pipe_screen *pscreen)
{
   struct pvrgl_screen *screen = (struct pvrgl_screen *)pscreen;

   pvrgl_tq_finish(screen, screen->tq_priv);
   if (screen->tctx && screen->ws)
      screen->ws->ops->transfer_ctx_destroy(screen->tctx);
   if (screen->ws)
      pvr_winsys_destroy(screen->ws);
   FREE(screen->dev_info);
   FREE(screen->runtime_info);
   FREE(screen->heaps);
   if (screen->fd >= 0)
      close(screen->fd);
   FREE(screen);
}

static const char *
pvrgl_get_name(struct pipe_screen *pscreen)
{
   return "PowerVR BXM-4-64 MC1 (pvrgl)";
}

static uint64_t
pvrgl_get_timestamp(struct pipe_screen *pscreen)
{
   return 0; /* TODO: GPU timestamp query */
}

static struct pipe_context *
pvrgl_context_create(struct pipe_screen *pscreen, void *priv, unsigned flags)
{
   return pvrgl_create_context(pscreen, priv, flags);
}

static bool
pvrgl_is_format_supported(struct pipe_screen *pscreen, enum pipe_format format,
   enum pipe_texture_target target, unsigned sample_count,
   unsigned storage_sample_count, unsigned usage)
{
   if (sample_count > 1)
      return false;

   switch (format) {
   case PIPE_FORMAT_R8G8B8A8_UNORM:
   case PIPE_FORMAT_BGRA8888_UNORM: /* same memory layout as B8G8R8A8 */
   case PIPE_FORMAT_BGRX8888_UNORM:
   case PIPE_FORMAT_B5G6R5_UNORM:
      return true;
   default:
      return false;
   }
}
