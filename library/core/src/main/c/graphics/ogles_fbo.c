//
// Created by showtime on 9/10/2017.
//
#include "ogles_fbo.h"
#include "../utils/log_util.h"
#include "../utils/ogles_util.h"

void ogles_fbo_setup(struct ogles_fbo *fbo, uint32_t width, uint32_t height)
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

    GLuint framebuffers[1];
    glGenFramebuffers(1, params);
    fbo->framebuffer_name = framebuffers[0];
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->framebuffer_name);

    GLuint renderbuffers[1];
    glGenRenderbuffers(1, renderbuffers);
    fbo->renderbuffer_name = renderbuffers[0];
    glBindRenderbuffer(GL_RENDERBUFFER, fbo->renderbuffer_name);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, fbo->width, fbo->height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo->renderbuffer_name);

    GLuint textures[1];
    glGenTextures(1, textures);
    fbo->texture_name = textures[0];
    glBindTexture(GL_TEXTURE_2D, fbo->texture_name);

    setupSampler(GL_TEXTURE_2D, GL_LINEAR, GL_NEAREST);
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
    GLuint params[1];
    params[0] = fbo->texture_name;
    glDeleteTextures(1, params);
    fbo->texture_name = 0;

    params[0] = fbo->renderbuffer_name;
    glDeleteRenderbuffers(1, params);
    fbo->renderbuffer_name = 0;

    params[0] = fbo->framebuffer_name;
    glDeleteFramebuffers(1, params);
    fbo->framebuffer_name = 0;
}

void ogles_fbo_enable(struct ogles_fbo* fbo)
{
    glBindFramebuffer(GL_FRAMEBUFFER, fbo->framebuffer_name);
}
