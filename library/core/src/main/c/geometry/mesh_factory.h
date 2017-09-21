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

struct mesh *create_sphere_mesh(void);

struct mesh *create_cube_mesh(void);

struct mesh *create_plane_mesh(float width, float height, uint32_t h_segments, uint32_t v_segments, enum axis up_axis, bool mirror_uvs);

struct mesh *create_quad_mesh(void);

#endif //EXOGFX_GEOMETRY_MESH_FACTORY_H
