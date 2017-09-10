//
// Created by showtime on 9/8/2017.
//
#include "context.h"
#include "gfx.h"

struct exogfx_renderer *renderer;

bool init_context(void)
{
    // TODO select ogles or vulkan, for now only ogles
    init_gfx();

    renderer = &ogles_renderer;

    return true;
}