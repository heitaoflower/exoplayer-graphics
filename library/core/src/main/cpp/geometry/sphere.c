//
// Created by showtime on 9/22/2017.

//

#include "sphere.h"
#include "../math/mat4.h"
#include "../utils/ogles_util.h"

#include <malloc.h>

static void update(struct primitive *primitive)
{
}

struct primitive *primitive_sphere_create(void)
{
    struct primitive *primitive = (struct primitive *)malloc(sizeof(struct primitive));
    struct mesh* sphere_mesh = create_sphere_mesh(1.0f, 64, 64, true);

    primitive->type = PrimitiveTypeSphere;
    primitive->vbo_vertices = createBuffer(GL_ARRAY_BUFFER, sphere_mesh->vertices, sphere_mesh->vertice_size * sizeof(float));
    primitive->vbo_uvs = createBuffer(GL_ARRAY_BUFFER, sphere_mesh->uvs, sphere_mesh->uv_size * sizeof(float));
    primitive->vbo_indices = createBuffer(GL_ELEMENT_ARRAY_BUFFER, sphere_mesh->indices, sphere_mesh->index_size * sizeof(uint32_t));
    primitive->elements_count = sphere_mesh->index_size;
    destroy_mesh(sphere_mesh);

    mat4_identity(&primitive->model_matrix);
    mat4_scale(&primitive->model_matrix, 100, 100, 100);

    primitive->update = &update;

    return primitive;
}
