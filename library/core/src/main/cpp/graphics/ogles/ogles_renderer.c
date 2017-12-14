//
// Created by showtime on 9/9/2017.
//
#include "ogles_fbo.h"
#include "ogles_eye.h"
#include "ogles_preview_filter.h"
#include "ogles_effects_filter.h"
#include "ogles_present_filter.h"
#include "../../utils/ogles_util.h"
#include "../../math/camera.h"
#include "../../context/context.h"
#include "../../video/video_format.h"
#include "../../sensor/head_tracker.h"

static struct ogles_eye both_ogles_eye;
static struct ogles_eye left_ogles_eye;
static struct ogles_eye right_ogles_eye;

static enum video_format video_format = VideoFormat_Unknown;

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

    ogles_preview_filter_init(&preview_filter, PrimitiveTypeSphere, true, texture);
    ogles_effects_filter_init(&effects_filter);
    ogles_present_filter_init(&present_filter, PrimitiveTypeQuad, false);

    ogles_eye_init(&both_ogles_eye, EyeTypeLeft, ProjectionTypePerspective);
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

static void draw_left(GLuint *texture, mat4 *mvp, const float st_mat[])
{
    glViewport(left_ogles_eye.camera.viewport_x, left_ogles_eye.camera.viewport_y, left_ogles_eye.camera.viewport_width, left_ogles_eye.camera.viewport_height);
    ogles_preview_filter_draw(&preview_filter, texture, mvp, st_mat, ogles_eye_get_aspect(&left_ogles_eye));
    ogles_effects_filter_draw(&effects_filter, texture);
}

static void draw_right(GLuint *texture, mat4 *mvp, const float st_mat[])
{
    glViewport(right_ogles_eye.camera.viewport_x, right_ogles_eye.camera.viewport_y, right_ogles_eye.camera.viewport_width, right_ogles_eye.camera.viewport_height);
    ogles_preview_filter_draw(&preview_filter, texture, mvp, st_mat, ogles_eye_get_aspect(&left_ogles_eye));
    ogles_effects_filter_draw(&effects_filter, texture);
}

static void draw_both(GLuint *texture, mat4 *mvp, const float st_mat[])
{
    glViewport(0, 0, both_ogles_eye.camera.viewport_width, both_ogles_eye.camera.viewport_height);

    ogles_preview_filter_draw(&preview_filter, texture, mvp, st_mat, ogles_eye_get_aspect(&both_ogles_eye));
    ogles_effects_filter_draw(&effects_filter, texture);
    ogles_present_filter_draw(&present_filter, texture);
}

static void draw(GLuint *texture, const float st_mat[], const int32_t display_rotation)
{
    mat4 head_view;
    head_tracker_get_last_view(&head_view, display_rotation);

    mat4_copy(&head_view, &both_ogles_eye.camera.model_mat);
    mat4_copy(&head_view, &left_ogles_eye.camera.model_mat);
    mat4_copy(&head_view, &right_ogles_eye.camera.model_mat);

    ogles_eye_update(&both_ogles_eye);
    ogles_eye_update(&left_ogles_eye);
    ogles_eye_update(&right_ogles_eye);

    draw_left(texture, &left_ogles_eye.camera.mvp_mat, st_mat);
    draw_right(texture, &right_ogles_eye.camera.mvp_mat, st_mat);
    //draw_both(texture, &both_ogles_eye.camera.mvp_mat, st_mat);
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