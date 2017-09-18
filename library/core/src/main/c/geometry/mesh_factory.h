//
// Created by showtime on 9/16/2017.
//

#ifndef EXOGFX_GEOMETRY_MESH_FACTORY_H
#define EXOGFX_GEOMETRY_MESH_FACTORY_H

#include <stdint.h>

typedef struct {
    float* vertices;
    float* uvs;
    uint32_t *triangles;
    uint32_t vertice_count;
    uint32_t uv_count;
    uint32_t triangle_count;
} mesh;

struct mesh *create_sphere_mesh(void);
struct mesh *create_cube_mesh(void);
struct mesh *create_plane_mesh(void);

#endif //EXOGFX_GEOMETRY_MESH_FACTORY_H
