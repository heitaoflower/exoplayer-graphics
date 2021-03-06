//
// Created by showtime on 9/11/2017.
//
#include "../../geometry/primitive_type.h"

#include <stdbool.h>

#ifndef EXOGFX_GRAPHICS_OGLES_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_FILTER_H

#define FILTER_TYPE_PREVIEW             0xF000
#define FILTER_TYPE_GRAY                0xF001
#define FILTER_TYPE_INVERT              0xF002
#define FILTER_TYPE_VIGNETTE            0xF003
#define FILTER_TYPE_DISTORTION          0xFFFD
#define FILTER_TYPE_EFFECTS             0xFFFE
#define FILTER_TYPE_PRESENT             0xFFFF

#define VERTICES_DATA_POSITION_SIZE_1 1
#define VERTICES_DATA_POSITION_SIZE_2 2
#define VERTICES_DATA_POSITION_SIZE_3 3
#define VERTICES_DATA_UV_SIZE 2

#define ogles_filter_create(name) \
        struct ogles_##name##_filter* ogles_##name##_filter_create

#define ogles_filter_init(name)    \
        void ogles_##name##_filter_init

#define ogles_filter_release(name) \
        void ogles_##name##_filter_release

#define ogles_filter_safe_release(name) \
        void ogles_##name##_filter_safe_release

#define ogles_filter_resize(name)  \
        void ogles_##name##_filter_resize

#define ogles_filter_pre_draw(name)       \
        void ogles_##name##_filter_pre_draw

#define ogles_filter_draw(name)    \
        void ogles_##name##_filter_draw

#define ogles_filter_post_draw(name) \
        void ogles_##name##_filter_post_draw

#define ogles_filter_use_program(name)  \
        void ogles_##name##_filter_use_program

#define ogles_filter_register_handle(name)      \
        void ogles_##name##_filter_register_handle

#define UNIFORM(u) .u = {-1, #u}

#define ATTRIBUTE(a) .a = {-1, #a}

struct ogles_filter_base
{
    uint32_t type;

    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;

    struct primitive *primitive;
    struct ogles_fbo *fbo;

    void (*init)(struct ogles_filter_base *base, primitive_type primitive_type, bool auto_fbo);
    void (*resize)(struct ogles_filter_base *base, GLint width, GLint height);
    void (*draw)(struct ogles_filter_base *base, GLuint *texture);
    void (*release)(struct ogles_filter_base *base);
    void (*safe_release)(struct ogles_filter_base *base);
};

struct uniform
{
    GLint location;
    const char *name;
};

struct attribute
{
    GLint location;
    const char *name;
};

#endif //EXOGFX_GRAPHICS_OGLES_FILTER_H
