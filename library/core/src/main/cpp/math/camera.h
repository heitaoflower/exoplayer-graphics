//
// Created by showtime on 9/23/2017.
//

#ifndef EXOGFX_MATH_CAMERA_H
#define EXOGFX_MATH_CAMERA_H

#include "mat4.h"

#include <inttypes.h>

typedef enum
{
    ProjectionTypeOrtho, ProjectionTypeFrustum, ProjectionTypePerspective
} projection_type;

typedef enum eye_type
{
    EyeTypeBoth, EyeTypeLeft, EyeTypeRight
} eye_type;

struct camera{
    eye_type eye_type;
    projection_type projection_type;
    mat4 model_mat;
    mat4 view_mat;
    mat4 projection_mat;
    mat4 mvp_mat;
    int32_t viewport_width;
    int32_t viewport_height;
    float aspect;
};

void camera_init(struct camera *camera, eye_type eye_type, projection_type projection_type);

void camera_rotate_yaw(struct camera *camera, float angle);

void camera_rotate_pitch(struct camera *camera, float angle);

void camera_rotate_roll(struct camera *camera, float angle);

void camera_set_lookat(struct camera *camera);

void camera_set_viewport(struct camera *camera, int width, int height);

void camera_set_projection(struct camera *camera, projection_type projection_type);

void camera_update(struct camera *camera);

#endif //EXOGFX_MATH_CAMERA_H
