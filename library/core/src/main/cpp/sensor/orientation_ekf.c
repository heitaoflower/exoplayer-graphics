//
// Created by showtime on 10/15/2017.
//

#include "orientation_ekf.h"
#include "../math/mat3.h"
#include "../math/mat4.h"
#include "so3.h"
#include "../utils/log_util.h"

#include <math.h>

static void acc_observation_function_numerical_jacobian(struct orientation_ekf *orientation_ekf, mat3 *so3_sensor_from_world_pred, struct vec3 *result)
{
    mat3_multiply_mv(so3_sensor_from_world_pred, &orientation_ekf->v_down, &orientation_ekf->v_h);
    mat3 temp;
    so3_from_two_vec(&orientation_ekf->v_h, &orientation_ekf->v_z, &temp);
    so3_to_mu(&temp, result);
}

static void orientation_ekf_update_covariances_after_motion(struct orientation_ekf *orientation_ekf)
{
    mat3 temp_m1;
    mat3 temp_m2;
    mat3_transpose_to(&orientation_ekf->so3_last_motion, &temp_m1);
    mat3_multiply_mm(&orientation_ekf->m_p, &temp_m1, &temp_m2);
    mat3_multiply_mm(&orientation_ekf->so3_last_motion, &temp_m2, &orientation_ekf->m_p);
    mat3_identity(&orientation_ekf->so3_last_motion);
}

static void orientation_ekf_update_accel_covariance(struct orientation_ekf *orientation_ekf, float current_accel_norm)
{
    const float current_accel_norm_change = fabsf(current_accel_norm - orientation_ekf->previous_accel_norm);
    orientation_ekf->previous_accel_norm = current_accel_norm;
    const float smoothing_factor = 0.5f;
    orientation_ekf->moving_average_accel_norm_change = smoothing_factor * orientation_ekf->moving_average_accel_norm_change + (1.0f - smoothing_factor) * current_accel_norm_change;
    const float max_accel_norm_change = 0.15f;
    const float min_accel_noise_sigma = 0.75f;
    const float max_accel_noise_sigma = 7.0f;
    const float norm_change_ratio = orientation_ekf->moving_average_accel_norm_change / max_accel_norm_change;
    const float accel_noise_sigma = fminf(max_accel_noise_sigma, min_accel_noise_sigma + norm_change_ratio * (max_accel_noise_sigma - min_accel_noise_sigma));
    mat3_set_same(&orientation_ekf->m_raccel, accel_noise_sigma * accel_noise_sigma);
}

static void orientation_ekf_filter_gyro_timestep(struct orientation_ekf *orientation_ekf, float timestep)
{
    const float filter_coeff = 0.95f;
    const uint32_t min_samples = 10;
    if (!orientation_ekf->timestamp_filter_init)
    {
        orientation_ekf->filtered_gyro_timestep = timestep;
        orientation_ekf->num_gyro_timestep_samples = 1;
        orientation_ekf->timestamp_filter_init = true;
    }
    else
    {
        orientation_ekf->filtered_gyro_timestep = filter_coeff * orientation_ekf->filtered_gyro_timestep + (1 - filter_coeff) * timestep;
        if (++orientation_ekf->num_gyro_timestep_samples > min_samples)
        {
            orientation_ekf->gyro_filter_valid = true;
        }
    }
}

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
    mat3_zero(&orientation_ekf->m_r);
    mat3_set_same(&orientation_ekf->m_r, 0.0625f);
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

float orientation_ekf_get_heading_degrees(struct orientation_ekf *orientation_ekf)
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

float orientation_ekf_set_heading_degrees(struct orientation_ekf *orientation_ekf, float heading)
{
    const float current_heading = orientation_ekf_get_heading_degrees(orientation_ekf);
    const float delta_heading = heading - current_heading;
    const float s = sinf(deg2rad(delta_heading));
    const float c = cosf(deg2rad(delta_heading));
    mat3 delta_heading_rotation;
    mat3_set(&delta_heading_rotation, c, -s, 0.0f, s, c, 0.0f, 0.0f, 0.0f, 1.0f);
    mat3_multiply_mm(&orientation_ekf->so3_sensor_from_world, &delta_heading_rotation,
                     &orientation_ekf->so3_sensor_from_world);
}

void orientation_ekf_get_predicted_gl_matrix(struct orientation_ekf *orientation_ekf, float seconds_after_last_gyro_event, mat4 *matrix)
{
    struct vec3 pmu;
    vec3_copy(&orientation_ekf->last_gyro, &pmu);
    vec3_scale(&pmu, -seconds_after_last_gyro_event);
    mat3 so3_predicted_motion;
    so3_from_mu(&pmu, &so3_predicted_motion);
    mat3 so3_predicted_state;
    mat3_multiply_mm(&so3_predicted_motion, &orientation_ekf->so3_sensor_from_world,
                     &so3_predicted_state);
    orientation_ekf_gl_matrix_from_so3(&so3_predicted_state, matrix);
}

