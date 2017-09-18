//
// Created by showtime on 9/16/2017.
//

#include "mesh_factory.h"

#include "../utils/log_util.h"

#include <malloc.h>
#include <string.h>

struct mesh *create_sphere_mesh(void)
{
    mesh *sphere_mesh;
    sphere_mesh = (mesh *)malloc(sizeof(mesh));

    memset(sphere_mesh, 0, sizeof(mesh));

    LOGI("create_sphere_mesh");

    return NULL;
}

struct mesh *create_cube_mesh(void)
{
    // TODO
    return NULL;
}

struct mesh *create_plane_mesh(void)
{
    // TODO
    return NULL;
}