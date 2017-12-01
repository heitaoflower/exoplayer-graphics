//
// Created by showtime on 9/3/2017.
//

#ifndef EXOGFX_GRAPHICS_GFX_H
#define EXOGFX_GRAPHICS_GFX_H

#include "ogles/ogles.h"

#include <stdbool.h>

enum api_type
{
    API_UNKNOWN,
    API_OGLES20,
    API_VULKAN
};

bool gfx_init(void);

void gfx_deinit(void);

#endif //EXOGFX_GRAPHICS_GFX_H
