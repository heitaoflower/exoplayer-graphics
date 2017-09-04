package com.heitao.exogfx.core;

/**
 * Created by showtime on 9/2/2017.
 */

public class NativeLibrary {

    private static final String LIB_NAME = "exogfx_jni";

    static {
        System.loadLibrary(LIB_NAME);
    }

    public static native void nativeInitializeGfx(int width, int height);

    public static native void nativeDrawFrame();
}
