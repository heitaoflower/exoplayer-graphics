//
// Created by showtime on 9/8/2017.
//

#ifndef EXOPLAYER_GRAPHICS_CONTEXT_H
#define EXOPLAYER_GRAPHICS_CONTEXT_H

#include <stdbool.h>
#include <stdint.h>
#include "ogles.h"

enum api_type
{
    API_UNKNOWN,
    API_OGLES,
    API_VULKAN
};

struct exogfx_renderer
{
    const char *name;
    enum api_type api_type;
    void (*create)(GLuint texture);
    void (*resize)(GLsizei width, GLsizei height);
    void (*draw)(GLuint texture, const float st_mat[]);
    void (*destroy)(void);
};

extern struct exogfx_renderer ogles_renderer;
extern struct exogfx_renderer vulkan_renderer;

extern struct exogfx_renderer *renderer;

bool context_init(void);

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
