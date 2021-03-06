FNSYM(glCheckFramebufferStatus, GLenum , (GLenum))
FNSYM(glClear, void, (GLbitfield))
FNSYM(glClearColor, void, (GLfloat, GLfloat, GLfloat, GLfloat))
FNSYM(glEnable, void, (GLenum))
FNSYM(glFinish, void, (void))
FNSYM(glFlush, void, (void))
FNSYM(glViewport, void, (GLint, GLint, GLsizei, GLsizei))
FNSYM(glScissor, void, (GLint, GLint, GLsizei, GLsizei))
FNSYM(glActiveTexture, void, (GLenum))
FNSYM(glAttachShader, void, (GLuint, GLuint))
FNSYM(glBindBuffer, void, (GLenum, GLuint))
FNSYM(glBindFramebuffer, void, (GLenum, GLuint))
FNSYM(glBindRenderbuffer, void, (GLenum, GLuint))
FNSYM(glBindVertexArray, void, (GLuint))
FNSYM(glBufferData, void, (GLenum, GLsizeiptr, const void*, GLenum))
FNSYM(glCompileShader, void, (GLuint))
FNSYM(glCreateProgram, GLuint, (void))
FNSYM(glCreateShader, GLuint, (GLenum))
FNSYM(glCullFace, void, (GLenum))
FNSYM(glDeleteProgram, void, (GLuint))
FNSYM(glDeleteShader, void, (GLuint))
FNSYM(glDeleteBuffers, void, (GLsizei, const GLuint *))
FNSYM(glDeleteFramebuffers, void, (GLsizei, const GLuint *))
FNSYM(glDeleteRenderbuffers, void, (GLsizei, const GLuint *))
FNSYM(glDeleteTextures, void, (GLsizei, const GLuint *))
FNSYM(glDepthFunc, void, (GLenum))
FNSYM(glDisable, void, (GLenum))
FNSYM(glDisableVertexAttribArray, void, (GLenum))
FNSYM(glDrawArrays, void, (GLenum, GLint, GLsizei))
FNSYM(glDrawArraysInstanced, void, (GLenum, GLint, GLsizei, GLsizei))
FNSYM(glDrawElements, void, (GLenum, GLsizei, GLenum, const void*))
FNSYM(glEnableVertexAttribArray, void, (GLuint))
FNSYM(glFrontFace, void, (GLenum))
FNSYM(glFramebufferRenderbuffer, void, (GLenum, GLenum, GLenum, GLuint))
FNSYM(glFramebufferTexture2D, void, (GLenum, GLenum, GLenum, GLuint, GLint))
FNSYM(glGenFramebuffers, void, (GLsizei, GLuint *))
FNSYM(glGenRenderbuffers, void, (GLsizei, GLuint *))
FNSYM(glGenBuffers, void, (GLsizei, GLuint*))
FNSYM(glGenTextures, void, (GLsizei, GLuint *))
FNSYM(glBindTexture, void, (GLenum, GLuint))
FNSYM(glGenVertexArrays, void, (GLsizei, GLuint*))
FNSYM(glGetAttribLocation, GLint, (GLuint, const GLchar*))
FNSYM(glGetError, GLenum, (void))
FNSYM(glGetProgramInfoLog, void, (GLuint, GLsizei, GLsizei*, GLchar*))
FNSYM(glGetIntegerv, void, (GLenum, GLint *))
FNSYM(glGetProgramiv, void, (GLuint, GLenum, GLint*))
FNSYM(glGetShaderInfoLog, void, (GLuint, GLsizei, GLsizei*, GLchar*))
FNSYM(glGetShaderiv, void, (GLuint, GLenum, GLint*))
FNSYM(glGetString, const GLubyte*, (GLenum))
FNSYM(glGetUniformLocation, GLint, (GLuint, const GLchar*))
FNSYM(glLinkProgram, void, (GLuint))
FNSYM(glRenderbufferStorage, void, (GLenum, GLenum, GLsizei, GLsizei))
FNSYM(glShaderSource, void, (GLuint, GLsizei, const GLchar *const*, const GLint*))
FNSYM(glTexImage2D, void, (GLenum, GLint, GLint, GLsizei, GLsizei, GLint, GLenum, GLenum, const void *))
FNSYM(glTexParameterf, void, (GLenum, GLenum, GLfloat))
FNSYM(glTexParameterfv, void, (GLenum, GLenum, const GLfloat *))
FNSYM(glTexParameteri, void, (GLenum, GLenum, GLint))
FNSYM(glTexParameteriv, void, (GLenum, GLenum, const GLint *))
FNSYM(glUniform1f, void, (GLint, GLfloat))
FNSYM(glUniform1i, void, (GLint, GLint))
FNSYM(glUniform2f, void, (GLint location, GLfloat v0, GLfloat v1))
FNSYM(glUniform2fv, void, (GLint location, GLsizei count, const GLfloat *value))
FNSYM(glUniform3fv, void, (GLint, GLsizei, const GLfloat*))
FNSYM(glUniform4fv, void, (GLint, GLsizei, const GLfloat*))
FNSYM(glUniformMatrix4fv, void, (GLint, GLsizei, GLboolean, const GLfloat*))
FNSYM(glUseProgram, void, (GLuint))
FNSYM(glVertexAttribPointer, void, (GLuint, GLint, GLenum, GLboolean, GLsizei, const void*))
