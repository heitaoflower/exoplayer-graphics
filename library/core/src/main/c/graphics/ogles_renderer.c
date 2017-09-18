//
// Created by showtime on 9/9/2017.
//
#include "context.h"
#include "ogles_fbo.h"
#include "ogles_video_filter.h"
#include "ogles_presentation_filter.h"
#include "../utils/ogles_util.h"
#include "../math/mat4.h"
#include "../geometry/primitive.h"

#pragma pack(1)

static mat4 mvp_mat;
static mat4 model_mat;
static mat4 view_mat;
static mat4 projection_mat;

static struct ogles_fbo fbo;
static struct ogles_video_filter video_filter = {
        .uniforms = {UNIFORM(uMVPMatrix), UNIFORM(uSTMatrix), UNIFORM(uCRatio), UNIFORM(sTexture)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aTextureCoord)}
};
static struct ogles_presentation_filter presentation_filter = {
        .uniforms = {UNIFORM(sTexture)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aTextureCoord)}
};

#pragma pack()

static void create(GLuint texture)
{
    create_primitive(Sphere);

    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    ogles_presentation_filter_init(&presentation_filter);
    ogles_video_filter_init(&video_filter);

    glBindTexture(video_filter.target, texture);
    initSampler(video_filter.target, GL_LINEAR, GL_NEAREST);

    mat4_lookat(&view_mat, 0.0f, 0.0f, 0.3f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);
}

static void resize(GLsizei width, GLsizei height)
{
    ogles_fbo_resize(&fbo, width, height);

    ogles_presentation_filter_resize(&presentation_filter, width, height);

    ogles_video_filter_resize(&video_filter, width, height);

    mat4_perspective_default(&projection_mat);

    mat4_identity(&model_mat);
}

static void draw(GLuint texture, const float st_mat[])
{
    mat4_multiply(&mvp_mat, &view_mat, &model_mat);
    mat4_multiply(&mvp_mat, &projection_mat, &mvp_mat);

    ogles_fbo_enable(&fbo);
    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_COLOR_BUFFER_BIT);

    ogles_video_filter_draw(&video_filter, texture, (float *)mvp_mat, st_mat, 1.7);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
