//
// Created by showtime on 9/3/2017.
//

#ifndef EXOGFX_GRAPHICS_OGLES_H
#define EXOGFX_GRAPHICS_OGLES_H

#include <GLES2/gl2.h>

#define GL_FN(fn) gl_##fn

#define GL_TEXTURE_EXTERNAL_OES 0x8D65

#define glCheckFramebufferStatus GL_FN(glCheckFramebufferStatus)
#define glClear GL_FN(glClear)
#define glClearColor GL_FN(glClearColor)
#define glEnable GL_FN(glEnable)
#define glViewport GL_FN(glViewport)
#define glActiveTexture GL_FN(glActiveTexture)
#define glAttachShader GL_FN(glAttachShader)
#define glBindBuffer GL_FN(glBindBuffer)
#define glBindFramebuffer GL_FN(glBindFramebuffer)
#define glBindRenderbuffer GL_FN(glBindRenderbuffer)
#define glBindVertexArray GL_FN(glBindVertexArray)
#define glBufferData GL_FN(glBufferData)
#define glCompileShader GL_FN(glCompileShader)
#define glCreateProgram GL_FN(glCreateProgram)
#define glCreateShader GL_FN(glCreateShader)
#define glCullFace GL_FN(glCullFace)
#define glDeleteProgram GL_FN(glDeleteProgram)
#define glDeleteShader GL_FN(glDeleteShader)
#define glDeleteBuffers GL_FN(glDeleteBuffers)
#define glDeleteFramebuffers GL_FN(glDeleteFramebuffers)
#define glDeleteRenderbuffers GL_FN(glDeleteRenderbuffers)
#define glDeleteTextures GL_FN(glDeleteTextures)
#define glDepthFunc GL_FN(glDepthFunc)
#define glDisable GL_FN(glDisable)
#define glDisableVertexAttribArray GL_FN(glDisableVertexAttribArray)
#define glDrawArrays GL_FN(glDrawArrays)
#define glDrawArraysInstanced GL_FN(glDrawArraysInstanced)
#define glDrawElements GL_FN(glDrawElements)
#define glEnableVertexAttribArray GL_FN(glEnableVertexAttribArray)
#define glFrontFace GL_FN(glFrontFace)
#define glFramebufferRenderbuffer GL_FN(glFramebufferRenderbuffer)
#define glFramebufferTexture2D GL_FN(glFramebufferTexture2D)
#define glGenFramebuffers GL_FN(glGenFramebuffers)
#define glGenRenderbuffers GL_FN(glGenRenderbuffers)
#define glGenBuffers GL_FN(glGenBuffers)
#define glGenTextures GL_FN(glGenTextures)
#define glBindTexture GL_FN(glBindTexture)
#define glGenVertexArrays GL_FN(glGenVertexArrays)
#define glGetAttribLocation GL_FN(glGetAttribLocation)
#define glGetError GL_FN(glGetError)
#define glGetProgramInfoLog GL_FN(glGetProgramInfoLog)
#define glGetIntegerv GL_FN(glGetIntegerv)
#define glGetProgramiv GL_FN(glGetProgramiv)
#define glGetShaderInfoLog  GL_FN(glGetShaderInfoLog)
#define glGetShaderiv GL_FN(glGetShaderiv)
#define glGetString GL_FN(glGetString)
#define glGetUniformLocation GL_FN(glGetUniformLocation)
#define glLinkProgram GL_FN(glLinkProgram)
#define glRenderbufferStorage GL_FN(glRenderbufferStorage)
#define glShaderSource GL_FN(glShaderSource)
#define glTexImage2D GL_FN(glTexImage2D)
#define glTexParameterf GL_FN(glTexParameterf)
#define glTexParameterfv GL_FN(glTexParameterfv)
#define glTexParameteri GL_FN(glTexParameteri)
#define glTexParameteriv GL_FN(glTexParameteriv)
#define glUniform1f GL_FN(glUniform1f)
#define glUniform1i GL_FN(glUniform1i)
#define glUniform2f GL_FN(glUniform2f)
#define glUniform2fv GL_FN(glUniform2fv)
#define glUniform3fv GL_FN(glUniform3fv)
#define glUniform4fv GL_FN(glUniform4fv)
#define glUniformMatrix4fv GL_FN(glUniformMatrix4fv)
#define glUseProgram GL_FN(glUseProgram)
#define glVertexAttribPointer GL_FN(glVertexAttribPointer)

#define FNSYM(fn, ret, args)                          \
        typedef ret (*PFN_##fn)args;        \
        extern PFN_##fn fn;
#include "ogles_func.h"
#undef FNSYM

#endif //EXOGFX_GRAPHICS_OGLES_H

