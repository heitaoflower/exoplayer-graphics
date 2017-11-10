//
// Created by showtime on 11/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_GRAY_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_GRAY_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../geometry/primitive.h"

struct ogles_gray_filter
{
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;

    struct primitive *primitive;

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

ogles_filter_init(gray)
(struct ogles_gray_filter *filter, struct primitive *primitive);

ogles_filter_release(gray)
(struct ogles_gray_filter *filter);

ogles_filter_safe_release(gray)
(struct ogles_gray_filter *filter);

ogles_filter_resize(gray)
(struct ogles_gray_filter *filter, GLint width, GLint height);

ogles_filter_pre_draw(gray)
(struct ogles_gray_filter *filter);

ogles_filter_draw(gray)
(struct ogles_gray_filter *filter, GLuint texture);

ogles_filter_post_draw(gray)
(struct ogles_gray_filter *filter);

ogles_filter_use_program(gray)
(struct ogles_gray_filter *filter);

ogles_filter_register_handle(gray)
(struct ogles_gray_filter *filter);

#endif // EXOGFX_GRAPHICS_OGLES_GRAY_FILTER_H