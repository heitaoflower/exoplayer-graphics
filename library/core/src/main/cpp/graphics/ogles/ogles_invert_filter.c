//
// Created by showtime on 11/10/2017.
//
#include "ogles_invert_filter.h"
#include "../../utils/ogles_util.h"

#include <malloc.h>

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
        LINE("varying vec2 vTextureCoord;")
        LINE("uniform lowp sampler2D uTexture;")
        LINE("void main() {")
        LINE("lowp vec4 color = texture2D(uTexture, vTextureCoord);")
        LINE("gl_FragColor = vec4((1.0 - color.rgb), color.w);")
        LINE("}");
#undef LINE

ogles_filter_create(invert)
(void)
{
#define STR(s) #s
    struct ogles_invert_filter *filter = malloc(sizeof(struct ogles_invert_filter));
    filter->base.type = FILTER_TYPE_INVERT;
    filter->base.init = ogles_invert_filter_init;
    filter->base.resize = ogles_invert_filter_resize;
    filter->base.draw = ogles_invert_filter_draw;
    filter->base.release = ogles_invert_filter_release;
    filter->base.safe_release = ogles_invert_filter_safe_release;
    filter->base.primitive = NULL;
    filter->base.fbo = NULL;
    filter->base.program = 0;
    filter->base.vertex_shader = 0;
    filter->base.fragment_shader = 0;
    filter->uniforms.uTexture.name = STR(uTexture);
    filter->uniforms.uTexture.location = -1;
    filter->attributes.aPosition.location = -1;
    filter->attributes.aPosition.name = STR(aPosition);
    filter->attributes.aTextureCoord.location = -1;
    filter->attributes.aTextureCoord.name = STR(aTextureCoord);
#undef STR
    return filter;
}

ogles_filter_init(invert)
(struct ogles_filter_base *filter, primitive_type primitive_type, bool create_fbo)
{
    ogles_invert_filter_safe_release(filter);

    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_source);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->primitive = create_primitive(primitive_type);
    filter->fbo = create_fbo ? malloc(sizeof(struct ogles_fbo)) : NULL;
    ogles_invert_filter_register_handle((struct ogles_invert_filter*)filter);
}

ogles_filter_resize(invert)
(struct ogles_filter_base *filter, GLint width, GLint height)
{
    ogles_fbo_resize(filter->fbo, width, height);
}

ogles_filter_safe_release(invert)
(struct ogles_filter_base *filter)
{
    filter->program = 0;
    filter->vertex_shader = 0;
    filter->fragment_shader = 0;
    safe_free_primitive(filter->primitive);
    ogles_fbo_safe_release(filter->fbo);
}

ogles_filter_release(invert)
(struct ogles_filter_base *filter)
{
    glDeleteProgram(filter->program);
    glDeleteShader(filter->vertex_shader);
    glDeleteShader(filter->fragment_shader);

    ogles_invert_filter_safe_release(filter);
}

ogles_filter_draw(invert)
(struct ogles_filter_base *filter, GLuint *texture)
{
    struct ogles_invert_filter *invert_filter = (struct ogles_invert_filter*)filter;
    ogles_invert_filter_use_program(invert_filter);
    ogles_invert_filter_pre_draw(invert_filter);

    glBindBuffer(GL_ARRAY_BUFFER, invert_filter->base.primitive->vbo_vertices);
    glEnableVertexAttribArray((GLuint)invert_filter->attributes.aPosition.location);
    glVertexAttribPointer((GLuint)invert_filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE_3, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, invert_filter->base.primitive->vbo_uvs);
    glEnableVertexAttribArray((GLuint)invert_filter->attributes.aTextureCoord.location);
    glVertexAttribPointer((GLuint)invert_filter->attributes.aTextureCoord.location, VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glUniform1i(invert_filter->uniforms.uTexture.location, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, invert_filter->base.primitive->vbo_indices);
    glDrawElements(GL_TRIANGLES, invert_filter->base.primitive->elements_count, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray((GLuint)invert_filter->attributes.aPosition.location);
    glDisableVertexAttribArray((GLuint)invert_filter->attributes.aTextureCoord.location);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ogles_invert_filter_post_draw(invert_filter, texture);
}

ogles_filter_pre_draw(invert)
(struct ogles_invert_filter *filter)
{
    ogles_fbo_enable(filter->base.fbo);
    glClear(GL_COLOR_BUFFER_BIT);

    if (filter->base.primitive != NULL)
    {
        (*filter->base.primitive->update)(filter->base.primitive);
    }
}

ogles_filter_post_draw(invert)
(struct ogles_invert_filter *filter, GLuint *texture)
{
    *texture = filter->base.fbo->rendertexture;
}

ogles_filter_use_program(invert)
(struct ogles_invert_filter *filter)
{
    glUseProgram(filter->base.program);
}

ogles_filter_register_handle(invert)
(struct ogles_invert_filter *filter)
{
    // Uniforms
    filter->uniforms.uTexture.location = glGetUniformLocation(filter->base.program, filter->uniforms.uTexture.name);
    if (filter->uniforms.uTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uTexture.name);}
    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->base.program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aTextureCoord.location = glGetAttribLocation(filter->base.program, filter->attributes.aTextureCoord.name);
    if (filter->attributes.aTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aTextureCoord.name); }
}