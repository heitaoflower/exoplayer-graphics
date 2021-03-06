//
// Created by showtime on 10/14/2017.
//

#include "head_tracker.h"
#include "orientation_ekf.h"
#include "../utils/math_util.h"
#include "../math/vec3.h"
#include "../math/euler.h"

#include <malloc.h>
#include <sys/prctl.h>

static bool running = false;

static struct head_tracker_context *context;

static pthread_t tracker_tid;

static void head_tracker_process_acc(struct orientation_ekf *orientation_ekf, float x, float y, float z, int64_t timestamp)
{
    struct vec3 vec3;
    vec3_set(&vec3, x, y, z);
    orientation_ekf_process_acc(orientation_ekf, &vec3, timestamp);
}

static void head_tracker_process_gyro(struct orientation_ekf *orientation_ekf, float x, float y, float z, int64_t timestamp)
{
    struct vec3 vec3;
    vec3_set(&vec3, x, y, z);
    orientation_ekf_process_gyro(orientation_ekf, &vec3, timestamp);
}

static struct head_tracker_context* tracker_context_create()
{
    struct head_tracker_context *context = (struct head_tracker_context*)malloc(sizeof(struct head_tracker_context));
    memset(context, 0, sizeof(struct head_tracker_context));
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

    context->orientation_ekf = malloc(sizeof(struct orientation_ekf));
    orientation_ekf_init(context->orientation_ekf);
    orientation_ekf_reset(context->orientation_ekf);

    context->display_rotation = DisplayRotationUnknown;
    mat4_identity(&context->neck_model_translation);
    mat4_set_translate(&context->neck_model_translation, 0.0f, -DEFAULT_NECK_VERTICAL_OFFSET, DEFAULT_NECK_HORIZONTAL_OFFSET);
    context->neck_model_enabled = DEFAULT_NECK_MODEL_ENABLED;

    return context;

}

static void head_tracker_context_release(struct head_tracker_context *context)
{
    ASensorManager_destroyEventQueue(context->sensor_manager, context->event_queue);
    pthread_mutex_destroy(context->lock);
    free(context->lock);
    free(context);
}

static void* head_tracker_worker(__attribute__((unused)) void *data)
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

                        head_tracker_process_acc(
                                context->orientation_ekf,
                                event.data[0],
                                event.data[1],
                                event.data[2],
                                event.timestamp
                        );

                        pthread_mutex_unlock(context->lock);
                    }else if (event.type == ASENSOR_TYPE_GYROSCOPE)
                    {
                        pthread_mutex_lock(context->lock);
                        gettimeofday(&context->last_gyro_time, NULL);
                        head_tracker_process_gyro(
                                context->orientation_ekf,
                                event.data[0],
                                event.data[1],
                                event.data[2],
                                event.timestamp
                        );
                        pthread_mutex_unlock(context->lock);
                    }
                }
            }
        }
    }

    head_tracker_context_release(context);

    return NULL;
}

void head_tracker_start(void)
{
    pthread_create(&tracker_tid, NULL, head_tracker_worker, NULL);
}

void head_tracker_stop(void)
{
    if (!running) return;

    if (context != NULL)
    {
        ASensorEventQueue_disableSensor(context->event_queue, context->acc);
        ASensorEventQueue_disableSensor(context->event_queue, context->gyro);
        ALooper_wake(context->looper);
    }
    running = false;

    pthread_join(tracker_tid, NULL);
}

void head_tracker_set_neck_model_enabled(bool enabled)
{
    if (context != NULL)
    {
        context->neck_model_enabled = enabled;
    }
}

void head_tracker_get_last_view(mat4 *head_view, int32_t display_rotation)
{
    if (context == NULL)
    {
        mat4_identity(head_view);
        return;
    }

    float rotation;
    switch (display_rotation)
    {
        case DisplayRotation0:
        {
            rotation = 0.0f;
            break;
        }
        case DisplayRotation90:
        {
            rotation = 90.0f;
            break;
        }
        case DisplayRotation180:
        {
            rotation = 180.0f;
            break;
        }
        case DisplayRotation270:
        {
            rotation = 270.0f;
            break;
        }
        default:
        {
            rotation = 0.0f;
        }
    }

    static mat4 ekf_to_head_tracker;
    static mat4 sensor_to_display;
    if (rotation != context->display_rotation)
    {
        context->display_rotation = rotation;
        struct vec3 angle;
        vec3_set(&angle, deg2rad(-90.0f), deg2rad(0.0f), deg2rad(rotation));
        euler_zyx(&angle, &ekf_to_head_tracker);
        vec3_set(&angle, deg2rad(0.0f), deg2rad(0.0f), deg2rad(-rotation));
        euler_zyx(&angle, &sensor_to_display);
    }

    struct timeval now;
    gettimeofday(&now, NULL);
    double seconds_since_last_gyro_event = (double)now.tv_sec + (double)(now.tv_usec / 1000000.0f) - (double)context->last_gyro_time.tv_sec - (double)(context->last_gyro_time.tv_usec / 1000000.0f);
    double seconds_to_predict_forward = seconds_since_last_gyro_event + 1.0f / 30;
    pthread_mutex_lock(context->lock);
    orientation_ekf_get_predicted_gl_matrix(context->orientation_ekf, (float)seconds_to_predict_forward, head_view);
    pthread_mutex_unlock(context->lock);

    mat4_multiply(head_view, &sensor_to_display, head_view);
    mat4_multiply(head_view, head_view, &ekf_to_head_tracker);

    if (context->neck_model_enabled)
    {
        mat4_multiply(head_view, &context->neck_model_translation, head_view);
        mat4_translate(head_view, 0.0f, DEFAULT_NECK_VERTICAL_OFFSET, 0.0f);
    }
}