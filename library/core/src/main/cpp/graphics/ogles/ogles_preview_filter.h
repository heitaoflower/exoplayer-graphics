//
// Created by showtime on 9/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_PREVIEW_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_PREVIEW_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../../math/mat4.h"
#include "ogles_eye.h"

struct ogles_preview_filter
{
    struct ogles_filter_base base;

    GLuint target;

    struct
    {
        struct uniform uMVPMatrix;
        struct uniform uSTMatrix;
        struct uniform uTexture;
        struct uniform uAspect;
    } uniforms;

    struct
    {
        struct attribute aPosition;
        struct attribute aTextureCoord;
    } attributes;
};

ogles_filter_init(preview)
(struct ogles_preview_filter *filter, primitive_type primitive_type, bool create_fbo, GLuint texture);

ogles_filter_release(preview)
(struct ogles_preview_filter *filter);

ogles_filter_safe_release(preview)
(struct ogles_preview_filter *filter);

ogles_filter_resize(preview)
(struct ogles_preview_filter *filter, GLint width, GLint height);

ogles_filter_pre_draw(preview)
(struct ogles_preview_filter *filter, struct ogles_eye *ogles_eye);

ogles_filter_draw(preview)
(struct ogles_preview_filter *filter, GLuint *texture, const float st_mat[], struct ogles_eye *ogles_eye);

ogles_filter_post_draw(preview)
(struct ogles_preview_filter *filter, GLuint *texture, struct ogles_eye *ogles_eye);

ogles_filter_use_program(preview)
(struct ogles_preview_filter *filter);

ogles_filter_register_handle(preview)
(struct ogles_preview_filter *filter);

#endif //EXOGFX_GRAPHICS_OGLES_PREVIEW_FILTER_H
