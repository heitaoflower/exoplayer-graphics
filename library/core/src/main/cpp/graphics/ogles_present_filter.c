//
// Created by showtime on 9/10/2017.
//
#include "ogles_present_filter.h"
#include "../utils/ogles_util.h"

#define LINE(s) s "\n"
static const char *vertex_shader_source =
        LINE("attribute vec4 aPosition;")
        LINE("attribute vec4 aTextureCoord;")
        LINE("varying highp vec2 vTextureCoord;")
        LINE("void main() {")
        LINE("gl_Position = aPosition;")
        LINE("vTextureCoord = aTextureCoord.xy;")
        LINE("}");

static const char *fragment_shader_source =
        LINE("precision mediump float;")
        LINE("varying highp vec2 vTextureCoord;")
        LINE("uniform lowp sampler2D sTexture;")
        LINE("void main() {")
        LINE("gl_FragColor = texture2D(sTexture, vTextureCoord);")
        LINE("}");
#undef LINE

ogles_filter_init(present)
(struct ogles_present_filter *filter, primitive_type primitive_type, bool create_fbo)
{
    ogles_present_filter_safe_release(filter);

    filter->base.vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_source);
    filter->base.fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    filter->base.program = createProgram(filter->base.vertex_shader, filter->base.fragment_shader);
    filter->base.primitive = create_primitive(primitive_type);;

    ogles_present_filter_register_handle(filter);
}

ogles_filter_resize(present)
(struct ogles_present_filter *filter, GLint width, GLint height)
{

}

ogles_filter_pre_draw(present)
(struct ogles_present_filter *filter)
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glClear(GL_COLOR_BUFFER_BIT);

    if (filter->base.primitive != NULL)
    {
        (*filter->base.primitive->update)(filter->base.primitive);
    }
}

ogles_filter_draw(present)
(struct ogles_present_filter *filter, GLuint *texture)
{
    ogles_present_filter_use_program(filter);
    ogles_present_filter_pre_draw(filter);

    glBindBuffer(GL_ARRAY_BUFFER, filter->base.primitive->vbo_vertices);
    glEnableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glVertexAttribPointer((GLuint)filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, filter->base.primitive->vbo_uvs);
    glEnableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);
    glVertexAttribPointer((GLuint)filter->attributes.aTextureCoord.location, VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glUniform1i(filter->uniforms.sTexture.location, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, filter->base.primitive->vbo_indices);
    glDrawElements(GL_TRIANGLES, filter->base.primitive->elements_count, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray((GLuint)filter->attributes.aPosition.location);
    glDisableVertexAttribArray((GLuint)filter->attributes.aTextureCoord.location);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ogles_present_filter_post_draw(filter);

}

ogles_filter_post_draw(present)
(struct ogles_present_filter *filter)
{

}

ogles_filter_safe_release(present)
(struct ogles_present_filter *filter)
{
    filter->base.program = 0;
    filter->base.vertex_shader = 0;
    filter->base.fragment_shader = 0;

    safe_free_primitive(filter->base.primitive);
    filter->base.primitive = NULL;
}

ogles_filter_release(present)
(struct ogles_present_filter *filter)
{
    glDeleteProgram(filter->base.program);
    glDeleteShader(filter->base.vertex_shader);
    glDeleteShader(filter->base.fragment_shader);

    ogles_present_filter_safe_release(filter);
}

ogles_filter_use_program(present)(struct ogles_present_filter *filter)
{
    glUseProgram(filter->base.program);
}

ogles_filter_register_handle(present)
(struct ogles_present_filter *filter)
{
    // Uniforms
    filter->uniforms.sTexture.location = glGetUniformLocation(filter->base.program, filter->uniforms.sTexture.name);
    if (filter->uniforms.sTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.sTexture.name); }

    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->base.program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aTextureCoord.location = glGetAttribLocation(filter->base.program, filter->attributes.aTextureCoord.name);
    if (filter->attributes.aTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aTextureCoord.name); }
}