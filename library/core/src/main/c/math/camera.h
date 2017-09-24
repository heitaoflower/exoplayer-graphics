//
// Created by showtime on 9/23/2017.
//

#ifndef EXOGFX_MATH_CAMERA_H
#define EXOGFX_MATH_CAMERA_H

#include "mat4.h"
#include "../graphics/ogles.h"

struct camera{
    mat4 view_mat;
    mat4 projection_mat;
    mat4 vp_mat;
    GLint viewport_width;
    GLint viewport_height;
};

void camera_set_lookat(struct camera *camera);

void camera_set_perspective(struct camera *camera, GLint width, GLint height);

void camera_update(struct camera *camera);

#endif //EXOGFX_MATH_CAMERA_H
