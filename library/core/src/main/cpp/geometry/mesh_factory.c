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

    plane_mesh->vertices = (float *)malloc((sizeof(float) * plane_mesh->vertice_size));
    plane_mesh->uvs = (float *)malloc((sizeof(float) * plane_mesh->uv_size));
    plane_mesh->indices = (uint32_t *)malloc((sizeof(uint32_t) * plane_mesh->index_size));

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

struct mesh *create_quad_mesh(float width, float height)
{
    struct mesh *quad_mesh;
    quad_mesh = (struct mesh *)malloc(sizeof(struct mesh));
    memset(quad_mesh, 0, sizeof(struct mesh));

    const float vertices[] =
            {      -width,   height,  0.0f,
                    width,   height,  0.0f,
                   -width,  -height,  0.0f,
                    width,  -height,  0.0f };

    const float uvs[] =
            {
                    0.0f, 1.0f,
                    1.0f, 1.0f,
                    0.0f, 0.0f,
                    1.0f, 0.0f };

    const int indices[] = { 3, 2, 1, 2, 0, 1 };

    quad_mesh->vertice_size = sizeof(vertices)/sizeof(float) * 3;
    quad_mesh->uv_size = sizeof(uvs)/sizeof(float) * 2;
    quad_mesh->index_size = 6;

    quad_mesh->vertices = (float *)malloc(sizeof(vertices));
    quad_mesh->uvs = (float *)malloc((sizeof(uvs)));
    quad_mesh->indices = (uint32_t *)malloc(sizeof(indices));

    memcpy(quad_mesh->vertices, vertices, sizeof(vertices));
    memcpy(quad_mesh->uvs, uvs, sizeof(uvs));
    memcpy(quad_mesh->indices, indices, sizeof(indices));

    return quad_mesh;
}

struct mesh *create_sphere_mesh(float radius, uint32_t h_segments, uint32_t v_segments, bool mirror_uvs)
{
    struct mesh *sphere_mesh;
    sphere_mesh = (struct mesh *)malloc(sizeof(struct mesh));
    memset(sphere_mesh, 0, sizeof(struct mesh));

    uint32_t num_vertices = (h_segments + 1) * (v_segments + 1);
    uint32_t num_uvs = num_vertices;
    uint32_t num_indices = 2 * h_segments * (v_segments - 1) * 3;

    sphere_mesh->vertice_size = num_vertices * 3;
    sphere_mesh->uv_size = num_uvs * 2;
    sphere_mesh->index_size = num_indices;

    sphere_mesh->vertices = (float *)malloc((sizeof(float) * sphere_mesh->vertice_size));
    sphere_mesh->uvs = (float *)malloc((sizeof(float) * sphere_mesh->uv_size));
    sphere_mesh->indices = (uint32_t *)malloc((sizeof(uint32_t) * sphere_mesh->index_size));

    uint32_t vertex_counter = 0, index_counter = 0;

    for (uint32_t j = 0; j <= v_segments; ++j)
    {
        float v_angle = PI * j / v_segments;
        float z = radius * cosf(v_angle);
        float ring_radius = radius * sinf(v_angle);

        for (uint32_t i = 0; i <= h_segments; i++)
        {
            float h_angle = 2.0f * PI * i / h_segments;
            float x = ring_radius * cosf(h_angle);
            float y = ring_radius * sinf(h_angle);

            sphere_mesh->vertices[vertex_counter++] = x;
            sphere_mesh->vertices[vertex_counter++] = z;
            sphere_mesh->vertices[vertex_counter++] = y;

            if (i > 0 && j > 0)
            {
                uint32_t a = (h_segments + 1) * j + i;
                uint32_t b = (h_segments + 1) * j + i - 1;
                uint32_t c = (h_segments + 1) * (j - 1) + i - 1;
                uint32_t d = (h_segments + 1) * (j - 1) + i;

                if (j == v_segments)
                {
                    sphere_mesh->indices[index_counter++] = a;
                    sphere_mesh->indices[index_counter++] = c;
                    sphere_mesh->indices[index_counter++] = d;
                }
                else if (j == 1)
                {
                    sphere_mesh->indices[index_counter++] = a;
                    sphere_mesh->indices[index_counter++] = b;
                    sphere_mesh->indices[index_counter++] = c;
                }
                else
                {
                    sphere_mesh->indices[index_counter++] = a;
                    sphere_mesh->indices[index_counter++] = b;
                    sphere_mesh->indices[index_counter++] = c;
                    sphere_mesh->indices[index_counter++] = a;
                    sphere_mesh->indices[index_counter++] = c;
                    sphere_mesh->indices[index_counter++] = d;
                }
            }
        }
    }

    uint32_t uv_counter = 0;
    for (int32_t j = 0; j <= v_segments; ++j)
    {
        for (int32_t i = h_segments; i >= 0; --i)
        {
            float u = (float) i / h_segments;
            float v = (float) j / v_segments;
            sphere_mesh->uvs[uv_counter++] = mirror_uvs ? 1.0f - u : u;
            sphere_mesh->uvs[uv_counter++] = mirror_uvs ? 1.0f - v : v;
        }
    }

    return sphere_mesh;
}

