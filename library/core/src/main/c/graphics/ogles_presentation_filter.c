//
// Created by showtime on 9/10/2017.
//
#include "ogles_presentation_filter.h"
#include "../utils/ogles_util.h"

#define L(s) s "\n"
static const char *vertex_shader =
        L("attribute vec4 aPosition;")
        L("attribute vec4 aTextureCoord;")
        L("varying highp vec2 vTextureCoord;")
        L("void main() {")
        L("gl_Position = aPosition;")
        L("vTextureCoord = aTextureCoord.xy;")
        L("}");

static const char *fragment_shader =
        L("precision mediump float;")
        L("varying highp vec2 vTextureCoord;")
        L("uniform lowp sampler2D sTexture;")
        L("void main() {")
        L("gl_FragColor = texture2D(sTexture, vTextureCoord);")
        L("}");
#undef L

ogles_filter_init(presentation)
(struct ogles_presentation_filter *filter, struct primitive *primitive)
{
    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->vbo_vertices = createBuffer(GL_ARRAY_BUFFER, primitive->mesh->vertices, primitive->mesh->vertice_size * sizeof(float));
    filter->vbo_uvs = createBuffer(GL_ARRAY_BUFFER, primitive->mesh->uvs, primitive->mesh->uv_size * sizeof(float));
    filter->vbo_indices = createBuffer(GL_ELEMENT_ARRAY_BUFFER, primitive->mesh->indices, primitive->mesh->index_size * sizeof(uint32_t));
    filter->elements_count = primitive->mesh->index_size;

    free_primitive(primitive);

    ogles_presentation_filter_register_handle(filter);
}

ogles_filter_resize(presentation)
(struct ogles_presentation_filter *filter, GLint width, GLint height)
{

}

ogles_filter_draw(presentation)
(struct ogles_presentation_filter *filter, GLuint texture)
{
    ogles_presentation_filter_use_program(filter);

    glBindBuffer(GL_ARRAY_BUFFER, filter->vbo_vertices);
    glEnableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glVertexAttribPointer((GLuint)filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, filter->vbo_uvs);
    glEnableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);
    glVertexAttribPointer((GLuint)filter->attributes.aTextureCoord.location, VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(filter->uniforms.sTexture.location, 0);

    ogles_presentation_filter_draw_cb(filter);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, filter->vbo_indices);
    glDrawElements(GL_TRIANGLES, filter->elements_count, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glDisableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

ogles_filter_draw_cb(presentation)
(struct ogles_presentation_filter *filter)
{

}

ogles_filter_safe_release(presentation)
(struct ogles_presentation_filter *filter)
{
    filter->program = 0;
    filter->vertex_shader = 0;
    filter->fragment_shader = 0;
    filter->vbo_vertices = 0;
    filter->vbo_uvs = 0;
    filter->vbo_indices = 0;
}

ogles_filter_release(presentation)
(struct ogles_presentation_filter *filter)
{
    glDeleteProgram(filter->program);
    glDeleteShader(filter->vertex_shader);
    glDeleteShader(filter->fragment_shader);
    glDeleteBuffers(1, &filter->vbo_vertices);
    glDeleteBuffers(1, &filter->vbo_uvs);
    glDeleteBuffers(1, &filter->vbo_indices);

    ogles_presentation_filter_safe_release(filter);

}

ogles_filter_use_program(presentation)(struct ogles_presentation_filter *filter)
{
    glUseProgram(filter->program);
}

ogles_filter_register_handle(presentation)
(struct ogles_presentation_filter *filter)
{
    // Uniforms
    filter->uniforms.sTexture.location = glGetUniformLocation(filter->program, filter->uniforms.sTexture.name);
    if (filter->uniforms.sTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.sTexture.name); }

    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aTextureCoord.location = glGetAttribLocation(filter->program, filter->attributes.aTextureCoord.name);
    if (filter->attributes.aTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aTextureCoord.name); }
}