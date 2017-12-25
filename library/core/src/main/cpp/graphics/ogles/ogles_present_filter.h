//
// Created by showtime on 9/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_PRESENT_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_PRESENT_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../../geometry/primitive.h"

struct ogles_present_filter
{
    struct ogles_filter_base base;

    struct
    {
        struct uniform uTexture;
    } uniforms;

    struct
    {
        struct attribute aPosition;
        struct attribute aTextureCoord;
    } attributes;
};

ogles_filter_init(present)
(struct ogles_present_filter *filter, primitive_type primitive_type, bool create_fbo);

ogles_filter_release(present)
(struct ogles_present_filter *filter);

ogles_filter_safe_release(present)
(struct ogles_present_filter *filter);

ogles_filter_resize(present)
(struct ogles_present_filter *filter, GLint width, GLint height);

ogles_filter_pre_draw(present)
(struct ogles_present_filter *filter);

ogles_filter_draw(present)
(struct ogles_present_filter *filter, GLuint *texture);

ogles_filter_post_draw(present)
(struct ogles_present_filter *filter, GLuint *texture);

ogles_filter_use_program(present)
(struct ogles_present_filter *filter);

ogles_filter_register_handle(present)
(struct ogles_present_filter *filter);

#endif //EXOGFX_GRAPHICS_OGLES_PRESENT_FILTER_H
