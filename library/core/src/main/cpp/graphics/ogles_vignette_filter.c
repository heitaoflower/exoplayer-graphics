//
// Created by showtime on 11/10/2017.
//
#include "ogles_vignette_filter.h"
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
                LINE("uniform lowp vec2 uVignetteCenter;")
                LINE("uniform lowp vec3 uVignetteColor;")
                LINE("uniform highp float uVignetteStart;")
                LINE("uniform highp float uVignetteEnd;")
                LINE("void main() {")
                LINE("lowp vec3 rgb = texture2D(sTexture, vTextureCoord).rgb;")
                LINE("lowp float d = distance(vTextureCoord, vec2(uVignetteCenter.x, uVignetteCenter.y));")
                LINE("lowp float percent = smoothstep(uVignetteStart, uVignetteEnd, d);")
                LINE("gl_FragColor = vec4(mix(rgb.x, uVignetteColor.x, percent), mix(rgb.y, uVignetteColor.y, percent), mix(rgb.z, uVignetteColor.z, percent), 1.0);")
                LINE("}");
#undef LINE

ogles_filter_create(vignette)
(void)
{
#define STR(s) #s
    struct ogles_vignette_filter *filter = malloc(sizeof(struct ogles_vignette_filter));
    filter->base.type = FILTER_TYPE_VIGNETTE;
    filter->base.init = ogles_vignette_filter_init;
    filter->base.resize = ogles_vignette_filter_resize;
    filter->base.draw = ogles_vignette_filter_draw;
    filter->base.release = ogles_vignette_filter_release;
    filter->base.safe_release = ogles_vignette_filter_safe_release;
    filter->base.primitive = NULL;
    filter->base.program = 0;
    filter->base.vertex_shader = 0;
    filter->base.fragment_shader = 0;
    filter->uniforms.sTexture.name = STR(sTexture);
    filter->uniforms.sTexture.location = -1;
    filter->uniforms.uVignetteCenter.name = STR(uVignetteCenter);
    filter->uniforms.uVignetteCenter.location = -1;
    filter->uniforms.uVignetteColor.name = STR(uVignetteColor);
    filter->uniforms.uVignetteColor.location = -1;
    filter->uniforms.uVignetteStart.name = STR(uVignetteStart);
    filter->uniforms.uVignetteStart.location = -1;
    filter->uniforms.uVignetteEnd.name = STR(uVignetteEnd);
    filter->uniforms.uVignetteEnd.location = -1;
    filter->attributes.aPosition.name = STR(aPosition);
    filter->attributes.aPosition.location = -1;
    filter->attributes.aTextureCoord.name = STR(aTextureCoord);
    filter->attributes.aTextureCoord.location = -1;
    filter->vignette_center_x = 0.5f;
    filter->vignette_center_y = 0.5f;
    filter->vignette_color[0] = 0.0f;
    filter->vignette_color[1] = 0.0f;
    filter->vignette_color[2] = 0.0f;
    filter->vignette_start = 0.2f;
    filter->vignette_end = 0.85f;
#undef STR
    return filter;
}

ogles_filter_init(vignette)
(struct ogles_filter_base *filter, struct primitive *primitive)
{
    ogles_vignette_filter_safe_release(filter);

    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader_source);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader_source);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->primitive = primitive;

    ogles_vignette_filter_register_handle((struct ogles_vignette_filter*)filter);
}

ogles_filter_resize(vignette)
(struct ogles_filter_base *filter, GLint width, GLint height)
{

}

ogles_filter_safe_release(vignette)
(struct ogles_filter_base *filter)
{
    filter->program = 0;
    filter->vertex_shader = 0;
    filter->fragment_shader = 0;
    safe_free_primitive(filter->primitive);
    filter->primitive = NULL;
}

ogles_filter_release(vignette)
(struct ogles_filter_base *filter)
{
    glDeleteProgram(filter->program);
    glDeleteShader(filter->vertex_shader);
    glDeleteShader(filter->fragment_shader);

    ogles_vignette_filter_safe_release(filter);
}

