/*
 * Copyright (c) 2017 heitaoflower
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "context/context.h"
#include "utils/log_util.h"
#include "utils/ogles_util.h"

#include <jni.h>

#undef JNI_METHOD
#define JNI_METHOD(class_name, return_type, method_name)        \
    JNIEXPORT return_type JNICALL                               \
        Java_com_heitao_exogfx_core_##class_name##_##method_name

JNI_METHOD(NativeLibrary, void, nativeInitializeContext)
(JNIEnv *evn, jobject obj)
{
    if (!context_init())
    {
        LOGE("initialized context failed.");
    }
}

jlong jptr(struct exogfx_renderer *nativeRenderer)
{
    return (jlong)nativeRenderer;
}

struct exogfx_renderer* native(jlong ptr)
{
    return (struct exogfx_renderer*)ptr;
}
JNI_METHOD(NativeLibrary, jlong , nativeCreateRenderer)
(JNIEnv *env, jobject obj)
{
    return jptr(renderer);
}

JNI_METHOD(NativeLibrary, void, nativeDestroyRenderer)
(JNIEnv *env, jobject obj, jlong renderer)
{
    struct exogfx_renderer *nativeRenderer = native(renderer);
    nativeRenderer->destroy();
}

JNI_METHOD(NativeLibrary, void, nativeOnSurfaceCreated)
(JNIEnv *env, jobject obj, jlong renderer, jint texture)
{
    native(renderer)->create((GLuint)texture);
}

JNI_METHOD(NativeLibrary, void, nativeOnSurfaceChanged)
(JNIEnv *env, jobject obj, jlong renderer, jint width, jint height)
{
    native(renderer)->resize((GLsizei)width, (GLsizei)height);
}

JNI_METHOD(NativeLibrary, void, nativeDrawFrame)
(JNIEnv *env, jobject obj, jlong renderer, jint texture, jfloatArray stMatrix)
{
    GLsizei size = (*env)->GetArrayLength(env, stMatrix);
    float nativeStMatrix[size];

    (*env)->GetFloatArrayRegion(env, stMatrix, 0, size, nativeStMatrix);

    native(renderer)->draw((GLuint*)&texture, nativeStMatrix);
}

JNI_METHOD(NativeLibrary, void, nativeOnResume)
(JNIEnv *env, jobject obj, jlong renderer)
{

}

JNI_METHOD(NativeLibrary, void, nativeOnPause)
(JNIEnv *env, jobject obj, jlong renderer)
{

}

#undef JNI_METHOD
#define JNI_METHOD(class_name, return_type, method_name)        \
    JNIEXPORT return_type JNICALL                               \
        Java_com_heitao_exogfx_ogles_##class_name##_##method_name

JNI_METHOD(OGLES, jint , glCheckFramebufferStatus)
(JNIEnv *env, jobject obj, jint target)
{
    return glCheckFramebufferStatus((GLenum)target);
}

JNI_METHOD(OGLES, void, glClear)
(JNIEnv *env, jobject obj, jint mask)
{
    glClear((GLbitfield)mask);
}

JNI_METHOD(OGLES, void, glClearColor)
(JNIEnv *env, jobject obj, jfloat red, jfloat green, jfloat blue, jfloat alpha)
{
    glClearColor(red, green, blue, alpha);
}

JNI_METHOD(OGLES, void, glViewport)
(JNIEnv *env, jobject obj, jint x, jint y, jint width, jint height)
{
    glViewport((GLint)x, (GLint)y, (GLsizei)width, (GLsizei)height);
}

JNI_METHOD(OGLES, void, glAttachShader)
(JNIEnv *env, jobject obj, jint program, jint shader)
{
    glAttachShader((GLuint)program, (GLuint)shader);
}

JNI_METHOD(OGLES, void, glGenTextures)
(JNIEnv *env, jobject obj, jintArray textures)
{
    GLsizei size = (*env)->GetArrayLength(env, textures);
    GLuint nativeTextures[size];

    glGenTextures(size, nativeTextures);

    (*env)->SetIntArrayRegion(env, textures, 0, size, (const jint*)nativeTextures);
}

JNI_METHOD(OGLES, void, glBindTexture)
(JNIEnv *env, jobject obj, jint target, jint texture)
{
    glBindTexture((GLenum)target, (GLuint)texture);
}

JNI_METHOD(OGLES, void, glTexImage2D)
(JNIEnv *env, jobject obj, jint target, jint level, jint internalformat, jint width, jint height, jint border, jint format, jint type, jbyteArray pixels)
{
    const void *nativePixels = pixels != NULL ? (*env)->GetByteArrayElements(env, pixels, JNI_FALSE) : NULL;

    glTexImage2D((GLenum)target, (GLint)level, (GLint)internalformat, (GLsizei)width, (GLsizei)height, (GLint)border, (GLenum)format, (GLenum)type, nativePixels);
}

JNI_METHOD(OGLES, jint , glGetAttribLocation)
(JNIEnv *env, jobject obj, jint program, jstring name)
{
    const GLchar *nativeName = (*env)->GetStringUTFChars(env, name, JNI_FALSE);

    GLint location = glGetAttribLocation((GLuint)program, nativeName);

    (*env)->ReleaseStringUTFChars(env, name, nativeName);

    return location;

}

JNI_METHOD(OGLES, void, glGetIntegerv)
(JNIEnv *env, jobject obj, jint pname, jintArray data)
{
    GLsizei size = (*env)->GetArrayLength(env, data);

    GLint nativeData[size];

    glGetIntegerv((GLenum)pname, nativeData);

    (*env)->SetIntArrayRegion(env, data, 0, size, nativeData);
}

JNI_METHOD(OGLES, jint , glGetUniformLocation)
(JNIEnv *env, jobject obj, jint program, jstring name)
{
    const GLchar *nativeName = (*env)->GetStringUTFChars(env, name, JNI_FALSE);

    GLint location = glGetUniformLocation((GLuint)program, nativeName);

    (*env)->ReleaseStringUTFChars(env, name, nativeName);

    return location;
}

JNI_METHOD(OGLES, void, glDeleteFramebuffers)
(JNIEnv *env, jobject obj, jintArray framebuffers)
{
    GLsizei size = (*env)->GetArrayLength(env, framebuffers);

    const GLuint *nativeFramebuffers = (const GLuint *)(*env)->GetIntArrayElements(env, framebuffers, JNI_FALSE);

    glDeleteFramebuffers(size, nativeFramebuffers);
}

JNI_METHOD(OGLES, void, glDeleteRenderbuffers)
(JNIEnv *env, jobject obj, jintArray renderbuffers)
{
    GLsizei size = (*env)->GetArrayLength(env, renderbuffers);

    const GLuint *nativeRenderbuffers = (const GLuint *)(*env)->GetIntArrayElements(env, renderbuffers, JNI_FALSE);

    glDeleteRenderbuffers(size, nativeRenderbuffers);
}

JNI_METHOD(OGLES, void, glDeleteTextures)
(JNIEnv *env, jobject obj, jintArray textures)
{
    GLsizei size = (*env)->GetArrayLength(env, textures);

    const GLuint *nativeTextures = (const GLuint *)(*env)->GetIntArrayElements(env, textures, JNI_FALSE);

    glDeleteTextures(size, nativeTextures);
}

JNI_METHOD(OGLES, void, glDisableVertexAttribArray)
(JNIEnv *env, jobject obj, jint index)
{
    glDisableVertexAttribArray((GLenum)index);
}
JNI_METHOD(OGLES, void, glDrawArrays)
(JNIEnv *env, jobject obj, jint mode, jint first, jint count)
{
    glDrawArrays((GLenum)mode, (GLint)first, (GLsizei)count);
}

JNI_METHOD(OGLES, void, glEnableVertexAttribArray)
(JNIEnv *env, jobject obj, jint index)
{
    glEnableVertexAttribArray((GLuint)index);
}

JNI_METHOD(OGLES, void, glFramebufferRenderbuffer)
(JNIEnv *env, jobject obj, jint target, jint attachment, jint renderbuffertarget, jint renderbuffer)
{
    glFramebufferRenderbuffer((GLenum)target, (GLenum)attachment, (GLenum)renderbuffertarget, (GLuint)renderbuffer);
}

JNI_METHOD(OGLES, void, glFramebufferTexture2D)
(JNIEnv *env, jobject obj, jint target, jint attachment, jint textarget, jint texture, jint level)
{
    glFramebufferTexture2D((GLenum)target, (GLenum)attachment, (GLenum)textarget, (GLuint)texture, (GLenum)level);
}

JNI_METHOD(OGLES, void, glGenFramebuffers)
(JNIEnv *env, jobject obj, jintArray framebuffers)
{
    GLsizei size = (*env)->GetArrayLength(env, framebuffers);
    GLuint nativeFramebuffers[size];

    glGenFramebuffers(size, nativeFramebuffers);
    (*env)->SetIntArrayRegion(env, framebuffers, 0, size, (const jint*)nativeFramebuffers);
}

JNI_METHOD(OGLES, void, glActiveTexture)
(JNIEnv *env, jobject obj, jint texture)
{
    glActiveTexture((GLenum)texture);
}

JNI_METHOD(OGLES, void, glBindBuffer)
(JNIEnv *env, jobject obj, jint target, jint buffer)
{
    glBindBuffer((GLenum)target, (GLuint)buffer);
}

JNI_METHOD(OGLES, void, glBindFramebuffer)
(JNIEnv *env, jobject obj, jint target, jint framebuffer)
{
    glBindFramebuffer((GLenum)target, (GLuint)framebuffer);
}

JNI_METHOD(OGLES, void, glBindRenderbuffer)
(JNIEnv *env, jobject obj, jint target, jint renderbuffer)
{
    glBindRenderbuffer((GLenum)target, (GLuint)renderbuffer);
}

JNI_METHOD(OGLES, void, glLinkProgram)
(JNIEnv *env, jobject obj, jint program)
{
    glLinkProgram((GLuint)program);
}

JNI_METHOD(OGLES, void, glRenderbufferStorage)
(JNIEnv *env, jobject obj, jint target, jint internalformat, jint width, jint height)
{
    glRenderbufferStorage((GLenum)target, (GLenum)internalformat, (GLsizei)width, (GLsizei)height);
}

JNI_METHOD(OGLES, void, glGenRenderbuffers)
(JNIEnv *env, jobject obj, jintArray renderbuffers)
{
    GLsizei  size = (*env)->GetArrayLength(env, renderbuffers);
    GLuint nativeRenderbuffers[size];

    glGenRenderbuffers(size, nativeRenderbuffers);
    (*env)->SetIntArrayRegion(env, renderbuffers, 0, size, (const jint*)nativeRenderbuffers);
}

JNI_METHOD(OGLES, jint , glCreateProgram)
(JNIEnv *env, jobject obj)
{
    return glCreateProgram();
}

JNI_METHOD(OGLES, void, glDeleteProgram)
(JNIEnv *env, jobject obj, jint program)
{
    glDeleteProgram((GLuint)program);
}

JNI_METHOD(OGLES, void, glDeleteShader)
(JNIEnv *env, jobject obj, jint shader)
{
    glDeleteShader((GLuint)shader);
}

JNI_METHOD(OGLES, void, glDeleteBuffers)
(JNIEnv *env, jobject obj, jintArray buffers)
{
    GLsizei size = (*env)->GetArrayLength(env, buffers);
    const GLuint *nativeBuffers = (const GLuint *)(*env)->GetIntArrayElements(env, buffers, JNI_FALSE);
    glDeleteBuffers(size, nativeBuffers);
}

JNI_METHOD(OGLES, void, glUniform1f)
(JNIEnv *env, jobject obj, jint location, jfloat value)
{
    glUniform1f((GLint)location, (GLfloat)value);
}

JNI_METHOD(OGLES, void, glUniform1i)
(JNIEnv *env, jobject obj, jint location, jint value)
{
    glUniform1i((GLint)location, (GLint)value);
}

JNI_METHOD(OGLES, void, glUniform4fv)
(JNIEnv *env, jobject obj, jint location, jint count, jfloatArray value)
{
    const GLfloat *nativeValue = (*env)->GetFloatArrayElements(env, value, JNI_FALSE);

    glUniform4fv(location, count, nativeValue);
}

JNI_METHOD(OGLES, void, glUniformMatrix4fv)
(JNIEnv *env, jobject obj, jint location, jint count, jboolean transpose, jfloatArray value)
{
    const GLfloat *nativeValue = (*env)->GetFloatArrayElements(env, value, JNI_FALSE);

    glUniformMatrix4fv((GLint)location, (GLsizei)count, (GLboolean)transpose, nativeValue);
}

JNI_METHOD(OGLES, void, glUseProgram)
(JNIEnv *env, jobject obj, jint program)
{
    glUseProgram((GLuint)program);
}

JNI_METHOD(OGLES, void, glVertexAttribPointer)
(JNIEnv *env, jobject obj, jint index, jint size, jint type, jboolean normalized, jint stride, jint offset)
{
    glVertexAttribPointer((GLuint)index, (GLint)size, (GLenum)type, (GLboolean)normalized, (GLsizei)stride, (const void*)offset);
}

#undef JNI_METHOD
#define JNI_METHOD(class_name, return_type, method_name)        \
    JNIEXPORT return_type JNICALL                               \
        Java_com_heitao_exogfx_ogles_##class_name##_##method_name

JNI_METHOD(OGLESUtil, void, initSampler)
(JNIEnv *env, jobject obj, jint target, jint mag, jint min)
{
    initSampler((GLenum)target, (GLint)mag, (GLint)min);
}

JNI_METHOD(OGLESUtil, jint , loadShader)
(JNIEnv *env, jobject obj, jint shaderType, jstring shaderSource)
{
    const char *nativeShaderSource = (*env)->GetStringUTFChars(env, shaderSource, JNI_FALSE);

    GLuint shader = loadShader((GLenum)shaderType, nativeShaderSource);

    (*env)->ReleaseStringUTFChars(env, shaderSource, nativeShaderSource);

    return shader;
}

JNI_METHOD(OGLESUtil, jint, createProgram)
(JNIEnv *env, jobject obj, jint vertexShader, jint fragmentShader)
{
    return createProgram((GLuint)vertexShader, (GLuint)fragmentShader);
}

JNI_METHOD(OGLESUtil, jint, createBuffer)
(JNIEnv *env, jobject obj, jobject data, jint target)
{
    GLfloat *nativeData = (*env)->GetDirectBufferAddress(env, data);
    GLsizei nativeSize = (GLsizei)(*env)->GetDirectBufferCapacity(env, data);
    return createBuffer((GLenum)target, nativeData, nativeSize * sizeof(GLfloat));
}