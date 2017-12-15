//
// Created by showtime on 12/10/2017.
//

#include "ogles_eye.h"

void ogles_eye_init(struct ogles_eye *ogles_eye, eye_type eye_type, projection_type projection_type)
{
    camera_init(&ogles_eye->camera, eye_type, projection_type);
}

void ogles_eye_rotate_yaw(struct ogles_eye *ogles_eye, float angle)
{
    camera_rotate_yaw(&ogles_eye->camera, angle);
}

void ogles_eye_rotate_pitch(struct ogles_eye *ogles_eye, float angle)
{
    camera_rotate_pitch(&ogles_eye->camera, angle);
}

void ogles_eye_rotate_roll(struct ogles_eye *ogles_eye, float angle)
{
    camera_rotate_roll(&ogles_eye->camera, angle);
}

void ogles_eye_set_lookat_default(struct ogles_eye *ogles_eye)
{
    camera_set_lookat_default(&ogles_eye->camera);
}

void ogles_eye_resize(struct ogles_eye *ogles_eye, GLint width, GLint height)
{
    camera_set_viewport(&ogles_eye->camera, width, height);

    camera_set_projection(&ogles_eye->camera, ogles_eye->camera.projection_type);
}

void ogles_eye_set_projection(struct ogles_eye *ogles_eye, projection_type projection_type)
{
    camera_set_projection(&ogles_eye->camera, projection_type);
}

void ogles_eye_update(struct ogles_eye *ogles_eye)
{
    camera_update(&ogles_eye->camera);
}

void ogles_eye_apply_viewport(struct ogles_eye *ogles_eye)
{
    glViewport(ogles_eye->camera.viewport.x, ogles_eye->camera.viewport.y, ogles_eye->camera.viewport.width, ogles_eye->camera.viewport.height);
}

float ogles_eye_get_aspect(struct ogles_eye *ogles_eye)
{
    return ogles_eye->camera.aspect;
}