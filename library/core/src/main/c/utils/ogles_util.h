//
// Created by showtime on 9/5/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLES_UTIL_H
#define EXOPLAYER_GRAPHICS_OGLES_UTIL_H

#include "../graphics/ogles.h"
#include "log_util.h"

void setupSampler(GLenum target, GLint mag, GLint min);

GLuint createProgramUTFChars(const char* vertexSource, const char * fragmentSource);

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

GLuint loadShader(GLenum shaderType, const char* shaderSource);

GLuint createBuffer(GLfloat *data, GLsizei size);

void updateBuffer(GLuint buffer, GLfloat *data, GLsizei size);

#endif //EXOPLAYER_GRAPHICS_OGLES_UTIL_H
