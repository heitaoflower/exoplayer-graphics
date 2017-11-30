//
// Created by showtime on 9/8/2017.
//

#ifndef EXOGFX_CONTEXT_H
#define EXOGFX_CONTEXT_H

#include "../graphics/ogles/ogles.h"

#include <stdbool.h>
#include <stdint.h>
#include <jni.h>

enum api_type
{
    API_UNKNOWN,
    API_OGLES20,
    API_VULKAN
};

struct exogfx_renderer
{
    const char *name;
    enum api_type api_type;
    void (*create)(GLuint texture);
    void (*resize)(GLsizei width, GLsizei height);
    void (*draw)(GLuint *texture, const float st_mat[]);
    void (*destroy)(void);
};

extern struct exogfx_renderer ogles_renderer;
extern struct exogfx_renderer vulkan_renderer;

extern struct exogfx_renderer *renderer;

bool context_init(JNIEnv *env, jobject android_context, jobject class_loader);

void context_deinit(void);

static inline bool api_is_ogles(void)
{
    switch (renderer->api_type)
    {
        case API_OGLES20:
        {
            return true;
        }
        default:
        {
            return false;
        }
    }
}

#endif //EXOGFX_CONTEXT_H
