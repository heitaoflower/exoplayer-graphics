//
// Created by showtime on 9/9/2017.
//
#include "../context/context.h"
#include "ogles_fbo.h"
#include "ogles_video_filter.h"
#include "ogles_presentation_filter.h"
#include "../utils/ogles_util.h"
#include "../math/camera.h"

#pragma pack(1)

struct camera camera;
static struct ogles_fbo fbo;
static struct ogles_video_filter video_filter = {
        .uniforms = {UNIFORM(uMVPMatrix), UNIFORM(uSTMatrix), UNIFORM(sTexture), UNIFORM(uAspect)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aTextureCoord)}
};
static struct ogles_presentation_filter presentation_filter = {
        .uniforms = {UNIFORM(sTexture)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aTextureCoord)}
};

#pragma pack()

static void create(GLuint texture)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    ogles_video_filter_init(&video_filter, create_primitive(PrimitiveTypeQuad));
    ogles_presentation_filter_init(&presentation_filter, create_primitive(PrimitiveTypeQuad));

    glBindTexture(video_filter.target, texture);
    initSampler(video_filter.target, GL_LINEAR, GL_NEAREST);

    camera_set_lookat(&camera);
}

static void resize(GLsizei width, GLsizei height)
{
    ogles_fbo_resize(&fbo, width, height);

    ogles_presentation_filter_resize(&presentation_filter, width, height);

    ogles_video_filter_resize(&video_filter, width, height);

    camera_set_projection(&camera, ProjectionTypeOrtho, width, height);
}

static void draw(GLuint texture, const float st_mat[])
{
    camera_update(&camera);
    ogles_fbo_enable(&fbo);

    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_COLOR_BUFFER_BIT);
    ogles_video_filter_draw(&video_filter, texture, &camera.mvp_mat, st_mat, camera.aspect);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_COLOR_BUFFER_BIT);
    ogles_presentation_filter_draw(&presentation_filter, fbo.rendertexture);
}

static void destroy(void)
{
    ogles_fbo_safe_release(&fbo);
    ogles_video_filter_safe_release(&video_filter);
    ogles_presentation_filter_safe_release(&presentation_filter);
}

struct exogfx_renderer ogles_renderer = {
        .name = "opengles",
        .api_type = API_OGLES,
        .create = create,
        .resize = resize,
        .draw = draw,
        .destroy = destroy
};