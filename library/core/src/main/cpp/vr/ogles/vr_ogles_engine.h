//
// Created by showtime on 11/29/2017.
//

#ifndef EXOGFX_VR_OGLES_ENGINE_H
#define EXOGFX_VR_OGLES_ENGINE_H

#include "vr_ogles_eye.h"

struct vr_ogles_engine
{
    struct vr_ogles_eye center_eye;
    struct vr_ogles_eye left_eye;
    struct vr_ogles_eye right_eye;
    bool vr_mode;
    bool project_changed;
};

void vr_ogles_engine_draw(struct vr_ogles_engine *vr_ogles_engine);

void vr_ogles_engine_init(struct vr_ogles_engine *vr_ogles_engine);

void vr_ogles_engine_release(struct vr_ogles_engine *vr_ogles_engine);

#endif //EXOGFX_VR_OGLES_ENGINE_H
