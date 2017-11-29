//
// Created by showtime on 9/12/2017.
//

#ifndef EXOGFX_UTILS_MATH_UTIL_H
#define EXOGFX_UTILS_MATH_UTIL_H

#include <stdbool.h>

#ifndef PI
#define PI 3.14159265358979323846264338327950288419716939937510f
#endif

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

#endif //EXOGFX_UTILS_MATH_UTIL_H
