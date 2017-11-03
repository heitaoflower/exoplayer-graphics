//
// Created by showtime on 9/8/2017.
//
#include "context.h"
#include "../graphics/gfx.h"
#include "../sensor/head_tracker.h"

struct exogfx_renderer *renderer;

bool context_init(void)
{
    gfx_init();

    renderer = &ogles_renderer;

    head_tracker_start();

    return true;
}