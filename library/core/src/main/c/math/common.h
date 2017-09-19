//
// Created by showtime on 9/12/2017.
//

#ifndef EXOGFX_MATH_COMMON_H
#define EXOGFX_MATH_COMMON_H

#include <stdbool.h>

#ifndef PI
#define PI 3.14159265358979323846264338327950288419716939937510f
#endif

#pragma pack(1)

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

typedef struct vec4 mat4[4];

#pragma pack()

float length(float x, float y, float z);

float deg2rad(float deg);

float rad2deg(float rad);

#endif //EXOPLAYER_MATH_COMMON_H
