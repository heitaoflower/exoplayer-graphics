//
// Created by showtime on 9/19/2017.
//

#include "plane.h"
#include <malloc.h>

struct primitive *primitive_plane_create(void)
{
    struct primitive *primitive = (struct primitive *)malloc(sizeof(struct primitive));
    primitive->type = Plane;
    primitive->mesh = create_plane_mesh(1, 1, 10, 10, AxisZ, true);

    return primitive;
}
