//
// Created by showtime on 9/16/2017.
//

#include "mesh_factory.h"

#include "../utils/log_util.h"

#include <malloc.h>
#include <string.h>

struct mesh *create_sphere_mesh(void)
{
    struct mesh *sphere = (struct mesh *) malloc(sizeof(struct mesh));
    memset(sphere, 0, sizeof(struct mesh));

    return sphere;
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