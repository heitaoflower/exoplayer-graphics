//
// Created by showtime on 9/16/2017.
//

#include "mesh_factory.h"

#include "../utils/log_util.h"
#include "../math/common.h"

#include <malloc.h>
#include <string.h>
#include <math.h>

struct mesh *create_plane_mesh(void) {

    LOGI("create_plane_mesh");

    mesh *plane_mesh;
    plane_mesh = (mesh *)malloc(sizeof(mesh));
    memset(plane_mesh, 0, sizeof(mesh));

    float width = 3;
    float height = 2;
    int segments_width = 2;
    int segments_height = 2;
    int num_texture_tiles = 1;

    int i, j;
    int num_vertices = (segments_width + 1) * (segments_height + 1);
    float vertices[num_vertices * 3];
    float uvs[num_vertices * 2];
    int indices[segments_width * segments_height * 6];

    int vertex_count = 0;
    int uv_count = 0;

    for (i = 0; i <= segments_width; i++) {
        for (j = 0; j <= segments_height; j++) {
            float v1 = ((float) i / (float) segments_width - 0.5f) * width;
            float v2 = ((float) j / (float) segments_height - 0.5f) * height;

            vertices[vertex_count] = v1;
            vertices[vertex_count + 1] = v2;
            vertices[vertex_count + 2] = 0;

            float u = (float) i / (float) segments_width;
            uvs[uv_count++] = u * num_texture_tiles;
            float v = (float) j / (float) segments_height;
            uvs[uv_count++] = (1.0f - v) * num_texture_tiles;

            vertex_count += 3;
        }
    }

    int col_span = segments_height + 1;
    int index_count = 0;

    for (int col = 0; col < segments_width; col++)
    {
        for (int row = 0; row < segments_height; row++)
        {
            int ul = col * col_span + row;
            int ll = ul + 1;
            int ur = (col + 1) * col_span + row;
            int lr = ur + 1;

            indices[index_count++] = (int) ur;
            indices[index_count++] = (int) lr;
            indices[index_count++] = (int) ul;

            indices[index_count++] = (int) lr;
            indices[index_count++] = (int) ll;
            indices[index_count++] = (int) ul;
        }
    }

    // TODO
    return NULL;
}

struct mesh *create_sphere_mesh(void)
{
    mesh *sphere_mesh;
    sphere_mesh = (mesh *)malloc(sizeof(mesh));
    memset(sphere_mesh, 0, sizeof(mesh));

    LOGI("create_sphere_mesh");
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
