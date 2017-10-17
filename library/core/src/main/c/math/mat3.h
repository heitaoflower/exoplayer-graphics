//
// Created by showtime on 9/12/2017.
//

#ifndef EXOGFX_MATH_MAT3_H
#define EXOGFX_MATH_MAT3_H

#include "../utils/math_util.h"

float* mat3_element(mat3 *mat, int row, int col);

void mat3_zero(mat3 *mat);

void mat3_identity(mat3 *mat);

void mat3_scale(mat3 *mat, float scalar);

void mat3_add(mat3 *src1, mat3 *src2, mat3 *dst);

void mat3_sub(mat3 *src1, mat3 *src2, mat3 *dst);

void mat3_mul(mat3 *src1, mat3 *src2, mat3 *dst);

void mat3_mulv(mat3 *mat, struct vec3 *vec, struct vec3 *dst);

void mat3_transpose(mat3 *src, mat3 *dst);

float mat3_determinant(mat3 *mat);

void mat3_invert(mat3 *src, mat3 *dst);

#endif //EXOGFX_MATH_MAT3_H
