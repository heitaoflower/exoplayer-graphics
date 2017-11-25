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
    orientation_ekf_reset(&o);
    o.aligned_to_gravity = true;
    // acc -1.3926239013671875, 5.91265869140625, 7.4751739501953125
    // previousAccelNorm 9.60976575139596
    // movingAverageAccelNormChange 0.002772407310237989
    struct vec3 acc;
    vec3_set(&acc,-1.3926239013671875f, 5.91265869140625f, 7.4751739501953125f );
    mat3_set(&o.so3_sensor_from_world, 0.9866880756909621f, -0.07736556012614729f, -0.1430426908151337f, 0.1497106196002979f, 0.7756272416900796f, 0.6131795106876484f, 0.06350883141864648f, -0.6264319213247411f, 0.77688459649889f);
    o.previous_accel_norm = 9.60976575139596f;
    o.moving_average_accel_norm_change = 0.002772407310237989f;
    orientation_ekf_process_acc(&o, &acc, 0);
}

void camera_update(struct camera *camera)
{
    mat4_identity(&camera->model_mat);
    mat4_multiply(&camera->mvp_mat, &camera->view_mat, &camera->model_mat);
    mat4_multiply(&camera->mvp_mat, &camera->projection_mat, &camera->mvp_mat);
}