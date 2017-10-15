//
// Created by showtime on 10/15/2017.
//

#ifndef EXOGFX_ORIENTATION_EKF_H
#define EXOGFX_ORIENTATION_EKF_H

#include "../math/vec3.h"

#include <stdint.h>

void oritentation_ekf_reset(void);

void orientation_ekf_release(void);

void process_gyro(struct vec3, int64_t timestamp);

void process_acc(struct vec3, int64_t timestamp);

#endif //EXOGFX_ORIENTATION_EKF_H
