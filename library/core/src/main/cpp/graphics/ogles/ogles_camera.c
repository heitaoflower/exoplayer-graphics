//
// Created by showtime on 12/10/2017.
//

#include "ogles_camera.h"
#include "ogles.h"

void ogles_camera_init(struct ogles_camera *ogles_camera, eye_type eye_type, projection_type projection_type)
{
    camera_init(&ogles_camera->camera, eye_type, projection_type);
}

void ogles_camera_rotate_yaw(struct ogles_camera *ogles_camera, float angle)
{
    camera_rotate_yaw(&ogles_camera->camera, angle);
}

void ogles_camera_rotate_pitch(struct ogles_camera *ogles_camera, float angle)
{
    camera_rotate_pitch(&ogles_camera->camera, angle);
}

void ogles_camera_rotate_roll(struct ogles_camera *ogles_camera, float angle)
{
    camera_rotate_roll(&ogles_camera->camera, angle);
}

void ogles_camera_set_lookat(struct ogles_camera *ogles_camera)
{
    camera_set_lookat(&ogles_camera->camera);
}

void ogles_camera_resize(struct ogles_camera *ogles_camera, GLint width, GLint height)
{
    camera_set_viewport(&ogles_camera->camera, width, height);
    camera_set_projection(&ogles_camera->camera, ogles_camera->camera.projection_type);

    glViewport(0, 0, width, height);
}

void ogles_camera_set_projection(struct ogles_camera *ogles_camera, projection_type projection_type)
{
    camera_set_projection(&ogles_camera->camera, projection_type);
}

void ogles_camera_update(struct ogles_camera *ogles_camera)
{
    camera_update(&ogles_camera->camera);
}

float ogles_camera_get_aspect(struct ogles_camera *ogles_camera)
{
    return ogles_camera->camera.aspect;
}