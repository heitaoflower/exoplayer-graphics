//
// Created by showtime on 9/8/2017.
//

#ifndef EXOGFX_CONTEXT_H
#define EXOGFX_CONTEXT_H

#include "../graphics/ogles/ogles.h"
#include "../graphics/ogles/ogles_renderer.h"

#include <stdbool.h>
#include <stdint.h>
#include <jni.h>

struct ogles_renderer *ogles_renderer;

bool context_init(JNIEnv *env, jobject appcontext, jobject class_loader);

void context_deinit(void);

#endif //EXOGFX_CONTEXT_H
