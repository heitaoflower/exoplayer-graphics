//
// Created by showtime on 9/10/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_FILTER_H
#define EXOPLAYER_GRAPHICS_OGLES_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "../utils/map.h"

struct ogles_filter
{
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint vertex_buffer;
    map_int_t handle_map;
};

void ogles_filter_init(struct ogles_filter *filter);

void ogles_filter_release(struct ogles_filter *filter);

void ogles_filter_resize(struct ogles_filter *filter, GLint width, GLint height);

void ogles_filter_draw(struct ogles_filter *filter, GLuint texture, struct ogles_fbo *fbo);

void ogles_filter_draw_cb(struct ogles_filter *filter);

void ogles_filter_use_program(struct ogles_filter *filter);

GLuint ogles_filter_get_vertex_buffer(struct ogles_filter *filter);

GLint ogles_filter_get_handle(struct ogles_filter *filter, const GLchar *name);

#endif //EXOPLAYER_GRAPHICS_OGLES_FILTER_H
