//
// Created by showtime on 9/16/2017.
//

#ifndef EXOGFX_MESH_H
#define EXOGFX_MESH_H

#include "mesh_types.h"

typedef struct mesh
{
    mesh_type type;
};

struct mesh* create_mesh(mesh_type type);

void free_mesh(struct mesh *mesh);

#endif //EXOGFX_MESH_H
