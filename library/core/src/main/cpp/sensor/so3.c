//
// Created by showtime on 11/2/2017.
//

#include "so3.h"
#include "../math/mat3.h"

static void so3_rodrigues_exp(struct vec3 *w, float k_a, float k_b, mat3 *result)
{
    const float wx2 = w->x * w->x;
    const float wy2 = w->y * w->y;
    const float wz2 = w->z * w->z;
    *mat3_element(result, 0, 0) = 1.0f - k_b * (wy2 + wz2);
    *mat3_element(result, 0, 0) = 1.0f - k_b * (wx2 + wz2);
    *mat3_element(result, 0, 0) = 1.0f - k_b * (wx2 + wy2);
    float a = k_a * w->z;
    float b = k_b * (w->x * w->y);
    *mat3_element(result, 0, 1) = b - a;
    *mat3_element(result, 1, 0) = b + a;
    a = k_a * w->y;
    b = k_b * (w->x * w->z);
    *mat3_element(result, 0, 2) = b + a;
    *mat3_element(result, 2, 0) = b - a;
    a = k_a * w->x;
    b = k_b * (w->y * w->z);
    *mat3_element(result, 1, 2) = b - a;
    *mat3_element(result, 2, 1) = b + a;
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
}


void so3_from_mu(struct vec3 *w, mat3 *result)
{

}

void so3_to_mu(mat3 *so3, struct vec3 *result)
{

}

