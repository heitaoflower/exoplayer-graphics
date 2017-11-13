//
// Created by showtime on 11/10/2017.
//

#include "ogles_filter_group.h"
#include "ogles_filter.h"
#include "ogles_gray_filter.h"
#include "../geometry/primitive.h"
#include "../utils/log_util.h"
#include "../utils/vec.h"

void ogles_filter_group_init(struct ogles_filter_group *group)
{
    vec_init(&group->vec);
}

void ogles_filter_group_add(struct ogles_filter_group *group, uint32_t filter_type)
{
    if (filter_type == FILTER_TYPE_GRAY)
    {
        struct ogles_gray_filter *gray_filter = ogles_gray_filter_create();
        ogles_gray_filter_init(gray_filter, create_primitive(PrimitiveTypeQuad));
        vec_push(&group->vec, gray_filter);
    }
}

void ogles_filter_group_remove(struct ogles_filter_group *group, uint32_t filter_type)
{
    int i; void* filter;
    vec_foreach(&group->vec, filter, i) {

            if (((struct ogles_filter_base*)filter)->type == filter_type)
            {
                vec_remove(&group->vec, filter);
            }
        }
}

void ogles_filter_group_release(struct ogles_filter_group *group)
{
    int i; void* filter;
    vec_foreach(&group->vec, filter, i) {

            if (((struct ogles_filter_base*)filter)->type == FILTER_TYPE_GRAY)
            {
                struct ogles_gray_filter* gray_filter = (struct ogles_gray_filter*)filter;
                ogles_gray_filter_release(gray_filter);
            }
        }

    vec_clear(&group->vec);
}

void ogles_filter_group_safe_release(struct ogles_filter_group *group)
{
    int i; void* filter;
    vec_foreach(&group->vec, filter, i) {

            if (((struct ogles_filter_base*)filter)->type == FILTER_TYPE_GRAY)
            {
                struct ogles_gray_filter* gray_filter = (struct ogles_gray_filter*)filter;
                ogles_gray_filter_safe_release(gray_filter);
            }
        }

    vec_clear(&group->vec);
}

void ogles_filter_group_resize(struct ogles_filter_group *group, GLint width, GLint height)
{
    int i; void* filter;
    vec_foreach(&group->vec, filter, i) {

            if (((struct ogles_filter_base*)filter)->type == FILTER_TYPE_GRAY)
            {
                struct ogles_gray_filter* gray_filter = (struct ogles_gray_filter*)filter;
                ogles_gray_filter_resize(gray_filter, width, height);
            }
        }
}

void ogles_filter_group_pre_draw(struct ogles_filter_group *group)
{
    int i; void* filter;
    vec_foreach(&group->vec, filter, i) {

            if (((struct ogles_filter_base*)filter)->type == FILTER_TYPE_GRAY)
            {
                struct ogles_gray_filter* gray_filter = (struct ogles_gray_filter*)filter;
                ogles_gray_filter_pre_draw(gray_filter);
            }
        }
}

void ogles_filter_group_draw(struct ogles_filter_group *group, GLuint texture)
{
    ogles_filter_group_pre_draw(group);

    int i; void* filter;
    vec_foreach(&group->vec, filter, i) {

            if (((struct ogles_filter_base*)filter)->type == FILTER_TYPE_GRAY)
            {
                struct ogles_gray_filter* gray_filter = (struct ogles_gray_filter*)filter;
                ogles_gray_filter_draw(gray_filter, texture);
            }
        }

    ogles_filter_group_post_draw(group);
}

void ogles_filter_group_post_draw(struct ogles_filter_group *group)
{
    int i; void* filter;
    vec_foreach(&group->vec, filter, i) {

            if (((struct ogles_filter_base*)filter)->type == FILTER_TYPE_GRAY)
            {
                struct ogles_gray_filter* gray_filter = (struct ogles_gray_filter*)filter;
                ogles_gray_filter_post_draw(gray_filter);
            }
        }
}
