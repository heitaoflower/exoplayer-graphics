//
// Created by showtime on 9/12/2017.
//

#ifndef EXOGFX_MATH_MAT4_H
#define EXOGFX_MATH_MAT4_H

#include "../utils/math_util.h"

float* mat4_element(mat4 *mat, int row, int col);

void mat4_identity(mat4 *mat);

void mat4_zero(mat4 *mat);

void mat4_multiply(mat4 *dst, mat4 *src1, mat4 *src2);

void mat4_rotate_euler(mat4 *dst, float x, float y, float z);

void mat4_perspective(mat4 *mat, float fovy, float aspect, float zNear, float zFar);

void mat4_perspective_default(mat4 *mat, float aspect);

void mat4_ortho(mat4 *mat, float left, float right, float bottom, float top, float nearVal, float farVal);

void mat4_ortho_default(mat4 *mat, float aspect);

void mat4_frustum(mat4 *mat, float left, float right, float bottom, float top, float nearVal, float farVal);

void mat4_frustum_default(mat4 *mat, float aspect);

void mat4_lookat(mat4 *mat, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

void mat4_set_translate(mat4 *mat, float x, float y, float z);

void mat4_translate(mat4 *mat, float x, float y, float z);

void mat4_rotate(mat4 *mat, float angle, float x, float y, float z);

void mat4_set_rotate(mat4 *mat, float angle, float x, float y, float z);

void mat4_scale(mat4 *mat, float x, float y, float z);

void mat4_set_scale(mat4 *mat, float x, float y, float z);

void mat4_print(mat4 *mat);

#endif //EXOGFX_MATH_MAT4_H
