//
// Created by showtime on 9/10/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_PRESENTATION_FILTER_H
#define EXOPLAYER_GRAPHICS_OGLES_PRESENTATION_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../utils/map.h"

struct ogles_presentation_filter
{
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint vertex_buffer;
    map_int_t handle_map;
};

OGLES_FILTER_INIT(presentation)
(struct ogles_presentation_filter *filter);

OGLES_FILTER_RELEASE(presentation)
(struct ogles_presentation_filter *filter);

OGLES_FILTER_RESIZE(presentation)
(struct ogles_presentation_filter *filter, GLint width, GLint height);

OGLES_FILTER_DRAW(presentation)
(struct ogles_presentation_filter *filter, GLuint texture);

OGLES_FILTER_DRAW_CB(presentation)
(struct ogles_presentation_filter *filter);

OGLES_FILTER_USE_PROGRAM(presentation)
(struct ogles_presentation_filter *filter);

OGLES_FILTER_GET_VERTEX_BUFFER(presentation)
(struct ogles_presentation_filter *filter);

OGLES_FILTER_GET_HANDLE(presentation)
(struct ogles_presentation_filter *filter, const GLchar *name);

#endif //EXOPLAYER_GRAPHICS_OGLES_PRESENTATION_FILTER_H
