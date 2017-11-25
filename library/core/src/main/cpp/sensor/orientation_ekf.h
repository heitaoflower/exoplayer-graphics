//
// Created by showtime on 10/15/2017.
//

#ifndef EXOGFX_ORIENTATION_EKF_H
#define EXOGFX_ORIENTATION_EKF_H

#include "../math/vec3.h"

#include <stdint.h>

struct orientation_ekf
{
    mat3 so3_sensor_from_world;
    mat3 so3_last_motion;
    mat3 m_p;
    mat3 m_q;
    mat3 m_r;
    mat3 m_raccel;
    mat3 m_s;
    mat3 m_h;
    mat3 m_k;
    struct vec3 v_nu;
    struct vec3 v_z;
    struct vec3 v_h;
    struct vec3 v_u;
    struct vec3 v_x;
    struct vec3 v_down;
    struct vec3 v_north;
    int64_t sensor_timestamp_gyro;
    struct vec3 last_gyro;
    float previous_accel_norm;
    float moving_average_accel_norm_change;
    float filtered_gyro_timestep;
    bool timestamp_filter_init;
    uint32_t num_gyro_timestep_samples;
    bool gyro_filter_valid;
    bool aligned_to_gravity;
    bool aligned_to_north;
};

void orientation_ekf_init(struct orientation_ekf *orientation_ekf);

void orientation_ekf_reset(struct orientation_ekf *orientation_ekf);

float orientation_ekf_get_heading_degrees(struct orientation_ekf *orientation_ekf);

float orientation_ekf_set_heading_degrees(struct orientation_ekf *orientation_ekf, float heading);

void orientation_ekf_get_predicted_gl_matrix(struct orientation_ekf *orientation_ekf, float seconds_after_last_gyro_event, mat4 *matrix);

void orientation_ekf_process_gyro(struct orientation_ekf *orientation_ekf, struct vec3 *gyro, int64_t timestamp);

void orientation_ekf_process_acc(struct orientation_ekf *orientation_ekf, struct vec3 *acc, int64_t timestamp);

#endif //EXOGFX_ORIENTATION_EKF_H
