//
// Created by showtime on 9/12/2017.
//

#ifndef EXOGFX_MATH_VEC3_H
#define EXOGFX_MATH_VEC3_H

#include "../utils/math_util.h"

void vec3_set(struct vec3 *vec, float x, float y, float z);

void vec3_set_component(struct vec3 *vec, int index, float value);

void vec3_zero(struct vec3 *vec);

void vec3_scale(struct vec3 *vec, float scalar);

void vec3_normalize(struct vec3 *vec);

float vec3_dot(struct vec3 *src1, struct vec3 *src2);

float vec3_distance(struct vec3 * vec);

bool vec3_same(struct vec3 *src1, struct vec3 *src2);

void vec3_add(struct vec3 *src1, struct vec3 *src2, struct vec3* dst);

void vec3_sub(struct vec3 *src1, struct vec3 *src2, struct vec3* dst);

void vec3_cross(struct vec3 *src1, struct vec3 *src2, struct vec3 *dst);

void vec3_ortho(struct vec3 *src, struct vec3* dst);

#endif //EXOPLAYER_MATH_VEC3_H