ogles_filter_draw(vignette)
(struct ogles_filter_base *filter, GLuint texture)
{
    struct ogles_vignette_filter *vignette_filter = (struct ogles_vignette_filter*)filter;
    ogles_vignette_filter_use_program(vignette_filter);
    ogles_vignette_filter_pre_draw(vignette_filter);

    glBindBuffer(GL_ARRAY_BUFFER, vignette_filter->base.primitive->vbo_vertices);
    glEnableVertexAttribArray((GLuint)vignette_filter->attributes.aPosition.location);
    glVertexAttribPointer((GLuint)vignette_filter->attributes.aPosition.location, VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, vignette_filter->base.primitive->vbo_uvs);
    glEnableVertexAttribArray((GLuint)vignette_filter->attributes.aTextureCoord.location);
    glVertexAttribPointer((GLuint)vignette_filter->attributes.aTextureCoord.location, VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, 0, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(vignette_filter->uniforms.sTexture.location, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vignette_filter->base.primitive->vbo_indices);
    glDrawElements(GL_TRIANGLES, vignette_filter->base.primitive->elements_count, GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray((GLuint)vignette_filter->attributes.aPosition.location);
    glDisableVertexAttribArray((GLuint)vignette_filter->attributes.aTextureCoord.location);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    ogles_vignette_filter_post_draw(vignette_filter);
}

ogles_filter_pre_draw(vignette)
(struct ogles_vignette_filter *filter)
{
    glUniform2f(filter->uniforms.uVignetteCenter.location, filter->vignette_center_x, filter->vignette_center_y);
    glUniform3fv(filter->uniforms.uVignetteColor.location, 1, filter->vignette_color);
    glUniform1f(filter->uniforms.uVignetteStart.location, filter->vignette_start);
    glUniform1f(filter->uniforms.uVignetteEnd.location, filter->vignette_end);
}

ogles_filter_post_draw(vignette)
(struct ogles_vignette_filter *filter)
{

}

ogles_filter_use_program(vignette)
(struct ogles_vignette_filter *filter)
{
    glUseProgram(filter->base.program);
}

ogles_filter_register_handle(vignette)
(struct ogles_vignette_filter *filter)
{
    // Uniforms
    filter->uniforms.sTexture.location = glGetUniformLocation(filter->base.program, filter->uniforms.sTexture.name);
    if (filter->uniforms.sTexture.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.sTexture.name);}
    filter->uniforms.uVignetteCenter.location = glGetUniformLocation(filter->base.program, filter->uniforms.uVignetteCenter.name);
    if (filter->uniforms.uVignetteCenter.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uVignetteCenter.name);}
    filter->uniforms.uVignetteColor.location = glGetUniformLocation(filter->base.program, filter->uniforms.uVignetteColor.name);
    if (filter->uniforms.uVignetteColor.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uVignetteColor.name);}
    filter->uniforms.uVignetteStart.location = glGetUniformLocation(filter->base.program, filter->uniforms.uVignetteStart.name);
    if (filter->uniforms.uVignetteStart.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uVignetteStart.name);}
    filter->uniforms.uVignetteEnd.location = glGetUniformLocation(filter->base.program, filter->uniforms.uVignetteEnd.name);
    if (filter->uniforms.uVignetteEnd.location == -1) { LOGE("could not get uniform location for %s", filter->uniforms.uVignetteEnd.name);}

    // Attributes
    filter->attributes.aPosition.location = glGetAttribLocation(filter->base.program, filter->attributes.aPosition.name);
    if (filter->attributes.aPosition.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aPosition.name); }
    filter->attributes.aTextureCoord.location = glGetAttribLocation(filter->base.program, filter->attributes.aTextureCoord.name);
    if (filter->attributes.aTextureCoord.location == -1) { LOGE("could not get attribute location for %s", filter->attributes.aTextureCoord.name); }
}