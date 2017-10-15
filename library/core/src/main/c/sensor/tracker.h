//
// Created by showtime on 10/14/2017.
//

#ifndef EXOGFX_TRACKER_H
#define EXOGFX_TRACKER_H

#include <android/looper.h>
#include <android/sensor.h>
#include <time.h>

enum {LOOPER_ID_USER = 3};

struct tracker_context
{
    ASensorManager *sensor_manager;
    ASensor const *acc;
    ASensor const *gyro;
    int acc_min_delay;
    int gyro_min_delay;
    ALooper *looper;
    ASensorEventQueue *event_queue;
    pthread_mutex_t *lock;
    struct timeval last_gyro_time;
};

void tracker_start(void);

void tracker_stop(void);

#endif //EXOGFX_TRACKER_H
