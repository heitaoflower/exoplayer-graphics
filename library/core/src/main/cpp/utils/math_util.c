//
// Created by showtime on 9/12/2017.
//

#include "math_util.h"

#include <math.h>

float deg2rad(float deg)
{
    return deg / 360.0f * 2.0f * PI;
}

float rad2deg(float rad)
{
    return rad / 2.0F / PI * 360.0F;
}

int signum(int value)
{
    return ((value >> 31) - (-value >> 31));
}

float clamp(float value, float min, float max)
{
    float temp = value > min ? value : min;
    return temp < max ? temp : max;
}