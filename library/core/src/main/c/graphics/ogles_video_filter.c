//
// Created by showtime on 9/10/2017.
//
#include "ogles_video_filter.h"
#include "../utils/ogles_util.h"

#define L(s) s "\n"
static const char *vertex_shader =
        L("uniform mat4 uMVPMatrix;")
        L("uniform mat4 uSTMatrix;")
        L("uniform float uCRatio;")

        L("attribute vec4 aPosition;")
        L("attribute vec4 aTextureCoord;")
        L("varying highp vec2 vTextureCoord;")

        L("void main() {")
        L("vec4 scaledPos = aPosition;")
        L("scaledPos.x = scaledPos.x * uCRatio;")
        L("gl_Position = uMVPMatrix * scaledPos;")
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

OGLES_FILTER_INIT(video)
(struct ogles_video_filter *filter)
{
    ogles_video_filter_release(filter);

    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->vertex_buffer = createBuffer(VERTICES_DATA, sizeof(VERTICES_DATA));
    filter->target = 0x8D65;

    map_init(&filter->handle_map);
}

OGLES_FILTER_RELEASE(video)
(struct ogles_video_filter *filter)
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

OGLES_FILTER_RESIZE(video)
(struct ogles_video_filter *filter, GLint width, GLint height)
{

}

OGLES_FILTER_DRAW(video)
(struct ogles_video_filter *filter, GLuint texture, const float mvp_matrix[], const float st_matrix[], const float aspect_ratio)
{
    ogles_video_filter_use_program(filter);

    glUniformMatrix4fv(ogles_video_filter_get_handle(filter, "uMVPMatrix"), 1, GL_FALSE, mvp_matrix);
    glUniformMatrix4fv(ogles_video_filter_get_handle(filter, "uSTMatrix"), 1, GL_FALSE, st_matrix);
    glUniform1f(ogles_video_filter_get_handle(filter, "uCRatio"), aspect_ratio);

    glBindBuffer(GL_ARRAY_BUFFER, ogles_video_filter_get_vertex_buffer(filter));
    glEnableVertexAttribArray((GLuint)ogles_video_filter_get_handle(filter, "aPosition"));

    glVertexAttribPointer((GLuint)ogles_video_filter_get_handle(filter, "aPosition"), VERTICES_DATA_POSITION_SIZE, GL_FLOAT, GL_FALSE, VERTICES_DATA_STRIDE_BYTES, VERTICES_DATA_POSITION_OFFSET);
    glEnableVertexAttribArray((GLuint)ogles_video_filter_get_handle(filter, "aTextureCoord"));
    glVertexAttribPointer((GLuint)ogles_video_filter_get_handle(filter, "aTextureCoord"), VERTICES_DATA_UV_SIZE, GL_FLOAT, GL_FALSE, VERTICES_DATA_STRIDE_BYTES, VERTICES_DATA_UV_OFFSET);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(filter->target, texture);
    glUniform1i(ogles_video_filter_get_handle(filter, "sTexture"), 0);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDisableVertexAttribArray((GLuint)ogles_video_filter_get_handle(filter, "aPosition"));
    glDisableVertexAttribArray((GLuint)ogles_video_filter_get_handle(filter, "aTextureCoord"));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

OGLES_FILTER_DRAW_CB(video)
(struct ogles_video_filter *filter)
{

}

OGLES_FILTER_USE_PROGRAM(video)
(struct ogles_video_filter *filter)
{
    glUseProgram(filter->program);
}

OGLES_FILTER_GET_VERTEX_BUFFER(video)
(struct ogles_video_filter *filter)
{
    return filter->vertex_buffer;
}

OGLES_FILTER_GET_HANDLE(video)
(struct ogles_video_filter *filter, const GLchar *name)
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
