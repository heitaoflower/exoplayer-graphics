//
// Created by showtime on 9/8/2017.
//
#include "context.h"
#include "gfx.h"

struct exogfx_renderer *renderer;

bool context_init(void)
{
    // TODO select ogles or vulkan, for now only ogles
    gfx_init();

    renderer = &ogles_renderer;

    return true;
}