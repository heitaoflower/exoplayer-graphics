package com.heitao.exogfx.ogles;

import com.heitao.exogfx.core.NativeLibrary;

import java.nio.FloatBuffer;

/**
 * Created by showtime on 9/7/2017.
 */

public class OGLESUtil extends NativeLibrary {

    public static native void setupSampler(int target, float mag, float min);

    public static native int loadShader(int shaderType, String shaderSource);

    public static native int createProgram(int vertexShader, int fragmentShader);

    public static native int createBuffer(float[] data);

}
