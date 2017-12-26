//
// Created by showtime on 12/23/2017.
//

#include "ogles_distortion_filter.h"
#include "../../utils/ogles_util.h"
#include "../../geometry/primitive.h"
#include "../../math/camera.h"

#include <malloc.h>

#define LINE(s) s "\n"
static const char *vertex_shader_source =
        LINE("uniform float uTextureCoordScale;")
        LINE("attribute vec2 aPosition;")
        LINE("attribute float aVignette;")
        LINE("attribute vec2 aRedTextureCoord;")
        LINE("attribute vec2 aGreenTextureCoord;")
        LINE("attribute vec2 aBlueTextureCoord;")
        LINE("varying highp vec2 vRedTextureCoord;")
        LINE("varying highp vec2 vGreenTextureCoord;")
        LINE("varying highp vec2 vBlueTextureCoord;")
        LINE("varying float vVignette;")
        LINE("void main() {")
        LINE("gl_Position = vec4(aPosition, 0.0, 1.0);")
        LINE("vRedTextureCoord = aRedTextureCoord.xy * uTextureCoordScale;")
        LINE("vGreenTextureCoord = aGreenTextureCoord.xy * uTextureCoordScale;")
        LINE("vBlueTextureCoord = aBlueTextureCoord.xy * uTextureCoordScale;")
        LINE("vVignette = aVignette;")
        LINE("}");

static const char *fragment_shader_source =
        LINE("precision mediump float;")
        LINE("varying vec2 vRedTextureCoord;")
        LINE("varying vec2 vBlueTextureCoord;")
        LINE("varying vec2 vGreenTextureCoord;")
        LINE("varying float vVignette;")
        LINE("uniform sampler2D uTexture;")
        LINE("void main() {")
        LINE("gl_FragColor = vVignette * vec4(texture2D(uTexture, vRedTextureCoord).r, texture2D(uTexture, vGreenTextureCoord).g, texture2D(uTexture, vBlueTextureCoord).b, 1.0);")
        LINE("}");
#undef LINE

ogles_filter_init(distortion)
(struct ogles_distortion_filter *filter, primitive_type primitive_type, bool create_fbo)
{
    ogles_distortion_filter_safe_release(filter);

    filter->base.vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_source);
    filter->base.fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    filter->base.program = createProgram(filter->base.vertex_shader, filter->base.fragment_shader);
    filter->base.primitive = create_primitive(primitive_type);
    filter->left_eye_primitive = create_primitive(PrimitiveTypeLeftDistortion);
    filter->right_eye_primitive = create_primitive(PrimitiveTypeRightDistortion);
    filter->base.fbo = create_fbo ? malloc(sizeof(struct ogles_fbo)) : NULL;
    ogles_distortion_filter_register_handle(filter);
}

ogles_filter_release(distortion)
(struct ogles_distortion_filter *filter)
{
    glDeleteProgram(filter->base.program);
    glDeleteShader(filter->base.vertex_shader);
    glDeleteShader(filter->base.fragment_shader);

    ogles_distortion_filter_safe_release(filter);
}

ogles_filter_safe_release(distortion)
(struct ogles_distortion_filter *filter)
{
    filter->base.program = 0;
    filter->base.vertex_shader = 0;
    filter->base.fragment_shader = 0;

    safe_free_primitive(filter->left_eye_primitive);
    safe_free_primitive(filter->right_eye_primitive);
    safe_free_primitive(filter->base.primitive);
    filter->base.primitive = NULL;
}

ogles_filter_resize(distortion)
(struct ogles_distortion_filter *filter, GLint width, GLint height)
{
}

ogles_filter_pre_draw(distortion)
(struct ogles_distortion_filter *filter, struct ogles_eye *ogles_eye)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (filter->base.primitive != NULL)
    {
        (*filter->base.primitive->update)(filter->base.primitive);
    }
}

ogles_filter_draw(distortion)
(struct ogles_distortion_filter *filter, GLuint *texture, struct ogles_eye *left_ogles_eye, struct ogles_eye *right_ogles_eye)
{
    ogles_distortion_filter_use_program(filter);
    ogles_distortion_filter_pre_draw(filter, NULL);
    //glDisable(GL_SCISSOR_TEST);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_SCISSOR_TEST);

    glScissor(0, 0, left_ogles_eye->camera.viewport.width, left_ogles_eye->camera.viewport.height);
    glBindBuffer(GL_ARRAY_BUFFER, filter->left_eye_primitive->vbo_vertices);
    glVertexAttribPointer((GLuint)filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE_2, GL_FLOAT, GL_FALSE, 9 * sizeof(GL_FLOAT), 0);
//    glEnableVertexAttribArray((GLuint) program->positon_location);
//    glVertexAttribPointer((GLuint) program->vignette_location, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)(2 * sizeof(float)));
//    glEnableVertexAttribArray((GLuint) program->vignette_location);
}

ogles_filter_post_draw(distortion)
(struct ogles_distortion_filter *filter, GLuint *texture, struct ogles_eye *ogles_eye)
{
    *texture = filter->base.fbo->rendertexture;
}

ogles_filter_use_program(distortion)
(struct ogles_distortion_filter *filter)
{
    glUseProgram(filter->base.program);
}

ogles_filter_register_handle(distortion)
(struct ogles_distortion_filter *filter)
{
    // Uniforms
    filter->uniforms.uTexture.location = glGetUniformLocation(filter->base.program, filter->uniforms.uTexture.name);
    if (filter->uniforms.uTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uTexture.name);}
    filter->uniforms.uTextureCoordScale.location = glGetUniformLocation(filter->base.program, filter->uniforms.uTextureCoordScale.name);
    if (filter->uniforms.uTextureCoordScale.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uTextureCoordScale.name);}

    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->base.program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aVignette.location = glGetAttribLocation(filter->base.program, filter->attributes.aVignette.name);
    if (filter->attributes.aVignette.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aVignette.name); }
    filter->attributes.aRedTextureCoord.location = glGetAttribLocation(filter->base.program, filter->attributes.aRedTextureCoord.name);
    if (filter->attributes.aRedTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aRedTextureCoord.name); }
    filter->attributes.aGreenTextureCoord.location = glGetAttribLocation(filter->base.program, filter->attributes.aGreenTextureCoord.name);
    if (filter->attributes.aGreenTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aGreenTextureCoord.name); }
    filter->attributes.aBlueTextureCoord.location = glGetAttribLocation(filter->base.program, filter->attributes.aBlueTextureCoord.name);
    if (filter->attributes.aBlueTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aBlueTextureCoord.name); }
}