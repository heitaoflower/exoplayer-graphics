//
// Created by showtime on 9/8/2017.
//
#include "context.h"
#include "../graphics/gfx.h"
#include "../sensor/head_tracker.h"
#include "../graphics/ogles/ogles_renderer.h"

bool context_init(JNIEnv *env, jobject appcontext, jobject class_loader)
{
    gfx_init();

    head_tracker_start();

    return true;
}

void context_deinit(void)
{
    gfx_deinit();

    head_tracker_stop();
}