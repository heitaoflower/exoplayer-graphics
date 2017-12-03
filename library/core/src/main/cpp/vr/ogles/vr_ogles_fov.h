//
// Created by showtime on 12/1/2017.
//

#ifndef EXOGFX_VR_OGLES_FOV_H
#define EXOGFX_VR_OGLES_FOV_H

#include "../../math/mat4.h"

#define DEFAULT_MAX_FOV_LEFT_RIGHT 40.0f
#define DEFAULT_MAX_FOV_BOTTOM  40.0f
#define DEFAULT_MAX_FOV_TOP 40.0f

struct vr_ogles_fov
{
    float left;
    float right;
    float bottom;
    float top;
};

void vr_ogles_fov_init(struct vr_ogles_fov *vr_ogles_fov);

void vr_ogles_fov_set(struct vr_ogles_fov *vr_ogles_fov, float left, float right, float bottom, float top);

void vr_ogles_fov_copy(struct vr_ogles_fov *src, struct vr_ogles_fov *dst);

void vr_ogles_fov_to_perspective(struct vr_ogles_fov *vr_ogles_fov, float near, float far, mat4 *mat);

#endif //EXOGFX_VR_OGLES_FOV_H
