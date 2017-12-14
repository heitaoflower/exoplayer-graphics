//
// Created by showtime on 9/10/2017.
//
#include "ogles_preview_filter.h"
#include "../../utils/ogles_util.h"
#include "../../geometry/primitive.h"

#include <malloc.h>

#define LINE(s) s "\n"
static const char *vertex_shader_source =
        LINE("uniform mat4 uMVPMatrix;")
        LINE("uniform mat4 uSTMatrix;")
        LINE("uniform float uAspect;")

        LINE("attribute vec4 aPosition;")
        LINE("attribute vec4 aTextureCoord;")
        LINE("varying highp vec2 vTextureCoord;")

        LINE("void main() {")
        LINE("vec4 scaledPosition = aPosition;")
        LINE("scaledPosition.x = scaledPosition.x * uAspect;")
        LINE("gl_Position = uMVPMatrix * scaledPosition;")
        LINE("vTextureCoord = (uSTMatrix * aTextureCoord).xy;")
        LINE("}");

static const char *fragment_shader_source =
        LINE("#extension GL_OES_EGL_image_external : require")
        LINE("precision mediump float;")
        LINE("varying highp vec2 vTextureCoord;")
        LINE("uniform lowp samplerExternalOES sTexture;")
        LINE("void main() {")
        LINE("gl_FragColor = texture2D(sTexture, vTextureCoord);")
        LINE("}");
#undef LINE

ogles_filter_init(preview)
(struct ogles_preview_filter *filter, primitive_type primitive_type, bool create_fbo, GLuint texture)
{
    ogles_preview_filter_safe_release(filter);

    filter->base.vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_source);
    filter->base.fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    filter->base.program = createProgram(filter->base.vertex_shader, filter->base.fragment_shader);
    filter->base.primitive = create_primitive(primitive_type);
    filter->base.fbo = create_fbo ? malloc(sizeof(struct ogles_fbo)) : NULL;
    filter->target = GL_TEXTURE_EXTERNAL_OES;

    glBindTexture(filter->target, texture);
    initSampler(filter->target, GL_LINEAR, GL_NEAREST);
    ogles_preview_filter_register_handle(filter);
}

ogles_filter_release(preview)
(struct ogles_preview_filter *filter)
{
    glDeleteProgram(filter->base.program);
    glDeleteShader(filter->base.vertex_shader);
    glDeleteShader(filter->base.fragment_shader);

    ogles_preview_filter_safe_release(filter);
}
ogles_filter_safe_release(preview)
(struct ogles_preview_filter *filter)
{
    filter->base.program = 0;
    filter->base.vertex_shader = 0;
    filter->base.fragment_shader = 0;

    safe_free_primitive(filter->base.primitive);
    ogles_fbo_safe_release(filter->base.fbo);
}

ogles_filter_resize(preview)
(struct ogles_preview_filter *filter, GLint width, GLint height)
{
    ogles_fbo_resize(filter->base.fbo, width, height);
}

ogles_filter_pre_draw(preview)
(struct ogles_preview_filter *filter)
{
    //ogles_fbo_enable(filter->base.fbo);
    if (filter->base.primitive != NULL)
    {
        (*filter->base.primitive->update)(filter->base.primitive);
    }
}

ogles_filter_draw(preview)
(struct ogles_preview_filter *filter, GLuint *texture, mat4 *mvp_mat, const float st_mat[], float aspect)
{
    ogles_preview_filter_use_program(filter);
    ogles_preview_filter_pre_draw(filter);

    glUniformMatrix4fv(filter->uniforms.uMVPMatrix.location, 1, GL_FALSE, (const float*)mvp_mat);
    glUniformMatrix4fv(filter->uniforms.uSTMatrix.location, 1, GL_FALSE, st_mat);
    glUniform1f(filter->uniforms.uAspect.location, aspect);

    glBindBuffer(GL_ARRAY_BUFFER, filter->base.primitive->vbo_vertices);
    glEnableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glVertexAttribPointer((GLuint)filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, filter->base.primitive->vbo_uvs);
    glEnableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);
    glVertexAttribPointer((GLuint)filter->attributes.aTextureCoord.location, VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(filter->target, *texture);
    glUniform1i(filter->uniforms.sTexture.location, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, filter->base.primitive->vbo_indices);
    glDrawElements(GL_TRIANGLES, filter->base.primitive->elements_count, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glDisableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    ogles_preview_filter_post_draw(filter, texture);
}

ogles_filter_post_draw(preview)
(struct ogles_preview_filter *filter, GLuint *texture)
{
    *texture = filter->base.fbo->rendertexture;
}

ogles_filter_use_program(preview)
(struct ogles_preview_filter *filter)
{
    glUseProgram(filter->base.program);
}

ogles_filter_register_handle(preview)
(struct ogles_preview_filter *filter)
{
    // Uniforms
    filter->uniforms.uMVPMatrix.location = glGetUniformLocation(filter->base.program, filter->uniforms.uMVPMatrix.name);
    if (filter->uniforms.uMVPMatrix.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uMVPMatrix.name); }
    filter->uniforms.uSTMatrix.location = glGetUniformLocation(filter->base.program, filter->uniforms.uSTMatrix.name);
    if (filter->uniforms.uSTMatrix.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uSTMatrix.name); }
    filter->uniforms.sTexture.location = glGetUniformLocation(filter->base.program, filter->uniforms.sTexture.name);
    if (filter->uniforms.sTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.sTexture.name); }
    filter->uniforms.uAspect.location = glGetUniformLocation(filter->base.program, filter->uniforms.uAspect.name);
    if (filter->uniforms.uAspect.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uAspect.name); }

    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->base.program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aTextureCoord.location = glGetAttribLocation(filter->base.program, filter->attributes.aTextureCoord.name);
    if (filter->attributes.aTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aTextureCoord.name); }
}
