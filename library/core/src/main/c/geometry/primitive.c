//
// Created by showtime on 9/16/2017.
//
#include "primitive.h"
#include "mesh_factory.h"
#include "../utils/log_util.h"

#include <stddef.h>

struct primitive *create_primitive(primitive_type type)
{
    switch (type)
    {
        case Sphere:
        {
            create_sphere_mesh();
            return NULL;
        }
        case Cube:
            return NULL;
        case Plane:
            return NULL;
        default:
            LOGE("invalid mesh type input.");
    }

    return NULL;
}

void free_primitive(struct primitive *primitive)
{
    LOGI("free_model");
}