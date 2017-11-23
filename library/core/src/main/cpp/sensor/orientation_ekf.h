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
    uint64_t sensor_timestamp_gyro;
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

void process_gyro(struct vec3, int64_t timestamp);

void process_acc(struct vec3, int64_t timestamp);

#endif //EXOGFX_ORIENTATION_EKF_H
