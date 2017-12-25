//
// Created by showtime on 9/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_DISTORTION_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_DISTORTION_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../../math/mat4.h"
#include "ogles_eye.h"

struct ogles_distortion_filter
{
    struct ogles_filter_base base;

    GLuint target;

    struct
    {
        struct uniform uMVPMatrix;
        struct uniform uSTMatrix;
        struct uniform sTexture;
        struct uniform uAspect;
    } uniforms;

    struct
    {
        struct attribute aPosition;
        struct attribute aTextureCoord;
    } attributes;
};

ogles_filter_init(distortion)
(struct ogles_distortion_filter *filter, primitive_type primitive_type, bool create_fbo, GLuint texture);

ogles_filter_release(distortion)
(struct ogles_distortion_filter *filter);

ogles_filter_safe_release(distortion)
(struct ogles_distortion_filter *filter);

ogles_filter_resize(distortion)
(struct ogles_distortion_filter *filter, GLint width, GLint height);

ogles_filter_pre_draw(distortion)
(struct ogles_distortion_filter *filter, struct ogles_eye *ogles_eye);

ogles_filter_draw(distortion)
(struct ogles_distortion_filter *filter, GLuint *texture, const float st_mat[], struct ogles_eye *ogles_eye);

ogles_filter_post_draw(distortion)
(struct ogles_distortion_filter *filter, GLuint *texture, struct ogles_eye *ogles_eye);

ogles_filter_use_program(distortion)
(struct ogles_distortion_filter *filter);

ogles_filter_register_handle(distortion)
(struct ogles_distortion_filter *filter);

#endif //EXOGFX_GRAPHICS_OGLES_DISTORTION_FILTER_H
