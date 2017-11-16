//
// Created by showtime on 11/10/2017.
//

#include "ogles_effects_filter.h"
#include "ogles_filter.h"
#include "ogles_gray_filter.h"
#include "ogles_invert_filter.h"
#include "../geometry/primitive.h"
#include "../utils/vec.h"

void ogles_effects_filter_init(struct ogles_effects_filter *group)
{
    vec_init(&group->vec);
}

void ogles_effects_filter_add(struct ogles_effects_filter *group, uint32_t filter_type)
{
    if (filter_type == FILTER_TYPE_GRAY)
    {
        struct ogles_gray_filter *gray_filter = ogles_gray_filter_create();
        gray_filter->base.init((struct ogles_filter_base*)gray_filter, create_primitive(PrimitiveTypeQuad));
        vec_push(&group->vec, gray_filter);
    }
    else if (filter_type == FILTER_TYPE_INVERT)
    {
        struct ogles_invert_filter *invert_filter = ogles_invert_filter_create();
        invert_filter->base.init((struct ogles_filter_base*)invert_filter, create_primitive(PrimitiveTypeQuad));
        vec_push(&group->vec, invert_filter);
    }
}

void ogles_effects_filter_remove(struct ogles_effects_filter *group, uint32_t filter_type)
{
    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i) {

            if (filter->type == filter_type)
            {
                vec_remove(&group->vec, filter);
                filter->release(filter);
            }
        }
}

void ogles_effects_filter_release(struct ogles_effects_filter *group)
{
    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i) {
            filter->release(filter);
        }

    vec_clear(&group->vec);
}

void ogles_effects_filter_safe_release(struct ogles_effects_filter *group)
{
    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i) {
            filter->safe_release(filter);
        }

    vec_clear(&group->vec);
}

void ogles_effects_filter_resize(struct ogles_effects_filter *group, GLint width, GLint height)
{
    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i) {
            filter->resize(filter, width, height);
        }
}

void ogles_effects_filter_draw(struct ogles_effects_filter *group, GLuint texture)
{
    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i){
            filter->draw(filter, texture);
        }
}
