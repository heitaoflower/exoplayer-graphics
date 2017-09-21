//
// Created by showtime on 9/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_PRESENTATION_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_PRESENTATION_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../geometry/primitive.h"

struct ogles_presentation_filter
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

ogles_filter_init(presentation)
(struct ogles_presentation_filter *filter, struct primitive *primitive);

ogles_filter_release(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_safe_release(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_resize(presentation)
(struct ogles_presentation_filter *filter, GLint width, GLint height);

ogles_filter_draw(presentation)
(struct ogles_presentation_filter *filter, GLuint texture);

ogles_filter_draw_cb(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_use_program(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_register_handle(presentation)
(struct ogles_presentation_filter *filter);

#endif //EXOGFX_GRAPHICS_OGLES_PRESENTATION_FILTER_H
