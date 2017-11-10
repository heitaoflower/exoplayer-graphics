//
// Created by showtime on 11/10/2017.
//

#include "ogles_gray_filter.h"
#include "../utils/ogles_util.h"

#define STR(s) s "\n"
static const char *vertex_shader_source =
        STR("attribute vec4 aPosition;")
                STR("attribute vec4 aTextureCoord;")
                STR("varying highp vec2 vTextureCoord;")
                STR("void main() {")
                STR("gl_Position = aPosition;")
                STR("vTextureCoord = aTextureCoord.xy;")
                STR("}");

static const char *fragment_shader_source =
        STR("precision mediump float;")
                STR("varying highp vec2 vTextureCoord;")
                STR("uniform lowp sampler2D sTexture;")
                STR("void main() {")
                STR("gl_FragColor = texture2D(sTexture, vTextureCoord);")
                STR("}");
#undef STR

ogles_filter_init(gray)
(struct ogles_gray_filter *filter, struct primitive *primitive)
{
    ogles_gray_filter_safe_release(filter);

    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_source);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->primitive = primitive;

    ogles_gray_filter_register_handle(filter);
}

ogles_filter_resize(gray)
(struct ogles_gray_filter *filter, GLint width, GLint height)
{

}

ogles_filter_pre_draw(gray)
(struct ogles_gray_filter *filter)
{

}

ogles_filter_draw(gray)
(struct ogles_gray_filter *filter, GLuint texture)
{
    ogles_gray_filter_pre_draw(filter);
    ogles_gray_filter_use_program(filter);

    glBindBuffer(GL_ARRAY_BUFFER, filter->primitive->vbo_vertices);
    glEnableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glVertexAttribPointer((GLuint)filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, filter->primitive->vbo_uvs);
    glEnableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);
    glVertexAttribPointer((GLuint)filter->attributes.aTextureCoord.location, VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(filter->uniforms.sTexture.location, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, filter->primitive->vbo_indices);
    glDrawElements(GL_TRIANGLES, filter->primitive->elements_count, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glDisableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ogles_gray_filter_post_draw(filter);
}

ogles_filter_post_draw(gray)
(struct ogles_gray_filter *filter)
{

}

ogles_filter_safe_release(gray)
(struct ogles_gray_filter *filter)
{
    filter->program = 0;
    filter->vertex_shader = 0;
    filter->fragment_shader = 0;

    safe_free_primitive(filter->primitive);
    filter->primitive = NULL;
}

ogles_filter_release(gray)
(struct ogles_gray_filter *filter)
{
    glDeleteProgram(filter->program);
    glDeleteShader(filter->vertex_shader);
    glDeleteShader(filter->fragment_shader);

    ogles_gray_filter_safe_release(filter);
}

ogles_filter_use_program(gray)
(struct ogles_gray_filter *filter)
{
    glUseProgram(filter->program);
}

ogles_filter_register_handle(gray)
(struct ogles_gray_filter *filter)
{
    // Uniforms
    filter->uniforms.sTexture.location = glGetUniformLocation(filter->program, filter->uniforms.sTexture.name);
    if (filter->uniforms.sTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.sTexture.name);}

    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aTextureCoord.location = glGetAttribLocation(filter->program, filter->attributes.aTextureCoord.name);
    if (filter->attributes.aTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aTextureCoord.name); }
}