//
// Created by showtime on 12/1/2017.
//

#include "vr_ogles_eye.h"

void vr_ogles_eye_init(struct vr_ogles_eye *vr_ogles_eye, enum eye_type eye_type)
{
    vr_ogles_eye->type = eye_type;
    mat4_identity(&vr_ogles_eye->view);
    vr_ogles_viewport_init(&vr_ogles_eye->viewport);
    vr_ogles_fov_init(&vr_ogles_eye->fov);
    vr_ogles_eye->projection_changed = true;
}

void vr_ogles_eye_get_perspective(struct vr_ogles_eye *vr_ogles_eye, const float near, const float far, mat4 *mat)
{
    if (!vr_ogles_eye->projection_changed && vr_ogles_eye->last_far == far && vr_ogles_eye->last_near == near)
    {
        mat4_copy(&vr_ogles_eye->perspective, mat);
        return;
    }

    vr_ogles_fov_to_perspective(&vr_ogles_eye->fov, near, far, mat);
    vr_ogles_eye->last_near = near;
    vr_ogles_eye->last_far = far;
    vr_ogles_eye->projection_changed = false;
}