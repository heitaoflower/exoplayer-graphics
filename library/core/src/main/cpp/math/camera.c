//
// Created by showtime on 9/23/2017.
//
#include "camera.h"

static void camera_set_perspective(struct camera *camera)
{
    mat4_perspective_default(&camera->projection_mat, camera->aspect);
}

static void camera_set_ortho(struct camera *camera)
{
    mat4_ortho_default(&camera->projection_mat, camera->aspect);
}

static void camera_set_frustum(struct camera *camera)
{
    mat4_frustum_default(&camera->projection_mat, camera->aspect);
}

void camera_init(struct camera *camera, eye_type eye_type, projection_type projection_type)
{
    camera->eye_type = eye_type;
    camera->projection_type = projection_type;
    mat4_identity(&camera->model_mat);
    mat4_identity(&camera->view_mat);
    mat4_identity(&camera->projection_mat);
    mat4_identity(&camera->mvp_mat);
}

void camera_rotate_yaw(struct camera *camera, float angle)
{
    mat4_rotate(&camera->model_mat, angle, 0, 1, 0);
}

void camera_rotate_pitch(struct camera *camera, float angle)
{
    mat4_rotate(&camera->model_mat, angle, 1, 0, 0);
}

void camera_rotate_roll(struct camera *camera, float angle)
{
    mat4_rotate(&camera->model_mat, angle, 0, 0, 1);
}

void camera_set_lookat(struct camera *camera)
{
    mat4_lookat(&camera->view_mat, 0.0f, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void camera_set_viewport(struct camera *camera, int width, int height)
{
    camera->viewport_width = width;
    camera->viewport_height = height;
    camera->aspect = camera->viewport_width / (float)camera->viewport_height;
}

void camera_set_projection(struct camera *camera, projection_type projection_type)
{
    camera->projection_type = projection_type;
    switch (projection_type)
    {
        case ProjectionTypePerspective:
        {
            camera_set_perspective(camera);
            break;
        }
        case ProjectionTypeOrtho:
        {
            camera_set_ortho(camera);
            break;
        }
        case ProjectionTypeFrustum:
        {
            camera_set_frustum(camera);
            break;
        }
    }
}

void camera_update(struct camera *camera)
{
    mat4_multiply(&camera->mvp_mat, &camera->view_mat, &camera->model_mat);
    mat4_multiply(&camera->mvp_mat, &camera->projection_mat, &camera->mvp_mat);
}