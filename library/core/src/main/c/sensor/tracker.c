//
// Created by showtime on 10/14/2017.
//

#include "tracker.h"
#include "../utils/math_util.h"
#include "../math/vec3.h"

#include <pthread.h>
#include <malloc.h>
#include <sys/prctl.h>

#define SENSOR_REFRESH_PERIOD_US 20000

static bool running = false;
static struct tracker_context *context;
static pthread_t tracker_tid;

static void tracker_process_acc(float x, float y, float z, int64_t timestamp)
{
    struct vec3 vec3;
    vec3_set(&vec3, x, y, z);

    //ekf.process_acc(vec3, timestamp);
}

static void tracker_process_gyro(float x, float y, float z, int64_t timestamp)
{
    struct vec3 vec3;
    vec3_set(&vec3, x, y, z);

    //ekf.process_gyro(vec3, timestamp);
}

static struct tracker_context * tracker_context_create()
{
    struct tracker_context *context = (struct tracker_context*)malloc(sizeof(struct tracker_context));
    memset(context, 0, sizeof(struct tracker_context));
    context->sensor_manager = ASensorManager_getInstance();
    context->acc = ASensorManager_getDefaultSensor(context->sensor_manager, ASENSOR_TYPE_ACCELEROMETER);
    context->gyro = ASensorManager_getDefaultSensor(context->sensor_manager, ASENSOR_TYPE_GYROSCOPE);
    context->acc_min_delay = ASensor_getMinDelay(context->acc);
    context->gyro_min_delay = ASensor_getMinDelay(context->gyro);

    if (context->acc == NULL || context->gyro == NULL)
    {
        free(context);
        return NULL;
    }

    context->looper = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
    context->event_queue = ASensorManager_createEventQueue(
            context->sensor_manager,
            context->looper,
            LOOPER_ID_USER,
            NULL,
            NULL
    );

    ASensorEventQueue_enableSensor(context->event_queue, context->acc);
    ASensorEventQueue_enableSensor(context->event_queue, context->gyro);

    ASensorEventQueue_setEventRate(context->event_queue, context->acc, SENSOR_REFRESH_PERIOD_US > context->acc_min_delay ? SENSOR_REFRESH_PERIOD_US : context->acc_min_delay);
    ASensorEventQueue_setEventRate(context->event_queue, context->gyro, SENSOR_REFRESH_PERIOD_US > context->gyro_min_delay ? SENSOR_REFRESH_PERIOD_US : context->gyro_min_delay);
    context->lock = malloc(sizeof(pthread_mutex_t));
    pthread_mutex_init(context->lock, NULL);

    return context;

}

static void tracker_context_release(struct tracker_context *context)
{
    ASensorManager_destroyEventQueue(context->sensor_manager, context->event_queue);
    pthread_mutex_destroy(context->lock);
    free(context->lock);
    free(context);
}

static void* tracker_thread(__attribute__((unused)) void *data)
{
    prctl(PR_SET_NAME, __func__);
    context = tracker_context_create();
    if (context == NULL) { return NULL; }

    struct android_poll_source* source;
    running = true;
    while (running)
    {
        int ident;
        int events;
        while (running && (ident = ALooper_pollAll(-1, NULL, &events, (void**)&source)) > 0)
        {
            if (ident == LOOPER_ID_USER)
            {
                ASensorEvent event;
                while (ASensorEventQueue_getEvents(context->event_queue, &event, 1) > 0)
                {
                    if (event.type == ASENSOR_TYPE_ACCELEROMETER)
                    {
                        pthread_mutex_lock(context->lock);

                        tracker_process_acc(
                                -event.data[1],
                                event.data[0],
                                event.data[2],
                                event.timestamp
                        );

                        pthread_mutex_unlock(context->lock);
                    }else if (event.type == ASENSOR_TYPE_GYROSCOPE)
                    {
                        pthread_mutex_lock(context->lock);
                        gettimeofday(&context->last_gyro_time, NULL);
                        tracker_process_gyro(
                                -event.data[1],
                                event.data[0],
                                event.data[2],
                                event.timestamp
                        );
                        pthread_mutex_unlock(context->lock);
                    }
                }
            }
        }
    }

    tracker_context_release(context);

    return NULL;
}

void tracker_start(void)
{
    pthread_create(&tracker_tid, NULL, tracker_thread, NULL);
}

void tracker_stop(void)
{

}
