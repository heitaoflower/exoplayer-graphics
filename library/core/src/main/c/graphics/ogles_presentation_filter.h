//
// Created by showtime on 9/10/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_PRESENTATION_FILTER_H
#define EXOGFX_GRAPHICS_OGLES_PRESENTATION_FILTER_H

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

ogles_filter_init(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_release(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_resize(presentation)
(struct ogles_presentation_filter *filter, GLint width, GLint height);

ogles_filter_draw(presentation)
(struct ogles_presentation_filter *filter, GLuint texture);

ogles_filter_draw_cb(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_use_program(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_get_vertex_buffer(presentation)
(struct ogles_presentation_filter *filter);

ogles_filter_get_handle(presentation)
(struct ogles_presentation_filter *filter, const GLchar *name);

#endif //EXOGFX_GRAPHICS_OGLES_PRESENTATION_FILTER_H
