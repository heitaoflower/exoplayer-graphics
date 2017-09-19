//
// Created by showtime on 9/16/2017.
//

#ifndef EXOGFX_GEOMETRY_PRIMITIVE_H
#define EXOGFX_GEOMETRY_PRIMITIVE_H

#include "primitive_type.h"
#include "mesh_factory.h"

struct primitive
{
    primitive_type type;
    struct mesh *mesh;
};

struct primitive* create_primitive(primitive_type type);

void free_primitive(struct primitive *primitive);

#endif //EXOGFX_GEOMETRY_PRIMITIVE_H
