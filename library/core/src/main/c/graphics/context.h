//
// Created by showtime on 9/8/2017.
//

#ifndef EXOPLAYER_GRAPHICS_CONTEXT_H
#define EXOPLAYER_GRAPHICS_CONTEXT_H

#include <stdbool.h>
#include <stdint.h>

enum api_type
{
    API_UNKNOWN,
    API_OGLES,
    API_VULKAN
};

struct exogfx_renderer
{
    const char* name;
    enum api_type api_type;
    void (*create)(void);
    void (*resize)(size_t width, size_t height);
    void (*draw)(void);
    void (*destroy)(void);
};

extern struct exogfx_renderer ogles_renderer;
extern struct exogfx_renderer vulkan_renderer;

extern struct exogfx_renderer *renderer;

bool init_context(void);

static inline bool api_is_ogles(void)
{
    switch (renderer->api_type)
    {
        case API_OGLES:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

#endif //EXOPLAYER_GRAPHICS_CONTEXT_H
