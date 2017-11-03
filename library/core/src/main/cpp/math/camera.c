//
// Created by showtime on 9/23/2017.
//


#include "camera.h"

static void camera_set_perspective(struct camera *camera, GLint width, GLint height)
{
    if (camera->viewport_width != width || camera->viewport_height != height)
    {
        camera->viewport_width = width;
        camera->viewport_height = height;

        mat4_perspective_default(&camera->projection_mat, width / (float)height);
    }
}

static void camera_set_ortho(struct camera *camera, GLint width, GLint height)
{
    if (camera->viewport_width != width || camera->viewport_height != height)
    {
        camera->viewport_width = width;
        camera->viewport_height = height;

        mat4_ortho_default(&camera->projection_mat, width / (float)height);
    }
}

void camera_set_lookat(struct camera *camera)
{
    mat4_lookat(&camera->view_mat, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
}

void camera_set_projection(struct camera *camera, projection_type projection_type, GLint width, GLint height)
{
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
            // TODO
            break;
        }
    }
}

void camera_update(struct camera *camera)
{
    mat4_multiply(&camera->vp_mat, &camera->projection_mat, &camera->view_mat);
}