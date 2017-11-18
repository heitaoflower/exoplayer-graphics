//
// Created by showtime on 11/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_INVERT_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_INVERT_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../geometry/primitive.h"

struct ogles_invert_filter
{
    struct ogles_filter_base base;

    struct
    {
        struct uniform sTexture;
    } uniforms;

    struct
    {
        struct attribute aPosition;
        struct attribute aTextureCoord;
    } attributes;
};

ogles_filter_create(invert)
(void);

ogles_filter_init(invert)
(struct ogles_filter_base *filter, primitive_type primitive, bool create_fbo);

ogles_filter_release(invert)
(struct ogles_filter_base *filter);

ogles_filter_safe_release(invert)
(struct ogles_filter_base *filter);

ogles_filter_resize(invert)
(struct ogles_filter_base *filter, GLint width, GLint height);

ogles_filter_draw(invert)
(struct ogles_filter_base *filter, GLuint texture);

ogles_filter_pre_draw(invert)
(struct ogles_invert_filter *filter);

ogles_filter_post_draw(invert)
(struct ogles_invert_filter *filter);

ogles_filter_use_program(invert)
(struct ogles_invert_filter *filter);

ogles_filter_register_handle(invert)
(struct ogles_invert_filter *filter);

#endif // EXOGFX_GRAPHICS_OGLES_INVERT_FILTER_H
