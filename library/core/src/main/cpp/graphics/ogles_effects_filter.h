//
// Created by showtime on 11/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_EFFECTS_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_EFFECTS_FILTER_H

#include "ogles.h"
#include "../utils/vec.h"
#include "../geometry/primitive_type.h"
#include "ogles_filter.h"

struct ogles_effects_filter
{
    struct ogles_filter_base base;
    vec_void_t vec;
};

void ogles_effects_filter_init(struct ogles_effects_filter *group);

void ogles_effects_filter_add(struct ogles_effects_filter *group, uint32_t filter_type, primitive_type primitive_type);

void ogles_effects_filter_remove(struct ogles_effects_filter *group, uint32_t filter_type);

void ogles_effects_filter_release(struct ogles_effects_filter *group);

void ogles_effects_filter_safe_release(struct ogles_effects_filter *group);

void ogles_effects_filter_resize(struct ogles_effects_filter *group, GLint width, GLint height);

void ogles_effects_filter_draw(struct ogles_effects_filter *group, GLuint *texture);

void ogles_effects_filter_pre_draw(struct ogles_effects_filter *group);

void ogles_effects_filter_post_draw(struct ogles_effects_filter *group);

#endif //EXOGFX_GRAPHICS_OGLES_EFFECTS_FILTER_H
