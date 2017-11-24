//
// Created by showtime on 9/23/2017.
//
#include "camera.h"

#include "../sensor/orientation_ekf.h"
#include "../math/mat3.h"
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

    struct orientation_ekf o;
    orientation_ekf_init(&o);
    o.last_gyro.x = 0.035064697265625f;
    o.last_gyro.y = -0.0138092041015625f;
    o.last_gyro.z = 0.027496337890625f;
    mat3_set(&o.so3_sensor_from_world, 0.3270542403031921f,
             0.08117731874733539f,
             -0.9415124889350661f,
             0.3465762055409068f,
             0.916579153676822f,
             0.199418125550194f,
             0.87915894902604f,
             -0.3915263694389938f,
             0.2716369716760765f);
    mat4 result;
    orientation_get_predicted_gl_matrix(&o, 0.03333333333333333f, &result);
}

void camera_update(struct camera *camera)
{
    mat4_identity(&camera->model_mat);
    mat4_multiply(&camera->mvp_mat, &camera->view_mat, &camera->model_mat);
    mat4_multiply(&camera->mvp_mat, &camera->projection_mat, &camera->mvp_mat);
}