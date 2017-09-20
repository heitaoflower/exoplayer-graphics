//
// Created by showtime on 9/16/2017.
//

#include "mesh_factory.h"

#include <malloc.h>
#include <string.h>
#include <math.h>

struct mesh *create_plane_mesh(float width, float height, uint32_t h_segments, uint32_t v_segments, enum axis up_axis, bool mirror_uvs) {

    struct mesh *plane_mesh;
    plane_mesh = (struct mesh *)malloc(sizeof(struct mesh));
    memset(plane_mesh, 0, sizeof(struct mesh));

    uint32_t num_vertices , num_uvs;
    num_vertices = num_uvs = (v_segments + 1) * (h_segments + 1);

    plane_mesh->vertice_size = num_vertices * 3;
    plane_mesh->uv_size = num_uvs * 2;
    plane_mesh->index_size = v_segments * h_segments * 6;

    plane_mesh->vertices = (float *)malloc((size_t)(sizeof(float) * plane_mesh->vertice_size));
    plane_mesh->uvs = (float *)malloc((size_t)(sizeof(float) * plane_mesh->uv_size));
    plane_mesh->indices = (uint32_t *)malloc((size_t)(sizeof(uint32_t) * plane_mesh->index_size));

    uint32_t vertex_counter = 0;
    uint32_t uv_counter = 0;

    for (uint32_t i = 0; i <= v_segments; i++) {
        for (uint32_t j = 0; j <= h_segments; j++) {
            float v1 = ((float) i / (float) v_segments - 0.5f) * width;
            float v2 = ((float) j / (float) h_segments - 0.5f) * height;

            if (up_axis == AxisX)
            {
                plane_mesh->vertices[vertex_counter] = v1;
                plane_mesh->vertices[vertex_counter + 1] = 0;
                plane_mesh->vertices[vertex_counter + 2] = v2;
            }
            else if (up_axis == AxisY)
            {
                plane_mesh->vertices[vertex_counter] = v1;
                plane_mesh->vertices[vertex_counter + 1] = v2;
                plane_mesh->vertices[vertex_counter + 2] = 0;
            }
            else if (up_axis == AxisZ)
            {
                plane_mesh->vertices[vertex_counter] = v1;
                plane_mesh->vertices[vertex_counter + 1] = v2;
                plane_mesh->vertices[vertex_counter + 2] = 0;
            }

            float u = (float) i / (float) v_segments;
            plane_mesh->uvs[uv_counter++] = mirror_uvs ? 1.0f - u : u;

            float v = (float) j / (float) h_segments;
            plane_mesh->uvs[uv_counter++] = 1.0f - v;

            vertex_counter += 3;
        }
    }

    uint32_t col_span = h_segments + 1;
    uint32_t index_counter = 0;

    for (uint32_t col = 0; col < v_segments; col++)
    {
        for (uint32_t row = 0; row < h_segments; row++)
        {
            uint32_t ul = col * col_span + row;
            uint32_t ll = ul + 1;
            uint32_t ur = (col + 1) * col_span + row;
            uint32_t lr = ur + 1;

            plane_mesh->indices[index_counter++] = ur;
            plane_mesh->indices[index_counter++] = lr;
            plane_mesh->indices[index_counter++] = ul;

            plane_mesh->indices[index_counter++] = lr;
            plane_mesh->indices[index_counter++] = ll;
            plane_mesh->indices[index_counter++] = ul;
        }
    }

    return plane_mesh;
}

struct mesh *create_sphere_mesh(void)
{
    struct mesh *sphere_mesh;
    sphere_mesh = (struct mesh *)malloc(sizeof(struct mesh));
    memset(sphere_mesh, 0, sizeof(struct mesh));

    int segment_width = 15, segment_height = 15;
    float radius = 1.0f;

    int num_vertices = (segment_width + 1) * (segment_height + 1);
    int num_indices = 2 * segment_width * (segment_height - 1) * 3;

    float vertices[num_vertices * 3];
    int indices[num_indices];

    int i, j;
    int vertice_index = 0, index = 0;

    for (j = 0; j < segment_height; ++j)
    {
        float h_angle = PI * j / segment_height;
        float z = radius * cosf(h_angle);
        float ring_radius = radius * sinf(h_angle);

    }

    // Should free data.

    return NULL;
}

struct mesh *create_cube_mesh(void)
{
    // TODO
    return NULL;
}
