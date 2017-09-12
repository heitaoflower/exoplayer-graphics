//
// Created by showtime on 9/10/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_VIDEO_FILTER_H
#define EXOPLAYER_GRAPHICS_OGLES_VIDEO_FILTER_H

#include "ogles.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../utils/map.h"

struct ogles_video_filter
{
    GLuint program;
    GLuint vertex_shader;
    GLuint fragment_shader;
    GLuint vertex_buffer;
    GLuint target;
    map_int_t handle_map;
};
OGLES_FILTER_INIT(video)
(struct ogles_video_filter *filter);

OGLES_FILTER_RELEASE(video)
(struct ogles_video_filter *filter);

OGLES_FILTER_RESIZE(video)
(struct ogles_video_filter *filter, GLint width, GLint height);

OGLES_FILTER_DRAW(video)
(struct ogles_video_filter *filter, GLuint texture, const float mvp_matrix[], const float st_matrix[], const float aspect_ratio);

OGLES_FILTER_DRAW_CB(video)
(struct ogles_video_filter *filter);

OGLES_FILTER_USE_PROGRAM(video)
(struct ogles_video_filter *filter);

OGLES_FILTER_GET_VERTEX_BUFFER(video)
(struct ogles_video_filter *filter);

OGLES_FILTER_GET_HANDLE(video)
(struct ogles_video_filter *filter, const GLchar *name);

#endif //EXOPLAYER_GRAPHICS_OGLES_VIDEO_FILTER_H
