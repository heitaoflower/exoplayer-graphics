//
// Created by showtime on 10/14/2017.
//

#ifndef EXOGFX_HEAD_TRACKER_H
#define EXOGFX_HEAD_TRACKER_H

#include "../math/mat4.h"
#include "orientation_ekf.h"

#include <android/looper.h>
#include <android/sensor.h>
#include <time.h>
#include <pthread.h>

#define SENSOR_REFRESH_PERIOD_US 1000000L / 60

enum looper_id_type {LOOPER_ID_USER = 3};

enum display_rotation {DisplayRotation0, DisplayRotation90, DisplayRotation180, DisplayRotation270, DisplayRotationUnknown};

struct head_tracker_context
{
    ASensorManager *sensor_manager;
    ASensor const *acc;
    ASensor const *gyro;
    int acc_min_delay;
    int gyro_min_delay;
    ALooper *looper;
    ASensorEventQueue *event_queue;
    pthread_mutex_t *lock;
    struct orientation_ekf *orientation_ekf;
    struct timeval last_gyro_time;
    float display_rotation;
};

void head_tracker_start(void);

void head_tracker_stop(void);

void head_tracker_get_last_view(mat4 *head_view, int32_t display_rotation);

#endif //EXOGFX_HEAD_TRACKER_H
