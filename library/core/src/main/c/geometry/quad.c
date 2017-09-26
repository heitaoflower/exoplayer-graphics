//
// Created by showtime on 9/20/2017.
//

#include "quad.h"
#include "../math/mat4.h"
#include "../utils/ogles_util.h"

#include <malloc.h>

static void update(struct primitive *primitive)
{

}

struct primitive *primitive_quad_create(void)
{
    struct primitive *primitive = (struct primitive *)malloc(sizeof(struct primitive));
    struct mesh* quad_mesh = create_quad_mesh(1.0f, 1.0f);

    primitive->type = Quad;
    primitive->vbo_vertices = createBuffer(GL_ARRAY_BUFFER, quad_mesh->vertices, quad_mesh->vertice_size * sizeof(float));
    primitive->vbo_uvs = createBuffer(GL_ARRAY_BUFFER, quad_mesh->uvs, quad_mesh->uv_size * sizeof(float));
    primitive->vbo_indices = createBuffer(GL_ELEMENT_ARRAY_BUFFER, quad_mesh->indices, quad_mesh->index_size * sizeof(uint32_t));
    primitive->elements_count = quad_mesh->index_size;
    destroy_mesh(quad_mesh);

    mat4_identity(&primitive->model_matrix);

    primitive->update = &update;

    return primitive;
}