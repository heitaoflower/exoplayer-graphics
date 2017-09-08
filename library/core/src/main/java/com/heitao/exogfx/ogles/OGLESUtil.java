package com.heitao.exogfx.ogles;

import com.heitao.exogfx.core.NativeLibrary;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * Created by showtime on 9/7/2017.
 */

public class OGLESUtil extends NativeLibrary {

    private static final int FLOAT_SIZE_BYTES = 4;

    public static native void setupSampler(int target, int mag, int min);

    public static native int loadShader(int shaderType, String shaderSource);

    public static native int createProgram(int vertexShader, int fragmentShader);

    public static native int createBuffer(final FloatBuffer buffer);

    public static int createBuffer(float[] data)
    {
        return createBuffer(toFloatBuffer(data));
    }

    private static FloatBuffer toFloatBuffer(final float[] data)
    {
        final FloatBuffer buffer = ByteBuffer.allocateDirect(data.length * FLOAT_SIZE_BYTES).order(ByteOrder.nativeOrder()).asFloatBuffer();

        buffer.put(data).position(0);

        return buffer;
    }
}
