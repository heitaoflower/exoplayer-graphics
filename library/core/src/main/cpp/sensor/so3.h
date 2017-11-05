//
// Created by showtime on 11/2/2017.
//

#ifndef EXOGFX_SO3_H
#define EXOGFX_SO3_H

#include "../math/vec3.h"

void so3_from_two_vec(struct vec3 *a, struct vec3 *b, mat3 *result);

void so3_from_mu(struct vec3 *w, mat3 *result);

void so3_to_mu(mat3 *so3, struct vec3 *result);

#endif //EXOGFX_SO3_H
