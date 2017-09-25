//
// Created by showtime on 9/12/2017.
//

#include "math_util.h"

#include <math.h>

float length(float x, float y, float z)
{
    return sqrtf(x * x + y * y + z * z);
}

float deg2rad(float deg)
{
    return deg / 360.0F * 2.0F * PI;
}

float rad2deg(float rad)
{
    return rad / 2.0F / PI * 360.0F;
}