//
// Created by showtime on 12/1/2017.
//

#ifndef EXOGFX_VR_OGLES_EYE_H
#define EXOGFX_VR_OGLES_EYE_H

#include "../../math/mat4.h"
#include "vr_ogles_viewport.h"
#include "vr_ogles_fov.h"

typedef enum eye_type {EYE_CENTER, EYE_LEFT, EYE_RIGHT} eye_type;

struct vr_ogles_eye
{
    enum eye_type type;
    mat4 view;
    struct vr_ogles_viewport viewport;
    struct vr_ogles_fov fov;
    bool projection_changed;
    mat4 perspective;
    float last_near;
    float last_far;
};

void vr_ogles_eye_init(struct vr_ogles_eye *vr_ogles_eye, enum eye_type eye_type);

void vr_ogles_eye_get_perspective(struct vr_ogles_eye *vr_ogles_eye, const float near, const float far, mat4 *mat);

#endif //EXOGFX_VR_OGLES_EYE_H
