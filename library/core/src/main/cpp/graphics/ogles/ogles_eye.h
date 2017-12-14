//
// Created by showtime on 12/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_EYE_H
#define EXOGFX_GRAPHICS_OGLES_EYE_H

#include "../../math/camera.h"
#include "ogles.h"

struct ogles_eye{
    struct camera camera;
};

void ogles_eye_init(struct ogles_eye *ogles_eye, eye_type eye_type, projection_type projection_type);

void ogles_eye_rotate_yaw(struct ogles_eye *ogles_eye, float angle);

void ogles_eye_rotate_pitch(struct ogles_eye *ogles_eye, float angle);

void ogles_eye_rotate_roll(struct ogles_eye *ogles_eye, float angle);

void ogles_eye_set_lookat_default(struct ogles_eye *ogles_eye);

void ogles_eye_resize(struct ogles_eye *ogles_eye, GLint width, GLint height);

void ogles_eye_update(struct ogles_eye *ogles_eye);

float ogles_eye_get_aspect(struct ogles_eye *ogles_eye);

#endif //EXOGFX_GRAPHICS_OGLES_EYE_H
