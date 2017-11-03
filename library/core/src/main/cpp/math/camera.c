//
// Created by showtime on 9/23/2017.
//
#include "camera.h"

static void camera_set_perspective(struct camera *camera, GLint width, GLint height)
{
    mat4_perspective_default(&camera->projection_mat, camera->aspect);
}

static void camera_set_ortho(struct camera *camera, GLint width, GLint height)
{
    mat4_ortho_default(&camera->projection_mat, camera->aspect);
}

static void camera_set_frustum(struct camera *camera, GLint width, GLint height)
{
    mat4_frustum_default(&camera->projection_mat, camera->aspect);
}

void camera_set_lookat(struct camera *camera)
{
    mat4_lookat(&camera->view_mat, 0.0f, 0.0f, 0.3f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}

void camera_set_projection(struct camera *camera, projection_type projection_type, GLint width, GLint height)
{
    camera->viewport_width = width;
    camera->viewport_height = height;
    camera->aspect = width / (float)height;

    switch (projection_type)
    {
        case ProjectionTypePerspective:
        {
            camera_set_perspective(camera, width, height);
            break;
        }
        case ProjectionTypeOrtho:
        {
            camera_set_ortho(camera, width, height);
            break;
        }
        case ProjectionTypeFrustum:
        {
            camera_set_frustum(camera, width, height);
            break;
        }
    }
}

void camera_update(struct camera *camera)
{
    mat4_identity(&camera->model_mat);
    mat4_multiply(&camera->mvp_mat, &camera->view_mat, &camera->model_mat);
    mat4_multiply(&camera->mvp_mat, &camera->projection_mat, &camera->mvp_mat);
}