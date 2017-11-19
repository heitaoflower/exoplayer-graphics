//
// Created by showtime on 11/10/2017.
//

#include "ogles_gray_filter.h"
#include "../utils/ogles_util.h"

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
                LINE("uniform lowp sampler2D sTexture;")
                LINE("const highp vec3 weight = vec3(0.2125, 0.7154, 0.0721);")
                LINE("void main() {")
                LINE("float luminance = dot(texture2D(sTexture, vTextureCoord).rgb, weight);")
                LINE("gl_FragColor = vec4(vec3(luminance), 1.0);")
                LINE("}");
#undef LINE

ogles_filter_create(gray)
(void)
{
#define STR(s) #s
    struct ogles_gray_filter *filter = malloc(sizeof(struct ogles_gray_filter));
    filter->base.type = FILTER_TYPE_GRAY;
    filter->base.init = ogles_gray_filter_init;
    filter->base.resize = ogles_gray_filter_resize;
    filter->base.draw = ogles_gray_filter_draw;
    filter->base.release = ogles_gray_filter_release;
    filter->base.safe_release = ogles_gray_filter_safe_release;
    filter->base.primitive = NULL;
    filter->base.fbo = NULL;
    filter->base.program = 0;
    filter->base.vertex_shader = 0;
    filter->base.fragment_shader = 0;
    filter->uniforms.sTexture.name = STR(sTexture);
    filter->uniforms.sTexture.location = -1;
    filter->attributes.aPosition.location = -1;
    filter->attributes.aPosition.name = STR(aPosition);
    filter->attributes.aTextureCoord.location = -1;
    filter->attributes.aTextureCoord.name = STR(aTextureCoord);
#undef STR
    return filter;
}

ogles_filter_init(gray)
(struct ogles_filter_base *filter, primitive_type primitive_type, bool create_fbo)
{
    ogles_gray_filter_safe_release(filter);

    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_source);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->primitive = create_primitive(primitive_type);
    filter->fbo = create_fbo ? malloc(sizeof(struct ogles_fbo)) : NULL;
    ogles_gray_filter_register_handle((struct ogles_gray_filter*)filter);
}

ogles_filter_resize(gray)
(struct ogles_filter_base *filter, GLint width, GLint height)
{
    ogles_fbo_resize(filter->fbo, width, height);
}

ogles_filter_safe_release(gray)
(struct ogles_filter_base *filter)
{
    filter->program = 0;
    filter->vertex_shader = 0;
    filter->fragment_shader = 0;
    safe_free_primitive(filter->primitive);
    ogles_fbo_safe_release(filter->fbo);
}

ogles_filter_release(gray)
(struct ogles_filter_base *filter)
{
    glDeleteProgram(filter->program);
    glDeleteShader(filter->vertex_shader);
    glDeleteShader(filter->fragment_shader);

    ogles_gray_filter_safe_release(filter);
}

ogles_filter_draw(gray)
(struct ogles_filter_base *filter, GLuint *texture)
{
    struct ogles_gray_filter *gray_filter = (struct ogles_gray_filter*)filter;
    ogles_gray_filter_use_program(gray_filter);
    ogles_gray_filter_pre_draw(gray_filter);

    glBindBuffer(GL_ARRAY_BUFFER, gray_filter->base.primitive->vbo_vertices);
    glEnableVertexAttribArray((GLuint)gray_filter->attributes.aPosition.location);
    glVertexAttribPointer((GLuint)gray_filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, gray_filter->base.primitive->vbo_uvs);
    glEnableVertexAttribArray((GLuint)gray_filter->attributes.aTextureCoord.location);
    glVertexAttribPointer((GLuint)gray_filter->attributes.aTextureCoord.location, VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, *texture);
    glUniform1i(gray_filter->uniforms.sTexture.location, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gray_filter->base.primitive->vbo_indices);
    glDrawElements(GL_TRIANGLES, gray_filter->base.primitive->elements_count, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray((GLuint)gray_filter->attributes.aPosition.location);
    glDisableVertexAttribArray((GLuint)gray_filter->attributes.aTextureCoord.location);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    *texture = filter->fbo->rendertexture;
    ogles_gray_filter_post_draw(gray_filter);
}

ogles_filter_pre_draw(gray)
(struct ogles_gray_filter *filter)
{
    ogles_fbo_enable(filter->base.fbo);
    glClear(GL_COLOR_BUFFER_BIT);

    if (filter->base.primitive != NULL)
    {
        (*filter->base.primitive->update)(filter->base.primitive);
    }
}

ogles_filter_post_draw(gray)
(struct ogles_gray_filter *filter)
{

}

ogles_filter_use_program(gray)
(struct ogles_gray_filter *filter)
{
    glUseProgram(filter->base.program);
}

ogles_filter_register_handle(gray)
(struct ogles_gray_filter *filter)
{
    // Uniforms
    filter->uniforms.sTexture.location = glGetUniformLocation(filter->base.program, filter->uniforms.sTexture.name);
    if (filter->uniforms.sTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.sTexture.name);}

    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->base.program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aTextureCoord.location = glGetAttribLocation(filter->base.program, filter->attributes.aTextureCoord.name);
    if (filter->attributes.aTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aTextureCoord.name); }
}