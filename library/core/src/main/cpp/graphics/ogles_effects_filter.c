//
// Created by showtime on 11/10/2017.
//

#include "ogles_effects_filter.h"
#include "ogles_filter.h"
#include "ogles_gray_filter.h"
#include "ogles_invert_filter.h"
#include "ogles_vignette_filter.h"
#include "../geometry/primitive.h"
#include "../utils/vec.h"

void ogles_effects_filter_init(struct ogles_effects_filter *group)
{
    vec_init(&group->vec);
    group->fbo = (struct ogles_fbo*)malloc(sizeof(struct ogles_fbo));
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
    else if (filter_type == FILTER_TYPE_VIGNETTE)
    {
        struct ogles_vignette_filter *vignette_filter = ogles_vignette_filter_create();
        vignette_filter->base.init((struct ogles_filter_base*)vignette_filter, create_primitive(PrimitiveTypeQuad));
        vec_push(&group->vec, vignette_filter);
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
    ogles_fbo_release(group->fbo);

    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i) {
            filter->release(filter);
        }

    vec_clear(&group->vec);
}

void ogles_effects_filter_safe_release(struct ogles_effects_filter *group)
{
    ogles_fbo_safe_release(group->fbo);

    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i) {
            filter->safe_release(filter);
        }

    vec_clear(&group->vec);
}

void ogles_effects_filter_resize(struct ogles_effects_filter *group, GLint width, GLint height)
{
    ogles_fbo_resize(group->fbo, width, height);

    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i) {
            filter->resize(filter, width, height);
        }
}

void ogles_effects_filter_pre_draw(struct ogles_effects_filter *group)
{

}

void ogles_effects_filter_post_draw(struct ogles_effects_filter *group)
{

}

void ogles_effects_filter_draw(struct ogles_effects_filter *group, GLuint texture)
{
    ogles_effects_filter_pre_draw(group);

    int i; struct ogles_filter_base* filter;
    vec_foreach(&group->vec, filter, i){
            filter->draw(filter, texture);
        }

    ogles_effects_filter_post_draw(group);
}
