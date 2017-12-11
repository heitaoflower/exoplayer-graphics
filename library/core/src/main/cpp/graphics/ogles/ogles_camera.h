//
// Created by showtime on 12/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_CAMERA_H
#define EXOGFX_GRAPHICS_OGLES_CAMERA_H

#include "../../math/camera.h"
#include "ogles.h"

struct ogles_camera{
    struct camera camera;
};

void ogles_camera_init(struct ogles_camera *ogles_camera, eye_type eye_type, projection_type projection_type);

void ogles_camera_rotate_yaw(struct ogles_camera *ogles_camera, float angle);

void ogles_camera_rotate_pitch(struct ogles_camera *ogles_camera, float angle);

void ogles_camera_rotate_roll(struct ogles_camera *ogles_camera, float angle);

void ogles_camera_set_lookat(struct ogles_camera *ogles_camera);

void ogles_camera_resize(struct ogles_camera *ogles_camera, GLint width, GLint height);

void ogles_camera_update(struct ogles_camera *ogles_camera);

float ogles_camera_get_aspect(struct ogles_camera *ogles_camera);

#endif //EXOGFX_GRAPHICS_OGLES_CAMERA_H
