//
// Created by showtime on 9/16/2017.
//

#ifndef EXOGFX_MESH_H
#define EXOGFX_MESH_H

#include "mesh_types.h"

typedef struct mesh
{
    model_type type;
};

struct mesh* create_model(model_type type);

void free_model(struct mesh *model);

#endif //EXOGFX_MESH_H
