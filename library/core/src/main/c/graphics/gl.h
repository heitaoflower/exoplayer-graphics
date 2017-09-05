//
// Created by showtime on 9/3/2017.
//

#ifndef EXOPLAYER_GRAPHICS_GL_H
#define EXOPLAYER_GRAPHICS_GL_H

#include <GLES2/gl2.h>

#define GL_FN(fn) gl_##fn

#define glClear GL_FN(glClear)
#define glClearColor GL_FN(glClearColor)
#define glEnable GL_FN(glEnable)
#define glViewport GL_FN(glViewport)
#define glAttachShader GL_FN(glAttachShader)
#define glBindBuffer GL_FN(glBindBuffer)
#define glBindVertexArray GL_FN(glBindVertexArray)
#define glBufferData GL_FN(glBufferData)
#define glCompileShader GL_FN(glCompileShader)
#define glCreateProgram GL_FN(glCreateProgram)
#define glCreateShader GL_FN(glCreateShader)
#define glCullFace GL_FN(glCullFace)
#define glDeleteProgram GL_FN(glDeleteProgram)
#define glDeleteShader GL_FN(glDeleteShader)
#define glDepthFunc GL_FN(glDepthFunc)
#define glDrawArrays GL_FN(glDrawArrays)
#define glDrawArraysInstanced GL_FN(glDrawArraysInstanced)
#define glDrawElements GL_FN(glDrawElements)
#define glEnableVertexAttribArray GL_FN(glEnableVertexAttribArray)
#define glFrontFace GL_FN(glFrontFace)
#define glGenBuffers GL_FN(glGenBuffers)
#define glGenTextures GL_FN(glGenTextures)
#define glBindTexture GL_FN(glBindTexture)
#define glGenVertexArrays GL_FN(glGenVertexArrays)
#define glGetAttribLocation GL_FN(glGetAttribLocation)
#define glGetError GL_FN(glGetError)
#define glGetProgramInfoLog GL_FN(glGetProgramInfoLog)
#define glGetProgramiv GL_FN(glGetProgramiv)
#define glGetShaderInfoLog  GL_FN(glGetShaderInfoLog)
#define glGetShaderiv GL_FN(glGetShaderiv)
#define glGetString GL_FN(glGetString)
#define glGetUniformLocation GL_FN(glGetUniformLocation)
#define glLinkProgram GL_FN(glLinkProgram)
#define glShaderSource GL_FN(glShaderSource)
#define glTexParameterf GL_FN(glTexParameterf)
#define glTexParameterfv GL_FN(glTexParameterfv)
#define glTexParameteri GL_FN(glTexParameteri)
#define glTexParameteriv GL_FN(glTexParameteriv)
#define glUniform1f GL_FN(glUniform1f)
#define glUniform1i GL_FN(glUniform1i)
#define glUniform3fv GL_FN(glUniform3fv)
#define glUniform4fv GL_FN(glUniform4fv)
#define glUniformMatrix4fv GL_FN(glUniformMatrix4fv)
#define glUseProgram GL_FN(glUseProgram)
#define glVertexAttribPointer GL_FN(glVertexAttribPointer)

#define FNSYM(fn, ret, args)                          \
        typedef ret (*PFN_##fn)args;        \
        extern PFN_##fn fn;
#include "gl_func.h"
#undef FNSYM

#endif //EXOPLAYER_GRAPHICS_GL_H

