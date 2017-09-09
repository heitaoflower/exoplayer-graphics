//
// Created by showtime on 9/9/2017.
//
#include "context.h"
#include "../utils/logUtil.h"

static void create(void)
{
    LOGI("create");
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
