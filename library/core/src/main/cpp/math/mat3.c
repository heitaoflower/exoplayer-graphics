//
// Created by showtime on 9/12/2017.
//

#include "mat3.h"

#include <string.h>

float* mat3_element(mat3 *mat, int row, int col)
{
    return (float*)mat + (row + col * 3);
}

void mat3_copy(mat3 *src, mat3 *dst)
{
    *mat3_element(dst, 0, 0) = *mat3_element(src, 0, 0);
    *mat3_element(dst, 0, 1) = *mat3_element(src, 0, 1);
    *mat3_element(dst, 0, 2) = *mat3_element(src, 0, 2);

    *mat3_element(dst, 1, 0) = *mat3_element(src, 1, 0);
    *mat3_element(dst, 1, 1) = *mat3_element(src, 1, 1);
    *mat3_element(dst, 1, 2) = *mat3_element(src, 1, 2);

    *mat3_element(dst, 2, 0) = *mat3_element(src, 2, 0);
    *mat3_element(dst, 2, 1) = *mat3_element(src, 2, 1);
    *mat3_element(dst, 2, 2) = *mat3_element(src, 2, 2);
}

void mat3_set(mat3 *mat, float e00, float e01, float e02, float e10, float e11, float e12, float e20, float e21, float e22)
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

void mat3_set_same(mat3 *mat, float value)
{
    *mat3_element(mat, 0, 0) = value;
    *mat3_element(mat, 1, 1) = value;
    *mat3_element(mat, 2, 2) = value;
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

void mat3_set_col(mat3 *mat, int col, struct vec3 *vec)
{
    *mat3_element(mat, 0, col) = vec->x;
    *mat3_element(mat, 1, col) = vec->y;
    *mat3_element(mat, 2, col) = vec->z;
}

void mat3_get_col(mat3 *mat, int col, struct vec3 *vec)
{
    vec->x = *mat3_element(mat, 0, col);
    vec->y = *mat3_element(mat, 1, col);
    vec->z = *mat3_element(mat, 2, col);
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
    float a00 = *mat3_element(src1, 0, 0), a01 = *mat3_element(src1, 0, 1), a02 = *mat3_element(src1, 0, 2),
          a10 = *mat3_element(src1, 1, 0), a11 = *mat3_element(src1, 1, 1), a12 = *mat3_element(src1, 1, 2),
          a20 = *mat3_element(src1, 2, 0), a21 = *mat3_element(src1, 2, 1), a22 = *mat3_element(src1, 2, 2);

    float b00 = *mat3_element(src2, 0, 0), b01 = *mat3_element(src2, 0, 1), b02 = *mat3_element(src2, 0, 2),
          b10 = *mat3_element(src2, 1, 0), b11 = *mat3_element(src2, 1, 1), b12 = *mat3_element(src2, 1, 2),
          b20 = *mat3_element(src2, 2, 0), b21 = *mat3_element(src2, 2, 1), b22 = *mat3_element(src2, 2, 2);

    *mat3_element(dst, 0, 0) = a00 + b00;
    *mat3_element(dst, 0, 1) = a01 + b01;
    *mat3_element(dst, 0, 2) = a02 + b02;
    *mat3_element(dst, 1, 0) = a10 + b10;
    *mat3_element(dst, 1, 1) = a11 + b11;
    *mat3_element(dst, 1, 2) = a12 + b12;
    *mat3_element(dst, 2, 0) = a20 + b20;
    *mat3_element(dst, 2, 1) = a21 + b21;
    *mat3_element(dst, 2, 2) = a22 + b22;
}

void mat3_sub(mat3 *src1, mat3 *src2, mat3 *dst)
{
    float a00 = *mat3_element(src1, 0, 0), a01 = *mat3_element(src1, 0, 1), a02 = *mat3_element(src1, 0, 2),
          a10 = *mat3_element(src1, 1, 0), a11 = *mat3_element(src1, 1, 1), a12 = *mat3_element(src1, 1, 2),
          a20 = *mat3_element(src1, 2, 0), a21 = *mat3_element(src1, 2, 1), a22 = *mat3_element(src1, 2, 2);

    float b00 = *mat3_element(src2, 0, 0), b01 = *mat3_element(src2, 0, 1), b02 = *mat3_element(src2, 0, 2),
          b10 = *mat3_element(src2, 1, 0), b11 = *mat3_element(src2, 1, 1), b12 = *mat3_element(src2, 1, 2),
          b20 = *mat3_element(src2, 2, 0), b21 = *mat3_element(src2, 2, 1), b22 = *mat3_element(src2, 2, 2);

    *mat3_element(dst, 0, 0) = a00 - b00;
    *mat3_element(dst, 0, 1) = a01 - b01;
    *mat3_element(dst, 0, 2) = a02 - b02;
    *mat3_element(dst, 1, 0) = a10 - b10;
    *mat3_element(dst, 1, 1) = a11 - b11;
    *mat3_element(dst, 1, 2) = a12 - b12;
    *mat3_element(dst, 2, 0) = a20 - b20;
    *mat3_element(dst, 2, 1) = a21 - b21;
    *mat3_element(dst, 2, 2) = a22 - b22;
}

void mat3_multiply_mm(mat3 *src1, mat3 *src2, mat3 *dst)
{
    float a00 = *mat3_element(src1, 0, 0), a01 = *mat3_element(src1, 0, 1), a02 = *mat3_element(src1, 0, 2),
          a10 = *mat3_element(src1, 1, 0), a11 = *mat3_element(src1, 1, 1), a12 = *mat3_element(src1, 1, 2),
          a20 = *mat3_element(src1, 2, 0), a21 = *mat3_element(src1, 2, 1), a22 = *mat3_element(src1, 2, 2);

    float b00 = *mat3_element(src2, 0, 0), b01 = *mat3_element(src2, 0, 1), b02 = *mat3_element(src2, 0, 2),
          b10 = *mat3_element(src2, 1, 0), b11 = *mat3_element(src2, 1, 1), b12 = *mat3_element(src2, 1, 2),
          b20 = *mat3_element(src2, 2, 0), b21 = *mat3_element(src2, 2, 1), b22 = *mat3_element(src2, 2, 2);

    *mat3_element(dst, 0, 0) = a00 * b00 + a10 * b01 + a20 * b02;
    *mat3_element(dst, 0, 1) = a01 * b00 + a11 * b01 + a21 * b02;
    *mat3_element(dst, 0, 2) = a02 * b00 + a12 * b01 + a22 * b02;
    *mat3_element(dst, 1, 0) = a00 * b10 + a10 * b11 + a20 * b12;
    *mat3_element(dst, 1, 1) = a01 * b10 + a11 * b11 + a21 * b12;
    *mat3_element(dst, 1, 2) = a02 * b10 + a12 * b11 + a22 * b12;
    *mat3_element(dst, 2, 0) = a00 * b20 + a10 * b21 + a20 * b22;
    *mat3_element(dst, 2, 1) = a01 * b20 + a11 * b21 + a21 * b22;
    *mat3_element(dst, 2, 2) = a02 * b20 + a12 * b21 + a22 * b22;
}

void mat3_multiply_mv(mat3 *src1, struct vec3 *src2, struct vec3 *dst)
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