//
// Created by showtime on 9/12/2017.
//

#ifndef EXOGFX_UTILS_MATH_UTIL_H
#define EXOGFX_UTILS_MATH_UTIL_H

#include <stdbool.h>

#define PI    (float)M_PI
#define PI_2  (float)M_PI_2
#define PI_4  (float)M_PI_4

#pragma pack(1)

enum axis {
    AxisX, AxisY, AxisZ
};

struct vec2
{
    float x, y;
};

struct vec3
{
    float x, y, z;
};

struct vec4
{
    float x, y, z, w;
};

typedef struct vec3 mat3[3];
typedef struct vec4 mat4[4];

#pragma pack()

float deg2rad(float deg);

float rad2deg(float rad);

int signum(int value);

float clamp(float value, float min, float max);

#endif //EXOGFX_UTILS_MATH_UTIL_H
