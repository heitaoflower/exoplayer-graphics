//
// Created by showtime on 9/9/2017.
//
#include "context.h"
#include "ogles_fbo.h"
#include "ogles_filter.h"
#include "../utils/log_util.h"

static struct ogles_fbo fbo;
static struct ogles_filter filter;

static void create(void)
{
    ogles_filter_init(&filter);
}

static void resize(GLint width, GLint height)
{
    ogles_fbo_init(&fbo, width, height);
    ogles_filter_resize(&filter, width, height);
}

static void draw(void)
{

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
