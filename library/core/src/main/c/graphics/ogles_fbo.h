//
// Created by showtime on 9/10/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_FBO_H
#define EXOPLAYER_GRAPHICS_OGLES_FBO_H

#include "ogles.h"

#include <stdint.h>

struct ogles_fbo
{
    GLint width;
    GLint height;
    GLuint framebuffer_name;
    GLuint renderbuffer_name;
    GLuint texture_name;
};

void ogles_fbo_init(struct ogles_fbo *fbo, GLint width, GLint height);

void ogles_fbo_release(struct ogles_fbo* fbo);

void ogles_fbo_enable(struct ogles_fbo *fbo);

#endif //EXOPLAYER_GRAPHICS_OGLES_FBO_H
