//
// Created by showtime on 12/1/2017.
//

#include "vr_ogles_viewport.h"
#include "../../graphics/ogles/ogles.h"

void vr_ogles_viewport_init(struct vr_ogles_viewport *vr_ogles_viewport)
{
    vr_ogles_viewport_set(vr_ogles_viewport, 0, 0, 0, 0);
}

void vr_ogles_viewport_set(struct vr_ogles_viewport *vr_ogles_viewport, GLint x, GLint y, GLint width, GLint height)
{
    vr_ogles_viewport->x = x;
    vr_ogles_viewport->y = y;
    vr_ogles_viewport->width = width;
    vr_ogles_viewport->height = height;
}

void vr_ogles_viewport_apply(struct vr_ogles_viewport *vr_ogles_viewport)
{
    glViewport(vr_ogles_viewport->x, vr_ogles_viewport->y, vr_ogles_viewport->width, vr_ogles_viewport->height);
}

void vr_ogles_viewport_apply_scissor(struct vr_ogles_viewport *vr_ogles_viewport)
{
    glScissor(vr_ogles_viewport->x, vr_ogles_viewport->y, vr_ogles_viewport->width, vr_ogles_viewport->height);
}
