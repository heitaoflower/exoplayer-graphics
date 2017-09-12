//
// Created by showtime on 9/11/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_FILTER_H
#define EXOPLAYER_GRAPHICS_OGLES_FILTER_H

#define FLOAT_SIZE_BYTES 4
#define VERTICES_DATA_POSITION_SIZE 3
#define VERTICES_DATA_UV_SIZE 2
#define VERTICES_DATA_STRIDE_BYTES (VERTICES_DATA_POSITION_SIZE + VERTICES_DATA_UV_SIZE) * FLOAT_SIZE_BYTES
#define VERTICES_DATA_POSITION_OFFSET 0 * FLOAT_SIZE_BYTES
#define VERTICES_DATA_UV_OFFSET VERTICES_DATA_POSITION_OFFSET + VERTICES_DATA_POSITION_SIZE * FLOAT_SIZE_BYTES

#define OGLES_FILTER_INIT(name)    \
        void ogles_##name##_filter_init

#define OGLES_FILTER_RELEASE(name) \
        void ogles_##name##_filter_release

#define OGLES_FILTER_RESIZE(name)  \
        void ogles_##name##_filter_resize

#define OGLES_FILTER_DRAW(name)    \
        void ogles_##name##_filter_draw

#define OGLES_FILTER_DRAW_CB(name) \
        void ogles_##name##_filter_draw_cb

#define OGLES_FILTER_USE_PROGRAM(name) \
        void ogles_##name##_filter_use_program

#define OGLES_FILTER_GET_VERTEX_BUFFER(name)    \
        GLuint ogles_##name##_filter_get_vertex_buffer

#define OGLES_FILTER_GET_HANDLE(name)  \
        GLint ogles_##name##_filter_get_handle

static const GLfloat VERTICES_DATA[] =
        {
                -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
                1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  -1.0f, 0.0f, 1.0f, 0.0f };

#endif //EXOPLAYER_GRAPHICS_OGLES_FILTER_H
