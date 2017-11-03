//
// Created by showtime on 9/3/2017.
//

#ifndef EXOGFX_UTILS_LOG_UTIL_H
#define EXOGFX_UTILS_LOG_UTIL_H

#include <android/log.h>

#define LOG_TAG "libExogfx"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#endif //EXOGFX_UTILS_LOG_UTIL_H
