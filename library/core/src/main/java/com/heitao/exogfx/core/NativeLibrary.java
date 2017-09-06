package com.heitao.exogfx.core;

/**
 * Created by showtime on 9/2/2017.
 */

public class NativeLibrary {

    private static final String LIB_NAME = "exogfx_jni";

    static {
        System.loadLibrary(LIB_NAME);
    }

    public static native void nativeInitializeContext();

    public static native void nativeOnSurfaceChanged();

    public static native void nativeOnSurfaceCreated();

    public static native void nativeDrawFrame();

    public static native void nativeInitializeGfx(int width, int height);

    public static native int nativeGlCheckFramebufferStatus(int target);

    public static native void nativeGlClearColor(float red, float green, float blue, float alpha);

    public static native void nativeGlGenTextures(int[] textures);

    public static native void nativeGlBindTexture(int target, int texture);

    public static native void nativeGlTexImage2D(int target, int level, int internalformat, int width, int height, int border, int format, int type, java.nio.Buffer pixels);

    public static native void nativeGlGetIntegerv(int pname, int[] params);

    public static native void nativeGlDeleteFramebuffers(int[] framebuffers);

    public static native void nativeGlDeleteRenderbuffers(int[] renderbuffers);

    public static native void nativeGlDeleteTextures(int[] texture);

    public static native void nativeGlFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer);

    public static native void nativeGlFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level);

    public static native void nativeGlGenFramebuffers(int[] framebuffers);

    public static native void nativeGlBindRenderbuffer(int target, int renderbuffer);

    public static native void nativeGlBindFramebuffer(int target, int framebuffer);

    public static native void nativeGlRenderbufferStorage(int target, int internalformat, int width, int height);

    public static native void nativeGlGenRenderbuffers(int[] renderbuffers);

    public static native void nativeSetupSampler(int target, float mag, float min);

}
