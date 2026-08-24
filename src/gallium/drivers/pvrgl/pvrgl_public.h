/* pvrgl_public.h — exported entry points for the PowerVR Gallium driver. */
#ifndef PVRGL_PUBLIC_H
#define PVRGL_PUBLIC_H

struct pipe_screen;

struct pipe_screen *
pvrgl_create_screen(int drm_fd);

#endif /* PVRGL_PUBLIC_H */
