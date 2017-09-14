//
// Created by showtime on 9/12/2017.
//

#ifndef EXOPLAYER_MATH_MAT4_H
#define EXOPLAYER_MATH_MAT4_H

#include "math.h"


float* mat4_get(float *mat4, int row, int col);

void mat4_identity(float *mat4);

void mat4_multiply(float *dst, float *src1, float *src2);

void mat4_perspective(float *mat4, float fovy, float aspect, float zNear, float zFar);

void mat4_frustum(float *mat4, float left, float right, float bottom, float top, float nearVal, float farVal);

void mat4_lookat(float *mat4, float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);

void mat4_translate(float *mat4, float x, float y, float z);

void mat4_rotate(float *mat4, float angle, float x, float y, float z);

#endif //EXOPLAYER_MATH_MAT4_H
