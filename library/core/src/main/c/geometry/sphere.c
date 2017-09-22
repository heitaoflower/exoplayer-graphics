//
// Created by showtime on 9/22/2017.
//

#include "sphere.h"
#include "../utils/ogles_util.h"

#include <malloc.h>

struct primitive *primitive_sphere_create(void)
{
    struct primitive *primitive = (struct primitive *)malloc(sizeof(struct primitive));
    struct mesh* sphere_mesh = create_sphere_mesh(1.0f, 24, 24, false);

    primitive->type = Sphere;
    primitive->vbo_vertices = createBuffer(GL_ARRAY_BUFFER, sphere_mesh->vertices, sphere_mesh->vertice_size * sizeof(float));
    primitive->vbo_uvs = createBuffer(GL_ARRAY_BUFFER, sphere_mesh->uvs, sphere_mesh->uv_size * sizeof(float));
    primitive->vbo_indices = createBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_mesh->indices, sphere_mesh->index_size * sizeof(uint32_t));
    primitive->elements_count = sphere_mesh->index_size;
    destroy_mesh(sphere_mesh);

    return primitive;
}