//
// Created by showtime on 9/16/2017.
//

#ifndef EXOGFX_GEOMETRY_PRIMITIVE_H
#define EXOGFX_GEOMETRY_PRIMITIVE_H

#include "../graphics/ogles.h"
#include "primitive_type.h"
#include "mesh_factory.h"

struct primitive
{
    primitive_type type;
    GLuint vbo_vertices;
    GLuint vbo_uvs;
    GLuint vbo_indices;
    GLuint elements_count;
};

struct primitive* create_primitive(primitive_type type);

void safe_free_primitive(struct primitive *primitive);

void free_primitive(struct primitive *primitive);

#endif //EXOGFX_GEOMETRY_PRIMITIVE_H
