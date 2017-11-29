//
// Created by showtime on 10/28/2017.
//

#include "vec3_ext.h"
#include <math.h>

float vec3_max(struct vec3* vec)
{
    float max;

    max = vec->x;
    if (vec->y > max)
    {
        max = vec->y;
    }

    if (vec->z > max)
    {
        max = vec->z;
    }

    return max;
}

float vec3_min(struct vec3* vec)
{
    float min;

    min = vec->x;
    if (vec->y < min)
    {
        min = vec->y;
    }

    if (vec->z < min)
    {
        min = vec->z;
    }

    return min;
}

int vec3_min_index(struct vec3 *vec, bool abs)
{
    float x = abs ? fabsf(vec->x) : vec->x;
    float y = abs ? fabsf(vec->y) : vec->y;
    float z = abs ? fabsf(vec->z) : vec->z;

    if (x < y)
    {
        if (x < z)
        {
            return 0;
        }

        return 2;
    }
    else
    {
        if (y < z)
        {
            return 1;
        }

        return 2;
    }
}

int vec3_max_index(struct vec3 *vec, bool abs)
{
    float x = abs ? fabsf(vec->x) : vec->x;
    float y = abs ? fabsf(vec->y) : vec->y;
    float z = abs ? fabsf(vec->z) : vec->z;

    if (x > y)
    {
        if (x > z)
        {
            return 0;
        }

        return 2;
    }
    else
    {
        if (y > z)
        {
            return 1;
        }

        return 2;
    }
}
