//
// Created by showtime on 9/12/2017.
//

#include "mat3.h"

#include <string.h>

float* mat3_element(mat3 *mat, int row, int col)
{
    return (float*)mat + (row + col * 3);
}

void mat3_set(mat3* mat, float e00, float e01, float e02, float e10, float e11, float e12, float e20, float e21, float e22)
{
    *mat3_element(mat, 0, 0) = e00;
    *mat3_element(mat, 0, 1) = e01;
    *mat3_element(mat, 0, 2) = e02;

    *mat3_element(mat, 1, 0) = e10;
    *mat3_element(mat, 1, 1) = e11;
    *mat3_element(mat, 1, 2) = e12;

    *mat3_element(mat, 2, 0) = e20;
    *mat3_element(mat, 2, 1) = e21;
    *mat3_element(mat, 2, 2) = e22;
}

void mat3_set_row(mat3 *mat, int row, struct vec3 *vec)
{
    *mat3_element(mat, row, 0) = vec->x;
    *mat3_element(mat, row, 1) = vec->y;
    *mat3_element(mat, row, 2) = vec->z;
}

void mat3_get_row(mat3 *mat, int row, struct vec3 *vec)
{
    vec->x = *mat3_element(mat, row, 0);
    vec->y = *mat3_element(mat, row, 1);
    vec->z = *mat3_element(mat, row, 2);
}

void mat3_zero(mat3 *mat)
{
    memset(mat, 0, sizeof(*mat));
}

void mat3_identity(mat3 *mat)
{
    mat3_zero(mat);

    for (int i = 0; i < 3; i++)
    {
        *mat3_element(mat, i, i) = 1.0f;
    }
}

void mat3_scale(mat3 *mat, float scalar)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            *mat3_element(mat, i, j) *= scalar;
        }
    }
}

void mat3_add(mat3 *src1, mat3 *src2, mat3 *dst)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            *mat3_element(dst, i, j) = *mat3_element(src1, i, j) + *mat3_element(src2, i, j);
        }
    }
}

void mat3_sub(mat3 *src1, mat3 *src2, mat3 *dst)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            *mat3_element(dst, i, j) = *mat3_element(src1, i, j) - *mat3_element(src2, i, j);
        }
    }
}

void mat3_mul(mat3 *src1, mat3 *src2, mat3 *dst)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            *mat3_element(dst, j, i) =
                *mat3_element(src1, 0, i) * *mat3_element(src2, j, 0) +
                *mat3_element(src1, 1, i) * *mat3_element(src2, j, 1) +
                *mat3_element(src1, 2, i) * *mat3_element(src2, j, 2);
        }
    }
}

void mat3_mulv(mat3 *src1, struct vec3 *src2, struct vec3 *dst)
{
    dst->x = *mat3_element(src1, 0, 0) * src2->x + *mat3_element(src1, 1, 0) * src2->y + *mat3_element(src1, 2, 0) * src2->z;
    dst->y = *mat3_element(src1, 0, 1) * src2->x + *mat3_element(src1, 1, 1) * src2->y + *mat3_element(src1, 2, 1) * src2->z;
    dst->z = *mat3_element(src1, 0, 2) * src2->x + *mat3_element(src1, 1, 2) * src2->y + *mat3_element(src1, 2, 2) * src2->z;
}

void mat3_transpose(mat3 *mat)
{
    mat3 tmp;

    *mat3_element(&tmp, 0, 1) = *mat3_element(mat, 1, 0);
    *mat3_element(&tmp, 0, 2) = *mat3_element(mat, 2, 0);
    *mat3_element(&tmp, 1, 0) = *mat3_element(mat, 0, 1);
    *mat3_element(&tmp, 1, 2) = *mat3_element(mat, 2, 1);
    *mat3_element(&tmp, 2, 0) = *mat3_element(mat, 0, 2);
    *mat3_element(&tmp, 2, 1) = *mat3_element(mat, 1, 2);

    *mat3_element(mat, 0, 1) = *mat3_element(&tmp, 0, 1);
    *mat3_element(mat, 0, 2) = *mat3_element(&tmp, 0, 2);
    *mat3_element(mat, 1, 0) = *mat3_element(&tmp, 1, 0);
    *mat3_element(mat, 1, 2) = *mat3_element(&tmp, 1, 2);
    *mat3_element(mat, 2, 0) = *mat3_element(&tmp, 2, 0);
    *mat3_element(mat, 2, 1) = *mat3_element(&tmp, 2, 1);
}

void mat3_transpose_to(mat3 *src, mat3 *dst)
{
    *mat3_element(dst, 0, 0) = *mat3_element(src, 0, 0);
    *mat3_element(dst, 0, 1) = *mat3_element(src, 1, 0);
    *mat3_element(dst, 0, 2) = *mat3_element(src, 2, 0);
    *mat3_element(dst, 1, 0) = *mat3_element(src, 0, 1);
    *mat3_element(dst, 1, 1) = *mat3_element(src, 1, 1);
    *mat3_element(dst, 1, 2) = *mat3_element(src, 2, 1);
    *mat3_element(dst, 2, 0) = *mat3_element(src, 0, 2);
    *mat3_element(dst, 2, 1) = *mat3_element(src, 1, 2);
    *mat3_element(dst, 2, 2) = *mat3_element(src, 2, 2);

}

float mat3_determinant(mat3 *mat)
{
    float a = *mat3_element(mat, 0, 0), b = *mat3_element(mat, 0, 1), c = *mat3_element(mat, 0, 2),
          d = *mat3_element(mat, 1, 0), e = *mat3_element(mat, 1, 1), f = *mat3_element(mat, 1, 2),
          g = *mat3_element(mat, 2, 0), h = *mat3_element(mat, 2, 1), i = *mat3_element(mat, 2, 2);

    return a * (e * i - h * f) - d * (b * i - c * h) + g * (b * f - c * e);
}

void mat3_invert(mat3 *src, mat3 *dst)
{
    float a = *mat3_element(src, 0, 0), b = *mat3_element(src, 0, 1), c = *mat3_element(src, 0, 2),
          d = *mat3_element(src, 1, 0), e = *mat3_element(src, 1, 1), f = *mat3_element(src, 1, 2),
          g = *mat3_element(src, 2, 0), h = *mat3_element(src, 2, 1), i = *mat3_element(src, 2, 2);

    *mat3_element(dst, 0, 0) = e * i - f * h;
    *mat3_element(dst, 0, 1) = -(b * i - h * c);
    *mat3_element(dst, 0, 2) =   b * f - e * c;
    *mat3_element(dst, 1, 0) = -(d * i - g * f);
    *mat3_element(dst, 1, 1) =   a * i - c * g;
    *mat3_element(dst, 1, 2) = -(a * f - d * c);
    *mat3_element(dst, 2, 0) =   d * h - g * e;
    *mat3_element(dst, 2, 1) = -(a * h - g * b);
    *mat3_element(dst, 2, 2) =   a * e - b * d;

    float det = 1.0f / (a * *mat3_element(dst, 0, 0) + b * *mat3_element(dst, 1, 0) + c * *mat3_element(dst, 2, 0));

    mat3_scale(dst, det);
}