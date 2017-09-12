//
// Created by showtime on 9/10/2017.
//
#include "ogles_fbo.h"
#include "../utils/log_util.h"
#include "../utils/ogles_util.h"

void ogles_fbo_resize(struct ogles_fbo *fbo, GLsizei width, GLsizei height)
{
    GLint params[1];
    glGetIntegerv(GL_MAX_TEXTURE_SIZE, params);

    if (width > params[0] || height > params[0])
    {
        LOGE("GL_MAX_TEXTURE_SIZE: %d", params[0]);
    }

    glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, params);
    if (width > params[0] || height > params[0])
    {
        LOGE("GL_MAX_RENDERBUFFER_SIZE: %d", params[0]);
    }

    glGetIntegerv(GL_FRAMEBUFFER_BINDING, params);
    GLuint current_framebuffer = (GLuint)params[0];
    glGetIntegerv(GL_RENDERBUFFER_BINDING, params);
    GLuint current_renderbuffer = (GLuint)params[0];
    glGetIntegerv(GL_TEXTURE_BINDING_2D, params);
    GLuint current_rendertexture = (GLuint)params[0];

    ogles_fbo_release(fbo);

    fbo->width = width;
    fbo->height = height;

    glGenFramebuffers(1, &fbo->framebuffer_name);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->framebuffer_name);

    glGenRenderbuffers(1, &fbo->renderbuffer_name);
    glBindRenderbuffer(GL_RENDERBUFFER, fbo->renderbuffer_name);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, fbo->width, fbo->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo->renderbuffer_name);

    glGenTextures(1, &fbo->texture_name);
    glBindTexture(GL_TEXTURE_2D, fbo->texture_name);

    initSampler(GL_TEXTURE_2D, GL_LINEAR, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbo->width, fbo->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->texture_name, 0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    if (status != GL_FRAMEBUFFER_COMPLETE)
    {
        LOGE("failed to initialize framebuffer object %d", status);

        ogles_fbo_release(fbo);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, current_framebuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, current_renderbuffer);
    glBindTexture(GL_TEXTURE_2D, current_rendertexture);
}

void ogles_fbo_release(struct ogles_fbo* fbo)
{
    glDeleteTextures(1, &fbo->texture_name);
    fbo->texture_name = 0;

    glDeleteRenderbuffers(1, &fbo->renderbuffer_name);
    fbo->renderbuffer_name = 0;

    glDeleteFramebuffers(1, &fbo->framebuffer_name);
    fbo->framebuffer_name = 0;
}

void ogles_fbo_enable(struct ogles_fbo* fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->framebuffer_name);
}
