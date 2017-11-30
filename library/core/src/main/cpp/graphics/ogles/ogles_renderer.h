//
// Created by showtime on 11/29/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_RENDERER_H
#define EXOGFX_GRAPHICS_OGLES_RENDERER_H

#include "../../math/camera.h"
#include "ogles_preview_filter.h"
#include "ogles_effects_filter.h"
#include "ogles_present_filter.h"

typedef struct ogles_renderer
{
    static struct camera *camera;

    ogles_preview_filter *ogles_preview_filter;
    ogles_effects_filter *ogles_effects_filter;
    ogles_present_filter *ogles_present_filter;
};


#endif //EXOGFX_GRAPHICS_OGLES_RENDERER_H
