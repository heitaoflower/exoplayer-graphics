//
// Created by showtime on 9/9/2017.
//
#include "ogles_fbo.h"
#include "ogles_eye.h"
#include "ogles_preview_filter.h"
#include "ogles_effects_filter.h"
#include "ogles_present_filter.h"
#include "../../context/context.h"
#include "../../video/video_format.h"
#include "../../sensor/head_tracker.h"
#include "ogles_distortion_filter.h"

static struct ogles_eye both_ogles_eye;
static struct ogles_eye left_ogles_eye;
static struct ogles_eye right_ogles_eye;

static enum video_format video_format = VideoFormat_Unknown;

static bool vr_enabled = false;

static struct ogles_preview_filter preview_filter = {
        .base = {.type = FILTER_TYPE_PREVIEW},
        .uniforms = {UNIFORM(uMVPMatrix), UNIFORM(uSTMatrix), UNIFORM(uTexture), UNIFORM(uAspect)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aTextureCoord)}
};

static struct ogles_effects_filter effects_filter = {
        .base = {.type = FILTER_TYPE_EFFECTS}
};

static struct ogles_distortion_filter distortion_filter = {
        .base = {.type = FILTER_TYPE_DISTORTION},
        .uniforms = {UNIFORM(uTextureCoordScale), UNIFORM(uTexture)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aVignette), ATTRIBUTE(aRedTextureCoord), ATTRIBUTE(aGreenTextureCoord), ATTRIBUTE(aBlueTextureCoord)}
};

static struct ogles_present_filter present_filter = {
        .base = {.type = FILTER_TYPE_PRESENT},
        .uniforms = {UNIFORM(uTexture)},
        .attributes = {ATTRIBUTE(aPosition), ATTRIBUTE(aTextureCoord)}
};

static void create(GLuint texture)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    ogles_preview_filter_init(&preview_filter, PrimitiveTypeSphere, true, texture);
    ogles_effects_filter_init(&effects_filter);
    ogles_present_filter_init(&present_filter, PrimitiveTypeQuad, false);

    ogles_eye_init(&both_ogles_eye, EyeTypeBoth, ProjectionTypePerspective);
    ogles_eye_set_lookat_default(&both_ogles_eye);

    ogles_eye_init(&left_ogles_eye, EyeTypeLeft, ProjectionTypePerspective);
    ogles_eye_set_lookat_default(&left_ogles_eye);

    ogles_eye_init(&right_ogles_eye, EyeTypeRight, ProjectionTypePerspective);
    ogles_eye_set_lookat_default(&right_ogles_eye);
}

static void resize(GLsizei width, GLsizei height)
{
    ogles_preview_filter_resize(&preview_filter, width, height);
    ogles_effects_filter_resize(&effects_filter, width, height);
    ogles_present_filter_resize(&present_filter, width, height);

    ogles_eye_resize(&both_ogles_eye, width, height);
    ogles_eye_resize(&left_ogles_eye, width, height);
    ogles_eye_resize(&right_ogles_eye, width, height);
}

static void draw_eye(struct ogles_eye *ogles_eye, GLuint *texture, const float st_mat[])
{
    ogles_eye_update(ogles_eye);
    ogles_preview_filter_draw(&preview_filter, texture, st_mat, ogles_eye);
}

static void draw(GLuint *texture, const float st_mat[], const int32_t display_rotation)
{
    mat4 head_view;
    head_tracker_get_last_view(&head_view, display_rotation);

    if (vr_enabled)
    {
        mat4_copy(&head_view, &left_ogles_eye.camera.model_mat);
        mat4_copy(&head_view, &right_ogles_eye.camera.model_mat);
        draw_eye(&left_ogles_eye, texture, st_mat);
        draw_eye(&right_ogles_eye, texture, st_mat);
    }
    else
    {
        mat4_copy(&head_view, &both_ogles_eye.camera.model_mat);
        draw_eye(&both_ogles_eye, texture, st_mat);
    }

    ogles_eye_apply_viewport(&both_ogles_eye);
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