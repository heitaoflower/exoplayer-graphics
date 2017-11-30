//
// Created by showtime on 11/29/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_RENDERER_H
#define EXOGFX_GRAPHICS_OGLES_RENDERER_H

#include "../../math/camera.h"
#include "ogles_preview_filter.h"
#include "ogles_effects_filter.h"
#include "ogles_present_filter.h"

struct ogles_renderer
{
    const char *name;
    struct camera *camera;
    struct ogles_preview_filter *ogles_preview_filter;
    struct ogles_effects_filter *ogles_effects_filter;
    struct ogles_present_filter *ogles_present_filter;
};

struct ogles_renderer *ogles_renderer_create(void);

void ogles_renderer_init(struct ogles_renderer *ogles_renderer, GLuint texture);

void ogles_renderer_resize(struct ogles_renderer *ogles_renderer, GLsizei width, GLsizei height);

void ogles_renderer_draw(struct ogles_renderer *ogles_renderer, GLuint *texture, const float st_mat[]);

void ogles_renderer_destroy(struct ogles_renderer *ogles_renderer);

#endif //EXOGFX_GRAPHICS_OGLES_RENDERER_H
