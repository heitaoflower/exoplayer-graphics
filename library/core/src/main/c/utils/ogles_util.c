//
// Created by showtime on 9/5/2017.
//
#include "ogles_util.h"
#include <stdlib.h>

void initSampler(GLenum target, GLint mag, GLint min)
{
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();

    if (program)
    {
        glAttachShader(program , vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;

        glGetProgramiv(program , GL_LINK_STATUS, &linkStatus);

        if( linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;

            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);

            if (bufLength)
            {
                char* buf = (char*) malloc((size_t)bufLength);

                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }

    return program;
}

GLuint createProgramUTFChars(const char *vertexSource, const char *fragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
    if (!vertexShader)
    {
        return 0;
    }

    GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, fragmentSource);
    if (!fragmentShader)
    {
        return 0;
    }

    return createProgram(vertexShader, fragmentShader);
}

GLuint loadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);

    if (shader)
    {
        glShaderSource(shader, 1, &shaderSource, NULL);
        glCompileShader(shader);

        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

            if (infoLen)
            {
                char * buf = (char*) malloc((size_t)infoLen);

                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

GLuint createBuffer(GLenum target, const void *data, GLsizei size)
{
    GLuint buffers[1];

    glGenBuffers(1, buffers);
    updateBuffer(target, buffers[0], data, size);

    return buffers[0];
}

void updateBuffer(GLenum target, GLuint buffer, const void *data, GLsizei size)
{
    glBindBuffer(target, buffer);
    glBufferData(target, size, data, GL_STATIC_DRAW);
    glBindBuffer(target, 0);
}

GLboolean checkGLError(const char* message)
{
    GLenum lastError = glGetError();
    if (lastError != GL_NO_ERROR)
    {
        LOGE("%s failed (%d).\\n", message, lastError);

        return false;
    }

    return true;
}