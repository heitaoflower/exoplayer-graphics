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

OGLES_FILTER_INIT(presentation)
(struct ogles_presentation_filter *filter)
{
    ogles_presentation_filter_release(filter);

    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->vertex_buffer = createBuffer(VERTICES_DATA, sizeof(VERTICES_DATA));

    map_init(&filter->handle_map);
}

OGLES_FILTER_RESIZE(presentation)
(struct ogles_presentation_filter *filter, GLint width, GLint height)
{

}

OGLES_FILTER_DRAW(presentation)
(struct ogles_presentation_filter *filter, GLuint texture, struct ogles_fbo *fbo)
{
    ogles_presentation_filter_use_program(filter);

    glBindBuffer(GL_ARRAY_BUFFER, filter->vertex_buffer);
    glEnableVertexAttribArray((GLuint)ogles_presentation_filter_get_handle(filter, "aPosition"));
    glVertexAttribPointer((GLuint)ogles_presentation_filter_get_handle(filter, "aPosition"), VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, VERTICES_DATA_STRIDE_BYTES, VERTICES_DATA + VERTICES_DATA_POSITION_OFFSET);
    glEnableVertexAttribArray((GLuint)ogles_presentation_filter_get_handle(filter, "aTextureCoord"));
    glVertexAttribPointer((GLuint)ogles_presentation_filter_get_handle(filter, "aTextureCoord"), VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, VERTICES_DATA_STRIDE_BYTES, VERTICES_DATA + VERTICES_DATA_UV_OFFSET);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(ogles_presentation_filter_get_handle(filter, "sTexture"), 0);

    ogles_presentation_filter_draw_cb(filter);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray((GLuint)ogles_presentation_filter_get_handle(filter, "aPosition"));
    glDisableVertexAttribArray((GLuint)ogles_presentation_filter_get_handle(filter, "aTextureCoord"));
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_ARRAY_BUFFER, 0);
}

OGLES_FILTER_DRAW_CB(presentation)(struct ogles_presentation_filter *filter)
{

}
OGLES_FILTER_RELEASE(presentation)
(struct ogles_presentation_filter *filter)
{
    glDeleteProgram(filter->program);
    filter->program = 0;

    glDeleteShader(filter->vertex_shader);
    filter->vertex_shader = 0;

    glDeleteShader(filter->fragment_shader);
    filter->fragment_shader = 0;

    glDeleteBuffers(1, &filter->vertex_buffer);
    filter->vertex_buffer = 0;

    map_deinit(&filter->handle_map);
}

OGLES_FILTER_USE_PROGRAM(presentation)(struct ogles_presentation_filter *filter)
{
    glUseProgram(filter->program);
}

OGLES_FILTER_GET_VERTEX_BUFFER(presentation)(struct ogles_presentation_filter *filter)
{
    return filter->vertex_buffer;
}

OGLES_FILTER_GET_HANDLE(presentation)(struct ogles_presentation_filter *filter, const GLchar *name)
{
    GLuint* value = (GLuint*)map_get(&filter->handle_map, name);

    if (value != NULL)
    {
        return *value;
    }

    GLint location = glGetAttribLocation(filter->program, name);

    if (location == -1)
    {
        location = glGetUniformLocation(filter->program, name);
    }

    if (location == -1)
    {
        LOGE("could not get attrib or uniform location for %s", name);

        return -1;
    }

    map_set(&filter->handle_map, name, location);

    return location;
}