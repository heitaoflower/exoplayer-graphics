//
// Created by showtime on 9/10/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_FILTER_H
#define EXOPLAYER_GRAPHICS_OGLES_FILTER_H

#include "ogles.h"

struct ogles_filter
{
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint vertex_buffer;
};

void ogles_filter_init(struct ogles_filter *filter);

void ogles_filter_release(struct ogles_filter *filter);

#endif //EXOPLAYER_GRAPHICS_OGLES_FILTER_H
