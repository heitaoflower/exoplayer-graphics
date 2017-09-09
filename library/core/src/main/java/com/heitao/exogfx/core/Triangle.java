package com.heitao.exogfx.core;

import android.opengl.GLES20;

import com.heitao.exogfx.ogles.OGLES;
import com.heitao.exogfx.ogles.OGLESUtil;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/**
 * Created by showtime on 9/8/2017.
 */

public class Triangle {
    private final String vertexShaderCode =
            "attribute vec4 vPosition;" +
                    "attribute vec2 aTextureCoord;" +
                    "varying highp vec2 vTextureCoord;" +
                    "void main() {" +
                    "  gl_Position = vPosition;" +
                    "  vTextureCoord = aTextureCoord.xy;" +
                    "}";

    private final String fragmentShaderCode =
            "precision mediump float;" +
                    "varying highp vec2 vTextureCoord;" +
                    "uniform vec4 vColor;" +
                    "void main() {" +
                    "  gl_FragColor = vec4(vTextureCoord.x,0.0, 0.0, 1.0);" +
                    "}";
    private FloatBuffer vertexBuffer;
    private int vertexBufferName;

    private int mPositionHandle;
    private int mUvHandle;
    private int mColorHandle;

    // REC
    private static final float[] rectangleCoords = new float[]{
            // X, Y, Z, U, V
            -1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 0.5f, 1.0f,
            -1.0f, -1.0f, 0.0f, 0.2f, 0.0f,
            1.0f, -1.0f, 0.0f, 0.1f, 0.0f
    };

    private static final int FLOAT_SIZE_BYTES = 4;
    protected static final int VERTICES_DATA_POS_SIZE = 3;
    protected static final int VERTICES_DATA_UV_SIZE = 2;
    protected static final int VERTICES_DATA_STRIDE_BYTES = (VERTICES_DATA_POS_SIZE + VERTICES_DATA_UV_SIZE) * FLOAT_SIZE_BYTES;
    protected static final int VERTICES_DATA_POS_OFFSET = 0 * FLOAT_SIZE_BYTES;
    protected static final int VERTICES_DATA_UV_OFFSET = VERTICES_DATA_POS_OFFSET + VERTICES_DATA_POS_SIZE * FLOAT_SIZE_BYTES;

    public void draw() {
        // 添加program到OpenGL ES环境中
        OGLES.glUseProgram(mProgram);

        // 获取指向vertex shader的成员vPosition的handle
        mPositionHandle = OGLES.glGetAttribLocation(mProgram, "vPosition");
        mUvHandle = OGLES.glGetAttribLocation(mProgram, "aTextureCoord");
        OGLES.glBindBuffer(GLES20.GL_ARRAY_BUFFER, vertexBufferName);
        // 启用一个指向三角形的顶点数组的handle
        OGLES.glEnableVertexAttribArray(mPositionHandle);

        //准备三角形的坐标数据
        OGLES.glVertexAttribPointer(mPositionHandle, VERTICES_DATA_POS_SIZE,
                GLES20.GL_FLOAT, false,
                VERTICES_DATA_STRIDE_BYTES, VERTICES_DATA_POS_OFFSET);

        OGLES.glEnableVertexAttribArray(mUvHandle);
        OGLES.glVertexAttribPointer(mUvHandle, VERTICES_DATA_UV_SIZE,
                GLES20.GL_FLOAT, false,
                VERTICES_DATA_STRIDE_BYTES, VERTICES_DATA_UV_OFFSET);

        // 获取指向fragment shader的成员vColor的handle
        mColorHandle = OGLES.glGetUniformLocation(mProgram, "vColor");

        //  绘制三角形
        OGLES.glUniform4fv(mColorHandle, 1, color);

        // Draw the triangle
        OGLES.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);

        // 禁用指向三角形的顶点数组
        OGLES.glDisableVertexAttribArray(mPositionHandle);
    }
    // 设置三角形颜色和透明度（r,g,b,a）
    float color[] = {0.0f, 1.0f, 0f, 1.0f};//绿色不透明
    private final int mProgram;
    public Triangle() {
        // 初始化顶点字节缓冲区，用于存放形状的坐标
        ByteBuffer bb = ByteBuffer.allocateDirect(
                //(每个浮点数占用4个字节
                rectangleCoords.length * 4);
        //设置使用设备硬件的原生字节序
        bb.order(ByteOrder.nativeOrder());

        //从ByteBuffer中创建一个浮点缓冲区
        vertexBuffer = bb.asFloatBuffer();
        // 把坐标都添加到FloatBuffer中
        vertexBuffer.put(rectangleCoords);
        //设置buffer从第一个坐标开始读
        vertexBuffer.position(0);

        int vertexShader = OGLESUtil.loadShader(GLES20.GL_VERTEX_SHADER,
                vertexShaderCode);
        int fragmentShader = OGLESUtil.loadShader(GLES20.GL_FRAGMENT_SHADER,
                fragmentShaderCode);

        // 创建空的OpenGL ES Program
        mProgram = OGLES.glCreateProgram();

        // 将vertex shader添加到program
        OGLES.glAttachShader(mProgram, vertexShader);

        // 将fragment shader添加到program
        OGLES.glAttachShader(mProgram, fragmentShader);

        // 创建可执行的 OpenGL ES program
        OGLES.glLinkProgram(mProgram);

        vertexBufferName = OGLESUtil.createBuffer(vertexBuffer);
    }
}
