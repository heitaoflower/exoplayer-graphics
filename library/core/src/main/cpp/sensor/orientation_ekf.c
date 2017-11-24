//
// Created by showtime on 10/15/2017.
//

#include "orientation_ekf.h"
#include "../math/mat3.h"
#include "../math/mat4.h"
#include "so3.h"

#include <math.h>

static void orientation_ekf_gl_matrix_from_so3(mat3 *so3, mat4 *matrix)
{
    mat4_zero(matrix);
    for (uint32_t r = 0; r < 3; ++r)
    {
        for (uint32_t c = 0; c < 3; ++c)
        {
            *mat4_element(matrix, r, c) = *mat3_element(so3, r, c);
        }
    }

    *mat4_element(matrix, 3, 3) = 1.0f;
}

void orientation_ekf_init(struct orientation_ekf* orientation_ekf)
{
    orientation_ekf->previous_accel_norm = 0.0f;
    orientation_ekf->moving_average_accel_norm_change = 0.0f;
    orientation_ekf->timestamp_filter_init = false;
    orientation_ekf->gyro_filter_valid = true;
}

void orientation_ekf_reset(struct orientation_ekf *orientation_ekf)
{
    orientation_ekf->sensor_timestamp_gyro = 0;
    mat3_identity(&orientation_ekf->so3_sensor_from_world);
    mat3_identity(&orientation_ekf->so3_last_motion);
    mat3_zero(&orientation_ekf->m_p);
    mat3_set_same(&orientation_ekf->m_p, 25.0f);
    mat3_zero(&orientation_ekf->m_q);
    mat3_set_same(&orientation_ekf->m_q, 1.0f);
    mat3_zero(&orientation_ekf->m_p);
    mat3_set_same(&orientation_ekf->m_p, 0.0625f);
    mat3_zero(&orientation_ekf->m_raccel);
    mat3_set_same(&orientation_ekf->m_raccel, 0.5625f);
    mat3_zero(&orientation_ekf->m_s);
    mat3_zero(&orientation_ekf->m_s);
    mat3_zero(&orientation_ekf->m_h);
    mat3_zero(&orientation_ekf->m_k);
    vec3_zero(&orientation_ekf->v_nu);
    vec3_zero(&orientation_ekf->v_z);
    vec3_zero(&orientation_ekf->v_h);
    vec3_zero(&orientation_ekf->v_u);
    vec3_zero(&orientation_ekf->v_x);

    vec3_set(&orientation_ekf->v_down, 0.0f, 0.0f, 9.81f);
    vec3_set(&orientation_ekf->v_north, 0.0f, 1.0f, 0.0f);
    orientation_ekf->aligned_to_gravity = false;
    orientation_ekf->aligned_to_north = false;
}

float orientation_get_heading_degrees(struct orientation_ekf *orientation_ekf)
{
    const float x = *mat3_element(&orientation_ekf->so3_sensor_from_world, 2, 0);
    const float y = *mat3_element(&orientation_ekf->so3_sensor_from_world, 2, 1);
    const float mag = sqrtf(x * x + y * y);
    if (mag < 0.1f)
    {
        return 0.0f;
    }

    float heading = -90.0f - rad2deg(atan2f(y, x));
    if (heading < 0.0f)
    {
        heading += 360.0f;
    }

    if (heading >= 360.0f)
    {
        heading -= 360.0f;
    }

    return heading;
}

float orientation_set_heading_degrees(struct orientation_ekf *orientation_ekf, float heading)
{
    const float current_heading = orientation_get_heading_degrees(orientation_ekf);
    const float delta_heading = heading - current_heading;
    const float s = sinf(deg2rad(delta_heading));
    const float c = cosf(deg2rad(delta_heading));
    mat3 delta_heading_rotation;
    mat3_set(&delta_heading_rotation, c, -s, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 1.0f);
    mat3_mul(&orientation_ekf->so3_sensor_from_world, &delta_heading_rotation, &orientation_ekf->so3_sensor_from_world);
}

void orientation_get_predicted_gl_matrix(struct orientation_ekf *orientation_ekf, float seconds_after_last_gyro_event, mat4 *matrix)
{
    struct vec3 pmu;
    vec3_copy(&orientation_ekf->last_gyro, &pmu);
    vec3_scale(&pmu, -seconds_after_last_gyro_event);
    mat3 so3_predicted_motion;
    so3_from_mu(&pmu, &so3_predicted_motion);
    mat3 so3_predicted_state;
    mat3_mul(&so3_predicted_motion, &orientation_ekf->so3_sensor_from_world, &so3_predicted_state);
    orientation_ekf_gl_matrix_from_so3(&so3_predicted_state, matrix);
}

void orientation_process_gyro(struct orientation_ekf *orientation_ekf, struct vec3 gyro, int64_t timestamp)
{

}

void orientation_process_acc(struct orientation_ekf *orientation_ekf, struct vec3 acc, int64_t timestamp)
{

}