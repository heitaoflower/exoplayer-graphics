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

    public static native void nativeGlGenTextures(int[] textures);

    public static native void nativeGlBindTexture(int target, int texture);

    public static native void nativeGlClearColor(float red, float green, float blue, float alpha);

    public static native void nativeSetupSampler(int target, float mag, float min);
}
