//
// Created by showtime on 9/19/2017.
//

#include "plane.h"
#include "../math/mat4.h"
#include "../utils/ogles_util.h"

#include <malloc.h>

static void update(struct primitive *primitive)
{

}

struct primitive *primitive_plane_create(void)
{
    struct primitive *primitive = (struct primitive *)malloc(sizeof(struct primitive));
    struct mesh * plane_mesh = create_plane_mesh(1, 1, 10, 10, AxisZ, true);

    primitive->type = Plane;
    primitive->vbo_vertices = createBuffer(GL_ARRAY_BUFFER, plane_mesh->vertices, plane_mesh->vertice_size * sizeof(float));
    primitive->vbo_uvs = createBuffer(GL_ARRAY_BUFFER, plane_mesh->uvs, plane_mesh->uv_size * sizeof(float));
    primitive->vbo_indices = createBuffer(GL_ELEMENT_ARRAY_BUFFER, plane_mesh->indices, plane_mesh->index_size * sizeof(uint32_t));
    primitive->elements_count = plane_mesh->index_size;
    destroy_mesh(plane_mesh);

    mat4_identity(&primitive->model_matrix);

    primitive->update = &update;

    return primitive;
}
