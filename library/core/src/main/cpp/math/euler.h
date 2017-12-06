//
// Created by showtime on 12/4/2017.
//

#ifndef EXOGFX_MATH_EULER_H
#define EXOGFX_MATH_EULER_H

#include "vec3.h"

typedef enum euler_order
{
    EulerXYZ = 0 << 0 | 1 << 2 | 2 << 4,
    EulerXZY = 0 << 0 | 2 << 2 | 1 << 4,
    EulerYZX = 1 << 0 | 2 << 2 | 0 << 4,
    EulerYXZ = 1 << 0 | 0 << 2 | 2 << 4,
    EUlerZXY = 2 << 0 | 0 << 2 | 1 << 4,
    EulerZYX = 2 << 0 | 1 << 2 | 0 << 4
} euler_order;

void euler_angles(mat4 *src, struct vec3 *dst);

void euler_xyz(struct vec3 *angles, mat4 *dst);

void euler_xzy(struct vec3 *angles, mat4 *dst);

void euler_zyx(struct vec3 *angles, mat4 *dst);

void euler_zxy(struct vec3 *angles, mat4 *dst);

void euler_yzx(struct vec3 *angles, mat4 *dst);

void euler_yxz(struct vec3 *angles, mat4 *dst);

#endif //EXOGFX_MATH_EULER_H
