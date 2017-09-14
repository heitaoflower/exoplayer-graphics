//
// Created by showtime on 9/9/2017.
//
#include "context.h"
#include "ogles_fbo.h"
#include "ogles_video_filter.h"
#include "ogles_presentation_filter.h"
#include "../utils/ogles_util.h"
#include "../math/mat4.h"

#pragma pack(1)

struct uniform
{
    GLint location;
    const char *name;
};

struct
{
    struct uniform model;
    struct uniform view;
    struct uniform projection;
} uniforms = {
#define UNIFORM(u) .u = {-1, #u}
        UNIFORM(model),
        UNIFORM(view),
        UNIFORM(projection),
};

static mat4 mvp_mat;
static mat4 model_mat;
static mat4 view_mat;
static mat4 projection_mat;
static mat4 st_mat;

#pragma pack()
static struct ogles_fbo fbo;

static struct ogles_video_filter video_filter;

static struct ogles_presentation_filter presentation_filter;

static void create(void)
{
    glClearColor(0.2f, 0.3f, 0.4f, 1.0f);

    ogles_presentation_filter_init(&presentation_filter);

    ogles_video_filter_init(&video_filter);

    mat4_lookat((float*)view_mat, 0.0, 0.0, 5.0, 0.0, 0.0, 0, 0.0, 1.0, 0);
}

static void resize(GLsizei width, GLsizei height)
{
    ogles_fbo_resize(&fbo, width, height);

    ogles_presentation_filter_resize(&presentation_filter, width, height);

    ogles_video_filter_resize(&video_filter, width, height);

    //mat4_frustum((float*)projection_mat,-1, 1, -1, 1, 5, 7);
    mat4_perspective((float*)projection_mat, deg2rad(60), 1, 0.3f, 1000);
    mat4_identity((float*)model_mat);
}

static void draw(GLuint texture)
{
    mat4_multiply(mvp_mat, view_mat, model_mat);
    mat4_multiply(mvp_mat, projection_mat, mvp_mat);

    float st[] = {
            1.0, 0.0, 0.0, 0.0,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
    };

    ogles_fbo_enable(&fbo);
    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(video_filter.target, texture);
    initSampler(video_filter.target, GL_LINEAR, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    ogles_video_filter_draw(&video_filter, texture, (float*)mvp_mat, st, 1.0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ogles_presentation_filter_draw(&presentation_filter, fbo.rendertexture);
}

static void destroy(void)
{
    LOGI("destroy");
}

struct exogfx_renderer ogles_renderer = {
        .name = "opengles",
        .api_type = API_OGLES,
        .create = create,
        .resize = resize,
        .draw = draw,
        .destroy = destroy
};
