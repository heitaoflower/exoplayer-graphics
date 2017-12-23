//
// Created by showtime on 12/22/2017.
//

#include "distortion.h"
#include "mesh_factory.h"
#include "primitive.h"
#include "../utils/ogles_util.h"
#include "../math/mat4.h"
#include "../math/camera.h"

#include <malloc.h>
#include <math.h>

static void update(struct primitive *primitive)
{

}


static float distortion_factor(float radius)
{
    const uint32_t num_coefficients = 2;
    float coefficients[num_coefficients] = {0.441000015f, 0.156000003f};

    float result = 1.0f;
    float r_factor = 1.0f;
    float squared_radius = radius * radius;
    for (uint32_t i = 0; i < num_coefficients; i++)
    {
        r_factor *= squared_radius;
        result += coefficients[i] * r_factor;
    }

    return result;
}

static float distort(float radius)
{
    return radius * distortion_factor(radius);
}

static float blue_distort_inverse(float radius)
{
    float r0 = radius / 0.9f;
    float r = radius * 0.9f;
    float dr0 = radius - distort(r0);
    while (fabsf(r - r0) > 0.0001f)
    {
        float dr = radius - distort(r);
        float r2 = r - dr * ((r - r0) / (dr - dr0));
        r0 = r;
        r = r2;
        dr0 = dr;
    }
    return r;
}

static struct primitive *primitive_distortion_create(float x_eye_offset_screen, float viewport_x_texture, float x_eye_offset_texture)
{
    struct primitive *primitive = (struct primitive *)malloc(sizeof(struct primitive));

    float screen_width = 2.47470069f;
    float screen_height = 1.39132345f;
    float y_eye_offset_screen = 0.80952388f;
    float texture_width = 2.86276627f;
    float texture_height = 1.51814604f;
    float y_eye_offset_texture = 0.839099586f;
    float viewport_y_texture = 0;
    float viewport_width_texture = 1.43138313f;
    float viewport_height_texture = 1.51814604f;

    struct mesh* distortion_mesh = create_distortion_mesh(screen_width, screen_height,
                                                          x_eye_offset_screen, y_eye_offset_screen,
                                                          texture_width, texture_height,
                                                          x_eye_offset_texture, y_eye_offset_texture,
                                                          viewport_x_texture, viewport_y_texture,
                                                          viewport_width_texture, viewport_height_texture,
                                                          blue_distort_inverse, distortion_factor);

    primitive->type = PrimitiveTypeDistortion;
    primitive->vbo_vertices = createBuffer(GL_ARRAY_BUFFER, distortion_mesh->vertices, distortion_mesh->vertice_size * sizeof(float));
    primitive->vbo_indices = createBuffer(GL_ELEMENT_ARRAY_BUFFER, distortion_mesh->indices, distortion_mesh->index_size * sizeof(uint32_t));
    primitive->elements_count = distortion_mesh->index_size;
    destroy_mesh(distortion_mesh);

    mat4_identity(&primitive->model_matrix);

    primitive->update = &update;

    return primitive;
}

struct primitive *primitive_distortion_right_create()
{
    const float x_eye_offset_screen = 0.523064613f;
    const float viewport_x_texture = 0;
    const float x_eye_offset_texture = 0.592283607f;

    return primitive_distortion_create(x_eye_offset_screen, viewport_x_texture, x_eye_offset_texture);
}

struct primitive *primitive_distortion_left_create()
{
    const float x_eye_offset_screen = 1.95163608f;
    const float x_eye_offset_texture = 2.27048278f;
    const float viewport_x_texture = 1.43138313f;

    return primitive_distortion_create(x_eye_offset_screen, viewport_x_texture, x_eye_offset_texture);
}