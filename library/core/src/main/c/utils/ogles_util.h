//
// Created by showtime on 9/5/2017.
//

#ifndef EXOGFX_OGLES_UTIL_H
#define EXOGFX_OGLES_UTIL_H

#include "../graphics/ogles.h"
#include "log_util.h"

#include <stdbool.h>

void initSampler(GLenum target, GLint mag, GLint min);

GLuint createProgramUTFChars(const char* vertexSource, const char * fragmentSource);

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

GLuint loadShader(GLenum shaderType, const char* shaderSource);

GLuint createBuffer(const GLfloat *data, GLsizei size);

void updateBuffer(GLuint buffer,const GLfloat *data, GLsizei size);

GLboolean checkGLError(const char* message);

#endif //EXOGFX_OGLES_UTIL_H
