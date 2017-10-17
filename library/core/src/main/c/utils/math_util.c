//
// Created by showtime on 9/12/2017.
//

#include "math_util.h"

#include <math.h>

float deg2rad(float deg)
{
    return deg / 360.0F * 2.0F * PI;
}

float rad2deg(float rad)
{
    return rad / 2.0F / PI * 360.0F;
}