//
// Created by showtime on 9/10/2017.
//
#include "ogles_video_filter.h"
#include "../utils/ogles_util.h"

#define L(s) s "\n"
static const char *vertex_shader =
        L("uniform mat4 uMVPMatrix;")
        L("uniform mat4 uSTMatrix;")
        L("uniform float uAspect;")

        L("attribute vec4 aPosition;")
        L("attribute vec4 aTextureCoord;")
        L("varying highp vec2 vTextureCoord;")

        L("void main() {")
        L("vec4 scaledPosition = aPosition;")
        L("scaledPosition.x = scaledPosition.x * uAspect;")
        L("gl_Position = uMVPMatrix * scaledPosition;")
        L("vTextureCoord = (uSTMatrix * aTextureCoord).xy;")
        L("}");

static const char *fragment_shader =
        L("#extension GL_OES_EGL_image_external : require")
        L("precision mediump float;")
        L("varying highp vec2 vTextureCoord;")
        L("uniform lowp samplerExternalOES sTexture;")
        L("void main() {")
        L("gl_FragColor = texture2D(sTexture, vTextureCoord);")
        L("}");
#undef L

ogles_filter_init(video)
(struct ogles_video_filter *filter, struct primitive *primitive)
{
    ogles_video_filter_safe_release(filter);

    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->primitive = primitive;
    filter->target = GL_TEXTURE_EXTERNAL_OES;

    ogles_video_filter_register_handle(filter);
}

ogles_filter_release(video)
(struct ogles_video_filter *filter)
{
    glDeleteProgram(filter->program);
    glDeleteShader(filter->vertex_shader);
    glDeleteShader(filter->fragment_shader);

    ogles_video_filter_safe_release(filter);
}
ogles_filter_safe_release(video)
(struct ogles_video_filter *filter)
{
    filter->program = 0;
    filter->vertex_shader = 0;
    filter->fragment_shader = 0;

    safe_free_primitive(filter->primitive);
    filter->primitive = NULL;
}

ogles_filter_resize(video)
(struct ogles_video_filter *filter, GLint width, GLint height)
{

}

ogles_filter_pre_draw(video)
(struct ogles_video_filter *filter)
{
    if (filter->primitive != NULL)
    {
        (*filter->primitive->update)(filter->primitive);
    }
}

ogles_filter_draw(video)
(struct ogles_video_filter *filter, GLuint texture, mat4 *mvp_mat, const float st_mat[], float aspect)
{
    ogles_video_filter_pre_draw(filter);

    ogles_video_filter_use_program(filter);

    glUniformMatrix4fv(filter->uniforms.uMVPMatrix.location, 1, GL_FALSE, (const float*)mvp_mat);
    glUniformMatrix4fv(filter->uniforms.uSTMatrix.location, 1, GL_FALSE, st_mat);
    glUniform1f(filter->uniforms.uAspect.location, aspect);

    glBindBuffer(GL_ARRAY_BUFFER, filter->primitive->vbo_vertices);
    glEnableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glVertexAttribPointer((GLuint)filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, filter->primitive->vbo_uvs);
    glEnableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);
    glVertexAttribPointer((GLuint)filter->attributes.aTextureCoord.location, VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(filter->target, texture);
    glUniform1i(filter->uniforms.sTexture.location, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, filter->primitive->vbo_indices);
    glDrawElements(GL_TRIANGLES, filter->primitive->elements_count, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glDisableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    ogles_video_filter_post_draw(filter);
}

ogles_filter_post_draw(video)
(struct ogles_video_filter *filter)
{

}

ogles_filter_use_program(video)
(struct ogles_video_filter *filter)
{
    glUseProgram(filter->program);
}

ogles_filter_register_handle(video)
(struct ogles_video_filter *filter)
{
    // Uniforms
    filter->uniforms.uMVPMatrix.location = glGetUniformLocation(filter->program, filter->uniforms.uMVPMatrix.name);
    if (filter->uniforms.uMVPMatrix.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uMVPMatrix.name); }
    filter->uniforms.uSTMatrix.location = glGetUniformLocation(filter->program, filter->uniforms.uSTMatrix.name);
    if (filter->uniforms.uSTMatrix.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uSTMatrix.name); }
    filter->uniforms.sTexture.location = glGetUniformLocation(filter->program, filter->uniforms.sTexture.name);
    if (filter->uniforms.sTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.sTexture.name); }
    filter->uniforms.uAspect.location = glGetUniformLocation(filter->program, filter->uniforms.uAspect.name);
    if (filter->uniforms.uAspect.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uAspect.name); }

    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aTextureCoord.location = glGetAttribLocation(filter->program, filter->attributes.aTextureCoord.name);
    if (filter->attributes.aTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aTextureCoord.name); }
}
