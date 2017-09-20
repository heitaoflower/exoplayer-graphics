//
// Created by showtime on 9/16/2017.
//
#include "primitive.h"
#include "plane.h"
#include "../utils/log_util.h"

#include <malloc.h>

struct primitive *create_primitive(primitive_type type)
{
    switch (type)
    {
        case Sphere:
        {
            return NULL;
        }
        case Cube:
            return NULL;
        case Plane:
            return primitive_plane_create();
        default:
            LOGE("invalid mesh type input.");
    }

    return NULL;
}

void free_primitive(struct primitive *primitive)
{
    if (primitive != NULL)
    {
        free(primitive);
    }

}