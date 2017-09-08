package com.heitao.exogfx.ogles;

import com.heitao.exogfx.core.NativeLibrary;
import com.heitao.exogfx.view.PlayerScaleType;

/**
 * Created by showtime on 9/7/2017.
 */

public final class OGLES extends NativeLibrary {

    public static native int glCheckFramebufferStatus(int target);

    public static native void glClear(int mask);

    public static native void glClearColor(float red, float green, float blue, float alpha);

    public static native void glGenTextures(int[] textures);

    public static native void glBindTexture(int target, int texture);

    public static native void glTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, java.nio.Buffer pixels);

    public static native int glGetAttribLocation(int program, String name);

    public static native void glGetIntegerv(int pname, int[] params);

    public static native int glGetUniformLocation(int program, String name);

    public static native void glDeleteFramebuffers(int[] framebuffers);

    public static native void glDeleteRenderbuffers(int[] renderbuffers);

    public static native void glDeleteTextures(int[] texture);

    public static native void glDisableVertexAttribArray(int index);

    public static native void glDrawArrays(int mode, int first, int count);

    public static native void glEnableVertexAttribArray(int index);

    public static native void glFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer);

    public static native void glFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level);

    public static native void glGenFramebuffers(int[] framebuffers);

    public static native void glActiveTexture(int texture);

    public static native void glBindBuffer(int target, int buffer);

    public static native void glBindFramebuffer(int target, int framebuffer);

    public static native void glBindRenderbuffer(int target, int renderbuffer);

    public static native void glRenderbufferStorage(int target, int internalformat, int width, int height);

    public static native void glGenRenderbuffers(int[] renderbuffers);

    public static native void glDeleteProgram(int program);

    public static native void glDeleteShader(int shader);

    public static native void glDeleteBuffers(int[] buffers);

    public static native void glUniform1f(int location, float value);

    public static native void glUniform1i(int location, int value);

    public static native void glUniformMatrix4fv(int location, int count, boolean transpose, float[] value);

    public static native void glUseProgram(int program);

    public static native void glVertexAttribPointer(int index, int size, int type, boolean normalized, int stride, int offset);
}
