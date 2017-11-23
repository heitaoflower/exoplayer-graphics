//
// Created by showtime on 10/15/2017.
//

#include "orientation_ekf.h"
#include "../math/mat3.h"

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