//
// Created by showtime on 9/5/2017.
//

#ifndef EXOPLAYER_GRAPHICS_OGLESUTIL_H
#define EXOPLAYER_GRAPHICS_OGLESUTIL_H

#include "../graphics/gl.h"
#include "logUtil.h"
#include <stdlib.h>

void setupSampler(GLenum target, GLfloat mag, GLfloat min);

GLuint createProgramUTFChars(const char* vertexSource, const char * fragmentSource);

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

GLuint loadShader(GLenum shaderType, const char* shaderSource);

GLuint createBuffer(GLfloat *data);

void updateBuffer(GLuint buffer, GLfloat *data);

#endif //EXOPLAYER_GRAPHICS_OGLESUTIL_H
