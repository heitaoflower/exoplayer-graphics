//
// Created by showtime on 9/16/2017.
//
#include "mesh.h"
#include "mesh_factory.h"
#include "../utils/log_util.h"

#include <stddef.h>

struct mesh *create_mesh(mesh_type type)
{
    switch (type)
    {
        case Sphere:
        {
            return create_sphere_mesh();
        }
        case Cube:
            return create_cube_mesh();
        case Plane:
            return create_plane_mesh();
        default:
            LOGE("invalid mesh type input.");
    }

    return NULL;
}

void free_mesh(struct mesh *mesh)
{
    LOGI("free_model");
}