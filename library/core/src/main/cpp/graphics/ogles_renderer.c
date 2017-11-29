//
// Created by showtime on 9/9/2017.
//
#include "ogles_fbo.h"
#include "ogles_preview_filter.h"
#include "ogles_effects_filter.h"
#include "ogles_present_filter.h"
#include "../utils/ogles_util.h"
#include "../math/camera.h"
#include "../context/context.h"
#include "../sensor/head_tracker.h"

#pragma pack(1)

static struct camera camera;

static struct ogles_preview_filter preview_filter = {
        .base = {.type = FILTER_TYPE_PREVIEW},
        .uniforms = {UNIFORM(uMVPMatrix), UNIFORM(uSTMatrix), UNIFORM(sTexture), UNIFORM(uAspect)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aTextureCoord)}
};

static struct ogles_effects_filter effects_filter = {
        .base = {.type = FILTER_TYPE_EFFECTS}
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

    ogles_preview_filter_init(&preview_filter, PrimitiveTypeQuad, true);
    ogles_effects_filter_init(&effects_filter);
    ogles_present_filter_init(&present_filter, PrimitiveTypeQuad, false);

    glBindTexture(preview_filter.target, texture);
    initSampler(preview_filter.target, GL_LINEAR, GL_NEAREST);
    camera_set_lookat(&camera);
}

static void resize(GLsizei width, GLsizei height)
{
    ogles_preview_filter_resize(&preview_filter, width, height);
    ogles_effects_filter_resize(&effects_filter, width, height);
    ogles_present_filter_resize(&present_filter, width, height);

    camera_set_projection(&camera, ProjectionTypeOrtho, width, height);
    glViewport(0, 0, width, height);
}

static void draw(GLuint *texture, const float st_mat[])
{
    camera_update(&camera);
    ogles_preview_filter_draw(&preview_filter, texture, &camera.mvp_mat, st_mat, camera.aspect);
    ogles_effects_filter_draw(&effects_filter, texture);
    ogles_present_filter_draw(&present_filter, texture);
}

static void destroy(void)
{
    ogles_preview_filter_release(&preview_filter);
    ogles_effects_filter_release(&effects_filter);
    ogles_present_filter_release(&present_filter);
}

struct exogfx_renderer ogles_renderer = {
        .name = "OGLES",
        .api_type = API_OGLES20,
        .create = create,
        .resize = resize,
        .draw = draw,
        .destroy = destroy
};
