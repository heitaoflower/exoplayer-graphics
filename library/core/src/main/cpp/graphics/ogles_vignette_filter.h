//
// Created by showtime on 11/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_VIGNETTE_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_VIGNETTE_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../geometry/primitive.h"

struct ogles_vignette_filter
{
    struct ogles_filter_base base;

    struct
    {
        struct uniform sTexture;
        struct uniform uVignetteCenter;
        struct uniform uVignetteColor;
        struct uniform uVignetteStart;
        struct uniform uVignetteEnd;
    } uniforms;

    struct
    {
        struct attribute aPosition;
        struct attribute aTextureCoord;
    } attributes;

    float vignette_center_x;
    float vignette_center_y;
    float vignette_color[3];
    float vignette_start;
    float vignette_end;
};

ogles_filter_create(vignette)
(void);

ogles_filter_init(vignette)
(struct ogles_filter_base *filter, struct primitive *primitive);

ogles_filter_release(vignette)
(struct ogles_filter_base *filter);

ogles_filter_safe_release(vignette)
(struct ogles_filter_base *filter);

ogles_filter_resize(vignette)
(struct ogles_filter_base *filter, GLint width, GLint height);

ogles_filter_draw(vignette)
(struct ogles_filter_base *filter, GLuint texture);

ogles_filter_pre_draw(vignette)
(struct ogles_vignette_filter *filter);

ogles_filter_post_draw(vignette)
(struct ogles_vignette_filter *filter);

ogles_filter_use_program(vignette)
(struct ogles_vignette_filter *filter);

ogles_filter_register_handle(vignette)
(struct ogles_vignette_filter *filter);

#endif // EXOGFX_GRAPHICS_OGLES_VIGNETTE_FILTER_H
