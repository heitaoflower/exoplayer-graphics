//
// Created by showtime on 9/9/2017.
//
#include "ogles_fbo.h"
#include "ogles_preview_filter.h"
#include "ogles_effects_filter.h"
#include "ogles_present_filter.h"
#include "../../vr/ogles/vr_ogles_engine.h"
#include "../../utils/ogles_util.h"
#include "../../math/camera.h"
#include "../../context/context.h"
#include "../../sensor/head_tracker.h"

static struct camera camera;

static struct vr_ogles_engine vr_ogles_engine;

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

static void create(GLuint texture)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    vr_ogles_engine_init(&vr_ogles_engine);

    ogles_preview_filter_init(&preview_filter, PrimitiveTypeSphere, true, texture);
    ogles_effects_filter_init(&effects_filter);
    ogles_present_filter_init(&present_filter, PrimitiveTypeQuad, false);

    camera_init(&camera);
}

static void resize(GLsizei width, GLsizei height)
{
    ogles_preview_filter_resize(&preview_filter, width, height);
    ogles_effects_filter_resize(&effects_filter, width, height);
    ogles_present_filter_resize(&present_filter, width, height);

    camera_set_projection(&camera, ProjectionTypePerspective, width, height);
}

static void draw(GLuint *texture, const float st_mat[], const int32_t display_rotation)
{
    mat4 native_head_view;
    head_tracker_get_last_view(&native_head_view, display_rotation);

    vr_ogles_engine_draw(&vr_ogles_engine);

    if (vr_ogles_engine.project_changed)
    {
        vr_ogles_engine.project_changed = false;
    }

    camera_set_lookat(&camera);
    mat4_copy(&native_head_view, &camera.model_mat);
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
        .create   = create,
        .resize   = resize,
        .draw     = draw,
        .destroy  = destroy
};