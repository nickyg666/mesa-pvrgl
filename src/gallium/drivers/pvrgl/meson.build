# pvrgl — Native OpenGL Gallium driver for PowerVR BXM (Rogue ISA).
#
# Talks to the mainline powervr DRM kernel driver through the shared
# imagination winsys (src/imagination/vulkan/winsys) — the same layer the
# Vulkan driver uses, with no Vulkan runtime objects involved.
#
# Milestones:
#   M2: winsys-backed resources + hardware clear via TQ/PBE
#   M3: draw triangle with pco-compiled shaders
#   M4: textures, blending, full pipe_screen

files_pvrgl = files(
  'pvrgl_screen.c',
  'pvrgl_context.c',
  'pvrgl_resource.c',
  'pvrgl_clear.c',
  'pvrgl_state.c',
  # TQ clear backend + linked arch helpers from the vulkan driver.
  'pvrgl_tq.c',
  # M3 render path: HWRT dataset + RENDER context + geometry/fragment submit.
  'pvrgl_render.c',
  '../../../imagination/vulkan/pvr_arch_job_common.c',
  '../../../imagination/vulkan/pvr_arch_formats.c',
  '../../../imagination/vulkan/pvr_usc.c',
)

# Shared imagination winsys — same sources the Vulkan driver compiles.
files_pvrgl_winsys = files(
  '../../../imagination/vulkan/winsys/powervr/pvr_drm.c',
  '../../../imagination/vulkan/winsys/powervr/pvr_drm_bo.c',
  '../../../imagination/vulkan/winsys/powervr/pvr_drm_job_compute.c',
  '../../../imagination/vulkan/winsys/powervr/pvr_drm_job_null.c',
  '../../../imagination/vulkan/winsys/powervr/pvr_drm_job_render.c',
  '../../../imagination/vulkan/winsys/powervr/pvr_drm_job_transfer.c',
  '../../../imagination/vulkan/winsys/pvr_winsys.c',
  '../../../imagination/vulkan/winsys/pvr_winsys_helper.c',
)

libpvrgl = static_library(
  'pvrgl',
  [files_pvrgl, files_pvrgl_winsys, pvr_entrypoints[1]],
  include_directories : [
    inc_include, inc_src, inc_gallium, inc_gallium_aux,
    inc_imagination,
    include_directories('../../../imagination/vulkan'),
    include_directories('../../../imagination/vulkan/winsys'),
    libpowervr_pds_includes,
  ],
  link_with : [
    libpowervr_common,
    libpowervr_pds,
    libpowervr_compiler,
  ],
  dependencies : [
    dep_libdrm,
    dep_csbgen,
    idep_mesautil,
    idep_nir_headers,
    idep_nir,
    idep_vulkan_util_headers,
    idep_vulkan_runtime,
    idep_vulkan_wsi_headers,
    idep_pco_uscgen_programs,
  ],
  c_args : [imagination_c_args, '-DPVR_BUILD_ARCH_ROGUE'],
  gnu_symbol_visibility : 'hidden',
)

driver_pvrgl = declare_dependency(
  compile_args : '-DGALLIUM_PVRGL',
  link_with : libpvrgl,
)
