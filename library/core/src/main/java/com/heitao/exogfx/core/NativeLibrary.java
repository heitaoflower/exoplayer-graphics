package com.heitao.exogfx.core;

/**
 * Created by showtime on 9/2/2017.
 */

public class NativeLibrary {

    private static final String LIB_NAME = "lib-exogfx";

    static
    {
        System.loadLibrary(LIB_NAME);
    }

    public static native void nativeInitializeContext();

    public static native void nativeOnSurfaceChanged(long renderer, int width, int height);

    public static native void nativeOnSurfaceCreated(long renderer, int texture);

    public static native void nativeDrawFrame(long renderer, int texture, float[] stMatrix);

    public static native void nativeOnPause(long renderer);

    public static native void nativeOnResume(long renderer);

    public static native long nativeCreateRenderer();

    public static native void nativeDestroyRenderer(long renderer);

}
