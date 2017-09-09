//
// Created by showtime on 9/3/2017.
//

#ifndef EXOPLAYER_GRAPHICS_GFX_H
#define EXOPLAYER_GRAPHICS_GFX_H

#include "ogles.h"

#include <stdbool.h>

enum api_type
{
    API_NULL,
    API_OGLES,
    API_VULKAN
};

struct renderer
{
    const char* name;
    enum api_type api_type;
    void (*resize)(uint32_t width, uint32_t height);
    void (*draw)(void);
    void (*destroy)(void);
};

bool init_gfx(void);

#endif //EXOPLAYER_GRAPHICS_GFX_H
