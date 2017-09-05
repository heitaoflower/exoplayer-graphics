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

#include "graphics/gfx.h"
#include "utils/logUtil.h"
#include "utils/glUtil.h"

#include <jni.h>
#include <stdlib.h>

#define JNI_METHOD(return_type, method_name) \
    JNIEXPORT return_type JNICALL            \
        Java_com_heitao_exogfx_core_NativeLibrary_##method_name

/* [Vertex source] */
static const char glVertexShader[] =
        "attribute vec4 vPosition;\n"
                "void main()\n"
                "{\n"
                "  gl_Position = vPosition;\n"
                "}\n";
/* [Vertex source] */

/* [Fragment source] */
static const char glFragmentShader[] =
        "precision mediump float;\n"
                "void main()\n"
                "{\n"
                "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
                "}\n";
/* [Fragment source] */

/* [loadShader] */
GLuint  loadShader(GLenum shaderType, const char* shaderSource)
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
                char * buf = (char*) malloc(infoLen);

                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not Compile Shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }

                glDeleteShader(shader);
                shader = 0;
            }
        }
    }

    return shader;
}

/* [createProgram] */
GLuint createProgram(const char* vertexSource, const char * fragmentSource)
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
                char* buf = (char*) malloc(bufLength);

                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }

    return program;
}
/* [createProgram] */

/* [setupGraphics] */
GLuint  simpleTriangleProgram;
GLuint  vPosition;

bool setupGraphics(int w, int h)
{
    simpleTriangleProgram = createProgram(glVertexShader, glFragmentShader);

    if (!simpleTriangleProgram)
    {
        LOGE("Could not create program");
        return false;
    }

    vPosition = glGetAttribLocation(simpleTriangleProgram, "vPosition");

    glViewport(0, 0, w, h);

    return true;
}
/* [setupGraphics] */

/* [renderFrame] */
const GLfloat triangleVertices[] = {
        0.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f
};

void renderFrame()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glUseProgram(simpleTriangleProgram);
    glVertexAttribPointer(vPosition, 2, GL_FLOAT, GL_FALSE, 0, triangleVertices);
    glEnableVertexAttribArray(vPosition);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
/* [renderFrame] */

JNIEXPORT void JNICALL Java_com_heitao_exogfx_core_NativeLibrary_nativeInitializeGfx(JNIEnv *env, jobject obj, jint width, jint height)
{
    setupGraphics(width, height);
}

JNI_METHOD(void, nativeInitializeContext)
(JNIEnv *evn, jobject obj)
{
    if (!init_gfx())
    {
        LOGE("initialized graphics failed.");
    }
}

JNI_METHOD(void, nativeCreateRenderer)
(JNIEnv *env, jobject obj)
{

}

JNI_METHOD(void, nativeOnSurfaceCreated)
(JNIEnv *env, jobject obj)
{

}

JNI_METHOD(void, nativeOnSurfaceChanged)
(JNIEnv *env, jobject obj, jint width, jint height)
{

}

JNI_METHOD(void, nativeDrawFrame)
(JNIEnv *env, jobject obj)
{
    renderFrame();
}

JNI_METHOD(void, nativeGlClearColor)
(JNIEnv *env, jobject obj, jfloat red, jfloat green, jfloat blue, jfloat alpha)
{
    glClearColor(red, green, blue, alpha);
}

JNI_METHOD(void, nativeGlGenTextures)
(JNIEnv *env, jobject obj, jintArray textures)
{
    GLsizei size = (*env)->GetArrayLength(env, textures);
    GLuint native_textures[size];

    glGenTextures(size, native_textures);

    (*env)->SetIntArrayRegion(env, textures, 0, size, (const jint*)native_textures);
}

JNI_METHOD(void, nativeGlBindTexture)
(JNIEnv *env, jobject obj, jint target, jint texture)
{
    glBindTexture((GLenum)target, (GLuint)texture);
}

JNI_METHOD(void, nativeSetupSampler)
(JNIEnv *env, jobject obj, jint target, jfloat mag, jfloat min)
{
    setupSampler((GLenum)target, (GLfloat)mag, (GLfloat)min);
}