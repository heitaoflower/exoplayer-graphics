//
// Created by showtime on 9/11/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_FILTER_H

#define FLOAT_SIZE_BYTES 4
#define VERTICES_DATA_POSITION_SIZE 3
#define VERTICES_DATA_UV_SIZE 2
#define VERTICES_DATA_STRIDE_BYTES (VERTICES_DATA_POSITION_SIZE + VERTICES_DATA_UV_SIZE) * FLOAT_SIZE_BYTES
#define VERTICES_DATA_POSITION_OFFSET 0 * FLOAT_SIZE_BYTES
#define VERTICES_DATA_UV_OFFSET VERTICES_DATA_POSITION_OFFSET + VERTICES_DATA_POSITION_SIZE * FLOAT_SIZE_BYTES

#define ogles_filter_init(name)    \
        void ogles_##name##_filter_init

#define ogles_filter_release(name) \
        void ogles_##name##_filter_release

#define ogles_filter_resize(name)  \
        void ogles_##name##_filter_resize

#define ogles_filter_draw(name)    \
        void ogles_##name##_filter_draw

#define ogles_filter_draw_cb(name) \
        void ogles_##name##_filter_draw_cb

#define ogles_filter_use_program(name) \
        void ogles_##name##_filter_use_program

#define ogles_filter_get_vertex_buffer(name)    \
        GLuint ogles_##name##_filter_get_vertex_buffer

#define ogles_filter_get_handle(name)  \
        GLint ogles_##name##_filter_get_handle

static const GLfloat VERTICES_DATA[] =
        {
                -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  -1.0f, 0.0f, 1.0f, 0.0f };

#endif //EXOGFX_GRAPHICS_OGLES_FILTER_H
