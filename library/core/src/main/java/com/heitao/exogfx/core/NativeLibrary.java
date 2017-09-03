package com.heitao.exogfx.core;

/**
 * Created by showtime on 9/2/2017.
 */

public class NativeLibrary {

    static
    {
        System.loadLibrary("exogfx_jni");
    }

    public static native void init(int width, int height);

    public static native void setup();
}
