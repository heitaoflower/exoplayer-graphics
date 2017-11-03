//
// Created by showtime on 9/16/2017.
//
#include "primitive.h"
#include "plane.h"
#include "quad.h"
#include "sphere.h"
#include "../utils/log_util.h"

#include <malloc.h>

struct primitive *create_primitive(primitive_type type)
{
    switch (type)
    {
        case Sphere:
        {
            return primitive_sphere_create();
        }
        case Cube:
        {
            return NULL;
        }
        case Plane:
        {
            return primitive_plane_create();
        }
        case Quad:
        {
            return primitive_quad_create();
        }
        default:
        {
            LOGE("invalid mesh type input.");
        }
    }

    return NULL;
}

void safe_free_primitive(struct primitive *primitive)
{
    if (primitive != NULL)
    {
        primitive->vbo_vertices = 0;
        primitive->vbo_uvs = 0;
        primitive->vbo_indices = 0;
        primitive->elements_count = 0;

        free(primitive);
    }
}

void free_primitive(struct primitive *primitive)
{
    if (primitive != NULL)
    {
        glDeleteBuffers(1, &primitive->vbo_vertices);
        glDeleteBuffers(1, &primitive->vbo_uvs);
        glDeleteBuffers(1, &primitive->vbo_indices);

        safe_free_primitive(primitive);
    }

}