struct mesh *create_distortion_mesh(float screen_width, float screen_height,
                                    float x_eye_offset_screen, float y_eye_offset_screen,
                                    float texture_width, float texture_height,
                                    float x_eye_offset_texture, float y_eye_offset_texture,
                                    float viewport_x_texture, float viewport_y_texture,
                                    float viewport_width_texture, float viewport_height_texture,
                                    float (*blue_distort_inverse)(float), float (*distortion_factor)(float))
{
    struct mesh *distortion_mesh;
    distortion_mesh = (struct mesh *)malloc(sizeof(struct mesh));
    memset(distortion_mesh, 0, sizeof(struct mesh));

    const float vignette_size_tan_angle = 0.05f;
    uint32_t rows = 40;
    uint32_t cols = 40;

    distortion_mesh->vertice_size = rows * cols * 9;
    distortion_mesh->vertices = (float*)malloc((sizeof(float) * distortion_mesh->vertice_size));
    distortion_mesh->uv_size = 0;
    distortion_mesh->uvs = NULL;

    uint32_t  vertex_counter = 0;
    for (uint32_t row = 0; row < rows; row++)
    {
        for (uint32_t col = 0; col < cols; col++)
        {
            const float u_texture_blue = col / 39.0f * (viewport_width_texture / texture_width) + viewport_x_texture / texture_width;
            const float v_texture_blue = row / 39.0f * (viewport_height_texture / texture_height) + viewport_y_texture / texture_height;

            const float x_texture = u_texture_blue * texture_width - x_eye_offset_texture;
            const float y_texture = v_texture_blue * texture_height - y_eye_offset_texture;
            const float r_texture = sqrtf(x_texture * x_texture + y_texture + y_texture);

            const float texture_to_screen_blue = (r_texture > 0.0) ? blue_distort_inverse(r_texture) / r_texture : 1.0f;

            const float x_screen = x_texture * texture_to_screen_blue;
            const float y_screen = y_texture * texture_to_screen_blue;

            const float u_screen = (x_screen + x_eye_offset_screen) / screen_width;
            const float v_screen = (y_screen + y_eye_offset_screen) / screen_height;
            const float r_screen = r_texture * texture_to_screen_blue;

            const float screen_to_texture_green = (r_screen > 0.0f) ? distortion_factor(r_screen) : 1.0f;
            const float u_texture_green = (x_screen * screen_to_texture_green + x_eye_offset_texture) / texture_width;
            const float v_texture_green = (y_screen * screen_to_texture_green + y_eye_offset_texture) / texture_height;

            const float screen_to_texture_red = (r_screen > 0.0f) ? distortion_factor(r_screen) : 1.0f;
            const float u_texture_red = (x_screen * screen_to_texture_red + x_eye_offset_texture) / texture_width;
            const float v_texture_red = (y_screen * screen_to_texture_red + y_eye_offset_texture) / texture_height;

            const float vignette_size_texture = vignette_size_tan_angle / texture_to_screen_blue;

            const float dx_texture = x_texture + x_eye_offset_texture - clamp(x_texture + x_eye_offset_texture, viewport_x_texture + vignette_size_texture, viewport_x_texture + viewport_width_texture - vignette_size_texture);
            const float dy_texture = y_texture + y_eye_offset_texture - clamp(y_texture + y_eye_offset_texture, viewport_y_texture + vignette_size_texture, viewport_y_texture + viewport_height_texture - vignette_size_texture);
            const float dr_texture = sqrtf(dx_texture * dx_texture + dy_texture * dy_texture);

            float vignette = 1.0f - clamp(dr_texture / vignette_size_texture, 0.0f, 1.0f);

            distortion_mesh->vertices[(vertex_counter + 0)] = 2.0f * u_screen - 1.0f;
            distortion_mesh->vertices[(vertex_counter + 1)] = 2.0f * v_screen - 1.0f;
            distortion_mesh->vertices[(vertex_counter + 2)] = vignette;
            distortion_mesh->vertices[(vertex_counter + 3)] = u_texture_red;
            distortion_mesh->vertices[(vertex_counter + 4)] = v_texture_red;
            distortion_mesh->vertices[(vertex_counter + 5)] = u_texture_green;
            distortion_mesh->vertices[(vertex_counter + 6)] = v_texture_green;
            distortion_mesh->vertices[(vertex_counter + 7)] = u_texture_blue;
            distortion_mesh->vertices[(vertex_counter + 8)] = v_texture_blue;

            vertex_counter += 9;

            distortion_mesh->index_size = (rows - 1) * (cols - 1) * 6;
            distortion_mesh->indices = (uint32_t *)malloc((sizeof(uint32_t) * distortion_mesh->index_size));
            uint32_t index_counter = 0;
            for (uint32_t i = 0; i < rows - 1; ++i)
            {
                for (uint32_t j = 0; j < cols - 1; ++j)
                {
                    distortion_mesh->indices[index_counter++] = (j * cols + i);
                    distortion_mesh->indices[index_counter++] = ((j + 1) * cols + i);
                    distortion_mesh->indices[index_counter++] = ((j + 1) * cols + i + 1);

                    distortion_mesh->indices[index_counter++] = (j * cols + i);
                    distortion_mesh->indices[index_counter++] = ((j + 1) * cols + i + 1);
                    distortion_mesh->indices[index_counter++] = (j * cols + i + 1);
                }
            }
        }
    }
    return distortion_mesh;
}

struct mesh *create_cube_mesh(void)
{
    return NULL;
}

void destroy_mesh(struct mesh *mesh)
{
    if (mesh != NULL)
    {
        if (mesh->vertices != NULL)
        {
            free(mesh->vertices);
        }

        if (mesh->uvs != NULL)
        {
            free(mesh->uvs);
        }

        if (mesh->indices != NULL)
        {
            free(mesh->indices);
        }

        free(mesh);
    }
}
