//
// Created by showtime on 9/9/2017.
//
#include "ogles_fbo.h"
#include "ogles_preview_filter.h"
#include "ogles_filter_group.h"
#include "ogles_present_filter.h"
#include "../utils/ogles_util.h"
#include "../math/camera.h"
#include "../context/context.h"

#pragma pack(1)

static struct camera camera;
static struct ogles_fbo fbo;
static struct ogles_filter_group filter_group;

static struct ogles_preview_filter preview_filter = {
        .base = {.type = FILTER_TYPE_PREVIEW},
        .uniforms = {UNIFORM(uMVPMatrix), UNIFORM(uSTMatrix), UNIFORM(sTexture), UNIFORM(uAspect)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aTextureCoord)}
};

static struct ogles_present_filter present_filter = {
        .base = {.type = FILTER_TYPE_PRESENT},
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

    ogles_preview_filter_init(&preview_filter, create_primitive(PrimitiveTypeQuad));
    ogles_present_filter_init(&present_filter, create_primitive(PrimitiveTypeQuad));
    ogles_filter_group_init(&filter_group);

    ogles_filter_group_add(&filter_group, FILTER_TYPE_GRAY);
    ogles_filter_group_remove(&filter_group, FILTER_TYPE_GRAY);

    glBindTexture(preview_filter.target, texture);
    initSampler(preview_filter.target, GL_LINEAR, GL_NEAREST);
    camera_set_lookat(&camera);
}

static void resize(GLsizei width, GLsizei height)
{
    ogles_fbo_resize(&fbo, width, height);

    ogles_preview_filter_resize(&preview_filter, width, height);
    ogles_present_filter_resize(&present_filter, width, height);
    ogles_filter_group_resize(&filter_group, width, height);

    camera_set_projection(&camera, ProjectionTypeOrtho, width, height);
}

static void draw(GLuint texture, const float st_mat[])
{
    camera_update(&camera);
    ogles_fbo_enable(&fbo);

    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_COLOR_BUFFER_BIT);
    ogles_preview_filter_draw(&preview_filter, texture, &camera.mvp_mat, st_mat, camera.aspect);
    ogles_filter_group_draw(&filter_group, fbo.rendertexture);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glViewport(0, 0, fbo.width, fbo.height);
    glClear(GL_COLOR_BUFFER_BIT);
    ogles_present_filter_draw(&present_filter, fbo.rendertexture);
}

static void destroy(void)
{
    ogles_fbo_safe_release(&fbo);
    ogles_preview_filter_safe_release(&preview_filter);
    ogles_present_filter_safe_release(&present_filter);
    ogles_filter_group_safe_release(&filter_group);
}

struct exogfx_renderer ogles_renderer = {
        .name = "opengles",
        .api_type = API_OGLES20,
        .create = create,
        .resize = resize,
        .draw = draw,
        .destroy = destroy
};
