//
// Created by showtime on 9/23/2017.
//

#ifndef EXOGFX_GRAPHICS_CAMERA_H
#define EXOGFX_GRAPHICS_CAMERA_H

#include "../math/mat4.h"

struct camera{
    mat4 view_mat;
    mat4 projection_mat;
    mat4 vp_mat;
};

void camera_set_lookat(struct camera *camera);

void camera_set_perspective_matrix(struct camera *camera);

void camera_update(struct camera *camera);

#endif //EXOGFX_GRAPHICS_CAMERA_H
