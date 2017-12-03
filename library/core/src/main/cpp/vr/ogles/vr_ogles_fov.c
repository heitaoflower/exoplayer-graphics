//
// Created by showtime on 12/1/2017.
//

#include <math.h>
#include "vr_ogles_fov.h"

void vr_ogles_fov_init(struct vr_ogles_fov *vr_ogles_fov)
{
    vr_ogles_fov->left = DEFAULT_MAX_FOV_LEFT_RIGHT;
    vr_ogles_fov->right = DEFAULT_MAX_FOV_LEFT_RIGHT;
    vr_ogles_fov->top = DEFAULT_MAX_FOV_TOP;
    vr_ogles_fov->bottom = DEFAULT_MAX_FOV_BOTTOM;
}

void vr_ogles_fov_set(struct vr_ogles_fov *vr_ogles_fov, float left, float right, float bottom, float top)
{
    vr_ogles_fov->left = left;
    vr_ogles_fov->right = right;
    vr_ogles_fov->bottom = bottom;
    vr_ogles_fov->top = top;
}

void vr_ogles_fov_copy(struct vr_ogles_fov *src, struct vr_ogles_fov *dst)
{
    dst->left = src->left;
    dst->right = src->right;
    dst->bottom = src->bottom;
    dst->top = src->top;
}

void vr_ogles_fov_to_perspective(struct vr_ogles_fov *vr_ogles_fov, float near, float far, mat4 *mat)
{
    const float l = -tanf(deg2rad(vr_ogles_fov->left)) * near;
    const float r = tanf(deg2rad(vr_ogles_fov->right)) * near;
    const float b = -tanf(deg2rad(vr_ogles_fov->bottom)) * near;
    const float t = tanf(deg2rad(vr_ogles_fov->top)) * near;
    mat4_frustum(mat, l, r, b, t, near, far);
}