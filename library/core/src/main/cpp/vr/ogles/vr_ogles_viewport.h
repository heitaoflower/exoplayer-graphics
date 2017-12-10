//
// Created by showtime on 12/1/2017.
//

#ifndef EXOGFX_VR_OGLES_VIEWPORT_H
#define EXOGFX_VR_OGLES_VIEWPORT_H

#include <GLES2/gl2.h>

struct vr_ogles_viewport
{
    GLint x;
    GLint y;
    GLsizei width;
    GLsizei height;
};

void vr_ogles_viewport_init(struct vr_ogles_viewport *vr_ogles_viewport);

void vr_ogles_viewport_set(struct vr_ogles_viewport *vr_ogles_viewport, GLint x, GLint y, GLint width, GLint height);

void vr_ogles_viewport_apply(struct vr_ogles_viewport *vr_ogles_viewport);

void vr_ogles_viewport_apply_scissor(struct vr_ogles_viewport *vr_ogles_viewport);

#endif // EXOGFX_VR_OGLES_VIEWPORT_H
