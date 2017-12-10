//
// Created by showtime on 11/29/2017.
//

#ifndef EXOGFX_VR_OGLES_ENGINE_H
#define EXOGFX_VR_OGLES_ENGINE_H

#include "../../math/camera.h"
#include "../../graphics/ogles/ogles_camera.h"

struct vr_ogles_engine
{
    struct ogles_camera both_ogles_camera;
    struct ogles_camera left_ogles_camera;
    struct ogles_camera right_ogles_camera;
    bool vr_mode;
};

void vr_ogles_engine_draw(struct vr_ogles_engine *vr_ogles_engine, int32_t display_rotation);

void vr_ogles_engine_init(struct vr_ogles_engine *vr_ogles_engine);

void vr_ogles_engine_resize(struct vr_ogles_engine *vr_ogles_engine, GLsizei width, GLsizei height);

void vr_ogles_engine_release(struct vr_ogles_engine *vr_ogles_engine);

#endif //EXOGFX_VR_OGLES_ENGINE_H
