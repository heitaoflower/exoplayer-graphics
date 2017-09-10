//
// Created by showtime on 9/9/2017.
//
#include "context.h"
#include "ogles_fbo.h"
#include "../utils/log_util.h"

static void create(void)
{
    LOGI("create");

    struct ogles_fbo fbo;

    ogles_fbo_setup(&fbo, 100, 200);
}

static void resize(size_t width, size_t height)
{
    LOGI("width%d", width);
}

static void draw(void)
{
    LOGI("draw");
}

static void destroy(void)
{
    LOGI("destroy");
}

struct exogfx_renderer ogles_renderer = {
        .name = "opengles",
        .api_type = API_OGLES,
        .create = create,
        .resize = resize,
        .draw = draw,
        .destroy = destroy
};
