//
// Created by showtime on 11/29/2017.
//

#include "vr_ogles_engine.h"

void vr_ogles_engine_init(struct vr_ogles_engine *vr_ogles_engine)
{
    vr_ogles_eye_init(&vr_ogles_engine->center_eye, EYE_CENTER);
    vr_ogles_eye_init(&vr_ogles_engine->left_eye, EYE_LEFT);
    vr_ogles_eye_init(&vr_ogles_engine->right_eye, EYE_RIGHT);

}

void vr_ogles_engine_draw(struct vr_ogles_engine *vr_ogles_engine)
{

}

void vr_ogles_engine_release(struct vr_ogles_engine *vr_ogles_engine)
{

}