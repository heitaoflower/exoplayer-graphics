//
// Created by showtime on 9/10/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_FBO_H
#define EXOPLAYER_GRAPHICS_OGLES_FBO_H

#include "ogles.h"

#include <stdint.h>

struct ogles_fbo
{
    uint32_t width;
    uint32_t height;
    uint32_t framebuffer_name;
    uint32_t renderbuffer_name;
    uint32_t texture_name;
};

void ogles_fbo_setup(struct ogles_fbo *fbo, uint32_t width, uint32_t height);

void ogles_fbo_release(struct ogles_fbo* fbo);

void ogles_fbo_enable(struct ogles_fbo *fbo);

#endif //EXOPLAYER_GRAPHICS_OGLES_FBO_H
