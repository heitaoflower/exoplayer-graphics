//
// Created by showtime on 9/10/2017.
//
#include "ogles_filter.h"
#include "../utils/ogles_util.h"

const char* const DEFAULT_UNIFORM_SAMPLER = "sTexture";

static const char vertex_shader[] =
        "attribute vec4 aPosition;\n"
        "attribute vec4 aTextureCoord;\n"
        "varying highp vec2 vTextureCoord;\n"
        "void main() {\n"
        "gl_Position = aPosition;\n"
        "vTextureCoord = aTextureCoord.xy;\n"
        "}\n";

static const char fragment_shader[] =
        "precision mediump float;\n"
        "varying highp vec2 vTextureCoord;\n"
        "uniform lowp sampler2D sTexture;\n"
        "void main() {\n"
        "gl_FragColor = texture2D(sTexture, vTextureCoord);\n"
        "}\n";

static const GLfloat VERTICES_DATA[] =
        {
            -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  -1.0f, 0.0f, 1.0f, 0.0f };

#define FLOAT_SIZE_BYTES 4
#define VERTICES_DATA_POSITION_SIZE 3
#define VERTICES_DATA_UV_SIZE 2
#define VERTICES_DATA_STRIDE_BYTES (VERTICES_DATA_POSITION_SIZE + VERTICES_DATA_UV_SIZE) * FLOAT_SIZE_BYTES
#define VERTICES_DATA_POSITION_OFFSET 0 * FLOAT_SIZE_BYTES
#define VERTICES_DATA_UV_OFFSET VERTICES_DATA_POSITION_OFFSET + VERTICES_DATA_POSITION_SIZE * FLOAT_SIZE_BYTES

void ogles_filter_init(struct ogles_filter *filter)
{
    ogles_filter_release(filter);

    filter->vertex_shader = loadShader(GL_VERTEX_SHADER, vertex_shader);
    filter->fragment_shader = loadShader(GL_FRAGMENT_SHADER, fragment_shader);
    filter->program = createProgram(filter->vertex_shader, filter->fragment_shader);
    filter->vertex_buffer = createBuffer(VERTICES_DATA, sizeof(VERTICES_DATA));
}

void ogles_filter_release(struct ogles_filter *filter)
{
    glDeleteProgram(filter->program);
    filter->program = 0;

    glDeleteShader(filter->vertex_shader);
    filter->vertex_shader = 0;

    glDeleteShader(filter->fragment_shader);
    filter->fragment_shader = 0;

    glDeleteBuffers(1, &filter->vertex_buffer);
    filter->vertex_buffer = 0;
}