package com.heitao.exogfx.core;

import android.content.res.Resources;
import android.opengl.GLES20;

import com.heitao.exogfx.ogles.OGLES;
import com.heitao.exogfx.ogles.OGLESUtil;

import java.util.HashMap;

import static android.opengl.GLES20.GL_FRAGMENT_SHADER;
import static android.opengl.GLES20.GL_VERTEX_SHADER;
import static android.opengl.GLES20.glGetUniformLocation;

/**
 * Created by showtime on 9/7/2017.
 */

public class OGLESFilter {

    public static final String DEFAULT_UNIFORM_SAMPLER = "sTexture";

    protected static final String DEFAULT_VERTEX_SHADER =
            "attribute vec4 aPosition;\n" +
                    "attribute vec4 aTextureCoord;\n" +
                    "varying highp vec2 vTextureCoord;\n" +
                    "void main() {\n" +
                    "gl_Position = aPosition;\n" +
                    "vTextureCoord = aTextureCoord.xy;\n" +
                    "}\n";

    protected static final String DEFAULT_FRAGMENT_SHADER =
            "precision mediump float;\n" +
                    "varying highp vec2 vTextureCoord;\n" +
                    "uniform lowp sampler2D sTexture;\n" +
                    "void main() {\n" +
                    "gl_FragColor = texture2D(sTexture, vTextureCoord);\n" +
                    "}\n";


    private static final float[] VERTICES_DATA = new float[]{
            //X,  Y,     Z,    U,    V
            -1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
            1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            1.0f,  -1.0f, 0.0f, 1.0f, 0.0f
    };

    private   static final int FLOAT_SIZE_BYTES = 4;
    protected static final int VERTICES_DATA_POSITION_SIZE = 3;
    protected static final int VERTICES_DATA_UV_SIZE = 2;
    protected static final int VERTICES_DATA_STRIDE_BYTES = (VERTICES_DATA_POSITION_SIZE + VERTICES_DATA_UV_SIZE) * FLOAT_SIZE_BYTES;
    protected static final int VERTICES_DATA_POSITION_OFFSET = 0 * FLOAT_SIZE_BYTES;
    protected static final int VERTICES_DATA_UV_OFFSET = VERTICES_DATA_POSITION_OFFSET + VERTICES_DATA_POSITION_SIZE * FLOAT_SIZE_BYTES;

    private final String vertexShaderSource;
    private final String fragmentShaderSource;

    private int program;

    private int vertexShader;
    private int fragmentShader;

    private int vertexBufferName;

    private final HashMap<String, Integer> handleMap = new HashMap<>();

    public OGLESFilter()
    {
        this(DEFAULT_VERTEX_SHADER, DEFAULT_FRAGMENT_SHADER);
    }

    public OGLESFilter(final Resources res, final int vertexShaderSourceResId, final int fragmentShaderSourceResId)
    {
        this(res.getString(vertexShaderSourceResId), res.getString(fragmentShaderSourceResId));
    }

    public OGLESFilter(final String vertexShaderSource, final String fragmentShaderSource) {
        this.vertexShaderSource = vertexShaderSource;
        this.fragmentShaderSource = fragmentShaderSource;
    }

    public void setup()
    {
        release();

        vertexShader = OGLESUtil.loadShader(GL_VERTEX_SHADER, vertexShaderSource);
        fragmentShader = OGLESUtil.loadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
        program = OGLESUtil.createProgram(vertexShader, fragmentShader);
        vertexBufferName = OGLESUtil.createBuffer(VERTICES_DATA);
    }

    public void setFrameSize(final int width, final int height) {
    }

    public void release()
    {
        OGLES.glDeleteProgram(program);
        program = 0;

        OGLES.glDeleteShader(vertexShader);
        vertexShader = 0;

        OGLES.glDeleteShader(fragmentShader);
        fragmentShader = 0;

        OGLES.glDeleteBuffers(new int[]{vertexBufferName});
        vertexBufferName = 0;

        handleMap.clear();
    }

    public void draw(final int texName, final ExogfxFramebufferObject framebufferObject)
    {

    }

    protected void onDraw()
    {

    }

    protected final void useProgram()
    {
        OGLES.glUseProgram(program);
    }

    protected final int getVertexBufferName()
    {
        return vertexBufferName;
    }

    protected final int getHandle(final String name)
    {
        final Integer value = handleMap.get(name);
        if (value != null)
        {
            return value;
        }

        int location = OGLES.glGetAttribLocation(program, name);

        if (location == -1)
        {
            location = glGetUniformLocation(program, name);
        }

        if (location == -1)
        {
            throw new IllegalStateException("could not get attrib or uniform location for " + name);
        }

        handleMap.put(name, location);

        return location;
    }
}

