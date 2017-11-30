//
// Created by showtime on 9/9/2017.
//
#include "ogles_fbo.h"
#include "ogles_preview_filter.h"
#include "ogles_effects_filter.h"
#include "ogles_present_filter.h"
#include "../../utils/ogles_util.h"
#include "../../math/camera.h"
#include "../../context/context.h"
#include "../../sensor/head_tracker.h"
#include "ogles_renderer.h"

static void ogles_renderer_set_global_state(void)
{
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_SCISSOR_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

struct ogles_renderer* ogles_renderer_create()
{
    struct ogles_renderer *render = malloc(sizeof(struct ogles_renderer));
    render->name = "OGLES";
    render->camera = camera_create();
    render->ogles_preview_filter = ogles_preview_filter_create();
    render->ogles_effects_filter = ogles_effects_filter_create();
    render->ogles_present_filter = ogles_present_filter_create();

    return render;
}

void ogles_renderer_init(struct ogles_renderer *ogles_renderer, GLuint texture)
{
    ogles_renderer_set_global_state();

    camera_set_lookat(ogles_renderer->camera);
    ogles_preview_filter_init(&ogles_renderer->ogles_preview_filter->base, PrimitiveTypeQuad, true, texture);
    ogles_effects_filter_init(ogles_renderer->ogles_effects_filter);
    ogles_present_filter_init(&ogles_renderer->ogles_present_filter->base, PrimitiveTypeQuad, false);
}

void ogles_renderer_resize(struct ogles_renderer *ogles_renderer, GLsizei width, GLsizei height)
{
    ogles_preview_filter_resize(&ogles_renderer->ogles_preview_filter->base, width, height);
    ogles_effects_filter_resize(ogles_renderer->ogles_effects_filter, width, height);
    ogles_present_filter_resize(&ogles_renderer->ogles_present_filter->base, width, height);
    camera_set_projection(ogles_renderer->camera, ProjectionTypeOrtho, width, height);
    glViewport(0, 0, width, height);
}

void ogles_renderer_draw(struct ogles_renderer *ogles_renderer, GLuint *texture, const float st_mat[])
{
    mat4 head_view;
    head_tracker_get_last_view(&head_view);

    camera_update(ogles_renderer->camera);
    ogles_preview_filter_draw(&ogles_renderer->ogles_preview_filter->base, texture, ogles_renderer->camera->mvp_mat, st_mat, ogles_renderer->camera->aspect);
    ogles_effects_filter_draw(ogles_renderer->ogles_effects_filter, texture);
    ogles_present_filter_draw(&ogles_renderer->ogles_present_filter->base, texture);
}

void ogles_renderer_destroy(struct ogles_renderer *ogles_renderer)
{
    camera_destroy(ogles_renderer->camera);

    ogles_preview_filter_release(&ogles_renderer->ogles_preview_filter->base);
    ogles_effects_filter_release(ogles_renderer->ogles_effects_filter);
    ogles_present_filter_release(&ogles_renderer->ogles_present_filter->base);

    free(ogles_renderer->ogles_preview_filter);
    free(ogles_renderer->ogles_effects_filter);
    free(ogles_renderer->ogles_present_filter);

    free(ogles_renderer);
}
