//
// Created by showtime on 11/29/2017.
//

#ifndef EXOGFX_VR_OGLES_ENGINE_H
#define EXOGFX_VR_OGLES_ENGINE_H

typedef struct ogles_vr_renderer
{

} ogles_vr_renderer;

void ogles_vr_draw(ogles_vr_renderer *vr_renderer);

void ogles_setup_renderer(void);

void ogles_unload_renderer();

#endif //EXOGFX_VR_OGLES_ENGINE_H
