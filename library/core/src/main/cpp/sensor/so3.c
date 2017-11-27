//
// Created by showtime on 11/2/2017.
//

#include "so3.h"
#include "../math/mat3.h"

#include <math.h>

static void so3_rodrigues_exp(struct vec3 *w, float k_a, float k_b, mat3 *result)
{
    const float wx2 = w->x * w->x;
    const float wy2 = w->y * w->y;
    const float wz2 = w->z * w->z;
    *mat3_element(result, 0, 0) = 1.0f - k_b * (wy2 + wz2);
    *mat3_element(result, 1, 1) = 1.0f - k_b * (wx2 + wz2);
    *mat3_element(result, 2, 2) = 1.0f - k_b * (wx2 + wy2);
    float a = k_a * w->z;
    float b = k_b * (w->x * w->y);
    *mat3_element(result, 1, 0) = b - a;
    *mat3_element(result, 0, 1) = b + a;
    a = k_a * w->y;
    b = k_b * (w->x * w->z);
    *mat3_element(result, 2, 0) = b + a;
    *mat3_element(result, 0, 2) = b - a;
    a = k_a * w->x;
    b = k_b * (w->y * w->z);
    *mat3_element(result, 2, 1) = b - a;
    *mat3_element(result, 1, 2) = b + a;
}

static void so3_rotation_pi_about_axis(struct vec3 *v, mat3 *result)
{
    struct vec3 rotation_pi_about_axis_tmp;
    vec3_copy(v, &rotation_pi_about_axis_tmp);
    vec3_scale(&rotation_pi_about_axis_tmp, PI / vec3_distance(&rotation_pi_about_axis_tmp));
    const float k_a = 0.0f;
    const float k_b = 0.20264236728467558f;

    so3_rodrigues_exp(&rotation_pi_about_axis_tmp, k_a, k_b, result);
}

void so3_from_two_vec(struct vec3 *a, struct vec3 *b, mat3 *result)
{
    struct vec3 from_two_vec_n_tmp;
    vec3_cross(a, b, &from_two_vec_n_tmp);
    if (vec3_distance(&from_two_vec_n_tmp) == 0)
    {
        const float dot = vec3_dot(a, b);
        if (dot >= 0.0f)
        {
            mat3_identity(result);
        }
        else
        {
            struct vec3 from_two_vec_rotation_axis_tmp;
            vec3_ortho(a, &from_two_vec_rotation_axis_tmp);
            so3_rotation_pi_about_axis(&from_two_vec_rotation_axis_tmp, result);
        }

        return;
    }

    struct vec3 from_two_vec_a_tmp;
    struct vec3 from_two_vec_b_tmp;
    vec3_copy(a, &from_two_vec_a_tmp);
    vec3_copy(b, &from_two_vec_b_tmp);
    vec3_normalize(&from_two_vec_n_tmp);
    vec3_normalize(&from_two_vec_a_tmp);
    vec3_normalize(&from_two_vec_b_tmp);

    struct vec3 vec_tmp;
    vec3_zero(&vec_tmp);
    mat3 r1_tmp;
    mat3_zero(&r1_tmp);
    mat3_set_row(&r1_tmp, 0, &from_two_vec_a_tmp);
    mat3_set_row(&r1_tmp, 1, &from_two_vec_n_tmp);
    vec3_cross(&from_two_vec_n_tmp, &from_two_vec_a_tmp, &vec_tmp);
    mat3_set_row(&r1_tmp, 2, &vec_tmp);

    mat3 r2_tmp;
    mat3_zero(&r2_tmp);
    mat3_set_row(&r2_tmp, 0, &from_two_vec_b_tmp);
    mat3_set_row(&r2_tmp, 1, &from_two_vec_n_tmp);
    vec3_cross(&from_two_vec_n_tmp, &from_two_vec_b_tmp, &vec_tmp);
    mat3_set_row(&r2_tmp, 2, &vec_tmp);

    mat3_transpose(&r1_tmp);
    mat3_mul(&r2_tmp, &r1_tmp, result);
}

void so3_from_mu(struct vec3 *w, mat3 *result)
{
    const float theta_sq = vec3_dot(w, w);
    const float theta = sqrtf(theta_sq);
    float k_a;
    float k_b;
    if (theta_sq < 1.0E-8)
    {
        k_a = 1.0f - 0.1666666716337204f * theta_sq;
        k_b = 0.5;
    }
    else if (theta_sq < 1.0E-6)
    {
        k_b = 0.5f - 0.0416666679084301f * theta_sq;
        k_a = 1.0f - theta_sq * 0.1666666716337204f * (1.0f - 0.1666666716337204f * theta_sq);
    }
    else
    {
        const float inv_theta = 1.0f / theta;
        k_a = sinf(theta) * inv_theta;
        k_b = (1.0f - cosf(theta)) * (inv_theta * inv_theta);
    }

    so3_rodrigues_exp(w, k_a, k_b, result);
}

void so3_to_mu(mat3 *so3, struct vec3 *result)
{
    const float cos_angle = (*mat3_element(so3, 0, 0) + *mat3_element(so3, 1, 1) + *mat3_element(so3, 2, 2) - 1.0f) * 0.5f;
    vec3_set(result,
             (*mat3_element(so3, 1, 2) - *mat3_element(so3, 2, 1)) / 2.0f,
             (*mat3_element(so3, 2, 0) - *mat3_element(so3, 0, 2)) / 2.0f,
             (*mat3_element(so3, 0, 1) - *mat3_element(so3, 1, 0)) / 2.0f);

    const float sin_angle_abs = vec3_distance(result);
    if (cos_angle > 0.7071067811865476f)
    {
        if (sin_angle_abs > 0.0)
        {
            vec3_scale(result, asinf(sin_angle_abs) / sin_angle_abs);
        }
    }
    else if (cos_angle > -0.7071067811865476)
    {
        const float angle = acosf(cos_angle);
        vec3_scale(result, angle / sin_angle_abs);
    }
    else
    {
        const float angle = PI - asinf(sin_angle_abs);
        const float d0 = *mat3_element(so3, 0, 0) - cos_angle;
        const float d1 = *mat3_element(so3, 1, 1) - cos_angle;
        const float d2 = *mat3_element(so3, 2, 2) - cos_angle;
        struct vec3 r2;
        vec3_zero(&r2);
        if ((d0 * d0 > d1 * d1) && (d0 * d0 > d2 * d2))
        {
            vec3_set(&r2, d0, (*mat3_element(so3, 1, 0) + *mat3_element(so3, 0, 1)) / 2.0f, (*mat3_element(so3, 0, 2) + *mat3_element(so3, 2, 0)) / 2.0f);
        }
        else if (d1 * d1 > d2 * d2)
        {
            vec3_set(&r2, (*mat3_element(so3, 1, 0) + *mat3_element(so3, 0, 1)) / 2.0f, d1, (*mat3_element(so3, 2, 1) + *mat3_element(so3, 1, 2)) / 2.0f);
        }
        else
        {
            vec3_set(&r2,(*mat3_element(so3, 0, 2) + *mat3_element(so3, 2, 0)) / 2.0f, (*mat3_element(so3, 2, 1) + *mat3_element(so3, 1, 2)) / 2.0f, d2);
        }

        if (vec3_dot(&r2, result) < 0.0f)
        {
            vec3_scale(&r2, -1.0f);
        }

        vec3_normalize(&r2);
        vec3_scale(&r2, angle);
        vec3_copy(&r2, result);
    }
}

