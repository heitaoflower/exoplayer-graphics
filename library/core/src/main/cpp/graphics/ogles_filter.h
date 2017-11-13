//
// Created by showtime on 9/11/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_FILTER_H

#define FILTER_TYPE_PREVIEW             0xF000
#define FILTER_TYPE_GRAY                0xF001
#define FILTER_TYPE_YUV                 0xF002
#define FILTER_TYPE_PRESENT        0xFFFF

#define VERTICES_DATA_POSITION_SIZE 3
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

#define ogles_filter_use_program(name) \
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
