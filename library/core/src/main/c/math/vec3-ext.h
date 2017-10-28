//
// Created by showtime on 10/28/2017.
//

#ifndef EXOGFX_VEC3_EXT_H
#define EXOGFX_VEC3_EXT_H

#include "../utils/math_util.h"

float vec3_max(struct vec3* vec);

float vec3_min(struct vec3* vec);

int vec3_max_index(struct vec3 *vec, bool abs);

int vec3_min_index(struct vec3 *vec, bool abs);

#endif //EXOGFX_VEC3_EXT_H
