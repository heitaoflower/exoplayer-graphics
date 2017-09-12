//
// Created by showtime on 9/10/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_FBO_H
#define EXOPLAYER_GRAPHICS_OGLES_FBO_H

#include "ogles.h"

#include <stdint.h>

struct ogles_fbo
{
    GLsizei width;
    GLsizei height;
    GLuint framebuffer;
    GLuint renderbuffer;
    GLuint rendertexture;
};

void ogles_fbo_resize(struct ogles_fbo *fbo, GLsizei width, GLsizei height);

void ogles_fbo_release(struct ogles_fbo* fbo);

void ogles_fbo_enable(struct ogles_fbo *fbo);

#endif //EXOPLAYER_GRAPHICS_OGLES_FBO_H
