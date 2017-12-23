//
// Created by showtime on 9/16/2017.
//

#ifndef EXOGFX_GEOMETRY_MESH_FACTORY_H
#define EXOGFX_GEOMETRY_MESH_FACTORY_H

#include "../utils/math_util.h"
#include <stdint.h>

struct mesh {
    float* vertices;
    float* uvs;
    uint32_t *indices;
    uint32_t vertice_size;
    uint32_t uv_size;
    uint32_t index_size;
};

struct mesh *create_sphere_mesh(float radius, uint32_t h_segments, uint32_t v_segments, bool mirror_uvs);

struct mesh *create_cube_mesh(void);

struct mesh *create_plane_mesh(float width, float height, uint32_t h_segments, uint32_t v_segments, enum axis up_axis, bool mirror_uvs);

struct mesh *create_quad_mesh(float width, float height);

struct mesh *create_distortion_mesh(float screen_width, float screen_height,
                                    float x_eye_offset_screen, float y_eye_offset_screen,
                                    float texture_width, float texture_height,
                                    float x_eye_offset_texture, float y_eye_offset_texture,
                                    float viewport_x_texture, float viewport_y_texture,
                                    float viewport_width_texture, float viewport_height_texture,
                                    float (*blue_distort_inverse)(float), float (*distortion_factor)(float));

void destroy_mesh(struct mesh *mesh);

#endif //EXOGFX_GEOMETRY_MESH_FACTORY_H
