//
// Created by showtime on 9/20/2017.
//

#include "quad.h"

#include <malloc.h>

struct primitive *primitive_quad_create(void)
{
    struct primitive *primitive = (struct primitive *)malloc(sizeof(struct primitive));
    primitive->type = Quad;
    primitive->mesh = create_quad_mesh();

    return primitive;
}