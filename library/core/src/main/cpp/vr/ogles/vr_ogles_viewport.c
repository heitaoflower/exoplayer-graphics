//
// Created by showtime on 12/1/2017.
//

#include "vr_ogles_viewport.h"
#include "../../graphics/ogles/ogles.h"

void vr_ogles_viewport_init(struct vr_ogles_viewport *vr_ogles_viewport)
{

}

void vr_ogles_viewport_set(struct vr_ogles_viewport *vr_ogles_viewport)
{
    glViewport(vr_ogles_viewport->x, vr_ogles_viewport->y, vr_ogles_viewport->width, vr_ogles_viewport->height);
}

void vr_ogles_viewport_set_scissor(struct vr_ogles_viewport *vr_ogles_viewport)
{
    glScissor(vr_ogles_viewport->x, vr_ogles_viewport->y, vr_ogles_viewport->width, vr_ogles_viewport->height);
}