void orientation_ekf_process_gyro(struct orientation_ekf *orientation_ekf, struct vec3 *gyro, int64_t timestamp)
{
    const float time_threshould = 0.04f;
    const float delta_default = 0.01f;
    if (orientation_ekf->sensor_timestamp_gyro != 0.0f)
    {
        float delta = (timestamp - orientation_ekf->sensor_timestamp_gyro) * 1.0E-9f;
        if (delta > time_threshould)
        {
            delta= (orientation_ekf->gyro_filter_valid ? orientation_ekf->filtered_gyro_timestep : delta_default);
        }
        else
        {
            orientation_ekf_filter_gyro_timestep(orientation_ekf, delta);
        }

        vec3_copy(gyro, &orientation_ekf->v_u);
        vec3_scale(&orientation_ekf->v_u, -delta);
        so3_from_mu(&orientation_ekf->v_u, &orientation_ekf->so3_last_motion);
        mat3_multiply_mm(&orientation_ekf->so3_last_motion, &orientation_ekf->so3_sensor_from_world,
                         &orientation_ekf->so3_sensor_from_world);
        orientation_ekf_update_covariances_after_motion(orientation_ekf);
        mat3 temp;
        mat3_copy(&orientation_ekf->m_q, &temp);
        mat3_scale(&temp, delta * delta);
        mat3_add(&orientation_ekf->m_p, &temp, &orientation_ekf->m_p);
    }
    orientation_ekf->sensor_timestamp_gyro = timestamp;
    vec3_copy(gyro, &orientation_ekf->last_gyro);
}

void orientation_ekf_process_acc(struct orientation_ekf *orientation_ekf, struct vec3 *acc, int64_t timestamp)
{
    vec3_copy(acc, &orientation_ekf->v_z);
    orientation_ekf_update_accel_covariance(orientation_ekf, vec3_distance(&orientation_ekf->v_z));
    if (orientation_ekf->aligned_to_gravity)
    {
        acc_observation_function_numerical_jacobian(orientation_ekf, &orientation_ekf->so3_sensor_from_world, &orientation_ekf->v_nu);
        const float eps = 1.0E-7f;
        for (uint32_t dof = 0; dof < 3; ++dof)
        {
            struct vec3 temp_v1, temp_v2;
            mat3 temp_m1, temp_m2;
            vec3_zero(&temp_v1);
            vec3_set_component(&temp_v1, dof, eps);
            so3_from_mu(&temp_v1, &temp_m1);
            mat3_multiply_mm(&temp_m1, &orientation_ekf->so3_sensor_from_world, &temp_m2);
            acc_observation_function_numerical_jacobian(orientation_ekf, &temp_m2, &temp_v1);
            vec3_sub(&orientation_ekf->v_nu, &temp_v1, &temp_v2);
            vec3_scale(&temp_v2, 1.0f/eps);
            mat3_set_row(&orientation_ekf->m_h, dof, &temp_v2);
        }

        mat3 temp_m3, temp_m4, temp_m5;
        mat3_transpose_to(&orientation_ekf->m_h, &temp_m3);
        mat3_multiply_mm(&orientation_ekf->m_p, &temp_m3, &temp_m4);
        mat3_multiply_mm(&orientation_ekf->m_h, &temp_m4, &temp_m5);
        mat3_add(&temp_m5, &orientation_ekf->m_raccel, &orientation_ekf->m_s);
        mat3_invert(&orientation_ekf->m_s, &temp_m3);

        mat3_transpose_to(&orientation_ekf->m_h, &temp_m4);
        mat3_multiply_mm(&temp_m4, &temp_m3, &temp_m5);
        mat3_multiply_mm(&orientation_ekf->m_p, &temp_m5, &orientation_ekf->m_k);
        mat3_multiply_mv(&orientation_ekf->m_k, &orientation_ekf->v_nu, &orientation_ekf->v_x);
        mat3_multiply_mm(&orientation_ekf->m_k, &orientation_ekf->m_h, &temp_m3);

        mat3_identity(&temp_m4);
        mat3_sub(&temp_m4, &temp_m3, &temp_m4);
        mat3_multiply_mm(&temp_m4, &orientation_ekf->m_p, &temp_m3);
        mat3_copy(&temp_m3, &orientation_ekf->m_p);
        so3_from_mu(&orientation_ekf->v_x, &orientation_ekf->so3_last_motion);
        mat3_multiply_mm(&orientation_ekf->so3_last_motion, &orientation_ekf->so3_sensor_from_world,
                         &orientation_ekf->so3_sensor_from_world);
        orientation_ekf_update_covariances_after_motion(orientation_ekf);
    }
    else
    {
        so3_from_two_vec(&orientation_ekf->v_down, &orientation_ekf->v_z, &orientation_ekf->so3_sensor_from_world);
        orientation_ekf->aligned_to_gravity = true;
    }
}