//
// Created by showtime on 9/10/2017.
//
#include "ogles_video_filter.h"

OGLES_FILTER_INIT(video)
(struct ogles_video_filter *filter)
{

}

OGLES_FILTER_RELEASE(video)
(struct ogles_video_filter *filter)
{

}

OGLES_FILTER_RESIZE(video)
(struct ogles_video_filter *filter, GLint width, GLint height)
{

}

OGLES_FILTER_DRAW(video)
(struct ogles_video_filter *filter, GLuint texture, struct ogles_fbo *fbo)
{

}

OGLES_FILTER_DRAW_CB(video)
(struct ogles_video_filter *filter)
{

}

OGLES_FILTER_USE_PROGRAM(video)
(struct ogles_video_filter *filter)
{

}

OGLES_FILTER_GET_VERTEX_BUFFER(video)
(struct ogles_video_filter *filter)
{
    return 0;
}

OGLES_FILTER_GET_HANDLE(video)
(struct ogles_video_filter *filter, const GLchar *name)
{
    return 0;
}
