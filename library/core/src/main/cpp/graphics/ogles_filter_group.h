//
// Created by showtime on 11/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_FILTER_GROUP_H
#define EXOGFX_GRAPHICS_OGLES_FILTER_GROUP_H

#include "ogles.h"
#include "../utils/vec.h"

struct ogles_filter_group
{
    vec_void_t vec;
};

void ogles_filter_group_init(struct ogles_filter_group *group);

void ogles_filter_group_add(struct ogles_filter_group *group);

void ogles_filter_group_remove(struct ogles_filter_group *group);

void ogles_filter_group_release(struct ogles_filter_group *group);

void ogles_filter_group_safe_release(struct ogles_filter_group *group);

void ogles_filter_group_resize(struct ogles_filter_group *group, GLint width, GLint height);

void ogles_filter_group_draw(struct ogles_filter_group *group, GLuint texture);

void ogles_filter_group_pre_draw(struct ogles_filter_group *group);

void ogles_filter_group_post_draw(struct ogles_filter_group *group);

#endif //EXOGFX_GRAPHICS_OGLES_FILTER_GROUP_H
