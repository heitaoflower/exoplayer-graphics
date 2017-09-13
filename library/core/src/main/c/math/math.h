//
// Created by showtime on 9/12/2017.
//

#ifndef EXOPLAYER_MATH_H
#define EXOPLAYER_MATH_H

#include <stdbool.h>

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

typedef struct vec3 mat3[3];
typedef struct vec3 mat4x3[4];
typedef struct vec4 mat4[4];

#pragma pack()

#endif //EXOPLAYER_MATH_H
