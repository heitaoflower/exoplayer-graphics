//
// Created by showtime on 11/29/2017.
//

#include <GLES2/gl2.h>
#include "vr_ogles_engine.h"
#include "../../sensor/head_tracker.h"
#include "../../graphics/ogles/ogles_eye.h"

void vr_ogles_engine_init(struct vr_ogles_engine *vr_ogles_engine)
{
    ogles_eye_init(&vr_ogles_engine->both_ogles_camera, EyeTypeBoth, ProjectionTypePerspective);
    ogles_eye_init(&vr_ogles_engine->left_ogles_camera, EyeTypeLeft, ProjectionTypePerspective);
    ogles_eye_init(&vr_ogles_engine->right_ogles_camera, EyeTypeRight, ProjectionTypePerspective);

    ogles_eye_set_lookat_default(&vr_ogles_engine->both_ogles_camera);
    ogles_eye_set_lookat_default(&vr_ogles_engine->left_ogles_camera);
    ogles_eye_set_lookat_default(&vr_ogles_engine->right_ogles_camera);
}

void vr_ogles_engine_resize(struct vr_ogles_engine *vr_ogles_engine, GLsizei width, GLsizei height)
{
    ogles_eye_resize(&vr_ogles_engine->both_ogles_camera, width, height);
    ogles_eye_resize(&vr_ogles_engine->left_ogles_camera, width, height);
    ogles_eye_resize(&vr_ogles_engine->right_ogles_camera, width, height);
}

void vr_ogles_engine_draw(struct vr_ogles_engine *vr_ogles_engine, int32_t display_rotation)
{
    mat4 head_view;
    head_tracker_get_last_view(&head_view, display_rotation);

    mat4_copy(&head_view, &vr_ogles_engine->both_ogles_camera.camera.model_mat);
    mat4_copy(&head_view, &vr_ogles_engine->left_ogles_camera.camera.model_mat);
    mat4_copy(&head_view, &vr_ogles_engine->right_ogles_camera.camera.model_mat);

    ogles_eye_update(&vr_ogles_engine->both_ogles_camera);
    ogles_eye_update(&vr_ogles_engine->left_ogles_camera);
    ogles_eye_update(&vr_ogles_engine->right_ogles_camera);
}

void vr_ogles_engine_release(struct vr_ogles_engine *vr_ogles_engine)
{

}