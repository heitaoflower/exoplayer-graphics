//
// Created by showtime on 9/12/2017.
//

#include "vec3.h"

#include <math.h>

void vec3_set(struct vec3 * vec, float x, float y, float z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

void vec3_set_component(struct vec3 *vec, int index, float value)
{
    if (index == 0)
    {
        vec->x = value;
    }
    else if (index == 1)
    {
        vec->y = value;
    }
    else
    {
        vec->z = value;
    }
}

void vec3_zero(struct vec3 *vec)
{
    vec->x = 0;
    vec->y = 0;
    vec->z = 0;
}

void vec3_scale(struct vec3 *vec, float scalar)
{
    vec->x *= scalar;
    vec->y *= scalar;
    vec->z *= scalar;
}

void vec3_normalize(struct vec3 *vec)
{
    float distance = vec3_distance(vec);

    if (distance != 0.0)
    {
        vec3_scale(vec, 1.0f / distance);
    }
}

float vec3_dot(struct vec3 *src1, struct vec3 *src2)
{
    return src1->x * src2->x + src1->y * src2->y + src1->z * src2->z;
}

float vec3_distance(struct vec3 *vec)
{
    return sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
}

bool vec3_same(struct vec3 *src1, struct vec3 *src2)
{
    return src1->x == src2->x && src1->y == src2->y && src1->z == src2->z;
}

void vec3_add(struct vec3 *src1, struct vec3 *src2, struct vec3 *dst)
{
    vec3_set(dst, src1->x + src2->x, src1->y + src2->y, src1->z + src2->z);
}

void vec3_sub(struct vec3 *src1, struct vec3 *src2, struct vec3 *dst)
{
    vec3_set(dst, src1->x - src2->x, src1->y - src2->y, src1->z - src2->z);
}

void vec3_cross(struct vec3 *src1, struct vec3 *src2, struct vec3 *dst)
{
    vec3_set(dst, src1->y * src2->z - src1->z * src2->y, src1->z * src2->x - src1->x * src2->z, src1->x * src2->y - src1->y * src2->x);
}

void vec3_ortho(struct vec3 *src, struct vec3 *dst)
{
    int index = vec3_largest_component_abs(src) - 1;
    vec3_zero(dst);
    vec3_set_component(dst, index < 0 ? 2 : index, 1.0);
    vec3_cross(src, dst, dst);
    vec3_normalize(dst);
}

int vec3_largest_component_abs(struct vec3 *vec)
{
    float x_abs = fabsf(vec->x);
    float y_abs = fabsf(vec->y);
    float z_abs = fabsf(vec->z);

    if (x_abs > y_abs)
    {
        if (x_abs > z_abs)
        {
            return 0;
        }

        return 2;
    }
    else
    {
        if (y_abs > z_abs)
        {
            return 1;
        }

        return 2;
    }
}
