//
// Created by showtime on 9/16/2017.
//
#include "primitive.h"
#include "plane.h"
#include "quad.h"
#include "sphere.h"
#include "distortion.h"
#include "../utils/log_util.h"

#include <malloc.h>

struct primitive *create_primitive(primitive_type type)
{
    switch (type)
    {
        case PrimitiveTypeSphere:
        {
            return primitive_sphere_create();
        }
        case PrimitiveTypeCube:
        {
            return NULL;
        }
        case PrimitiveTypePlane:
        {
            return primitive_plane_create();
        }
        case PrimitiveTypeQuad:
        {
            return primitive_quad_create();
        }
        case PrimitiveTypeLeftDistortion:
        {
            return primitive_distortion_left_create();
        }
        case PrimitiveTypeRightDistortion:
        {
            return primitive_distortion_right_create();
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