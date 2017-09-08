package com.heitao.exogfx.core;

import android.opengl.GLES20;

import com.heitao.exogfx.ogles.OGLES;

/**
 * Created by showtime on 9/7/2017.
 */

public class OGLESPreviewFilter extends OGLESFilter {

    public static final int GL_TEXTURE_EXTERNAL_OES = 0x8D65;

    private static final String VERTEX_SHADER =
            "uniform mat4 uMVPMatrix;\n" +
                    "uniform mat4 uSTMatrix;\n" +
                    "uniform float uCRatio;\n" +

                    "attribute vec4 aPosition;\n" +
                    "attribute vec4 aTextureCoord;\n" +
                    "varying highp vec2 vTextureCoord;\n" +

                    "void main() {\n" +
                    "vec4 scaledPos = aPosition;\n" +
                    "scaledPos.x = scaledPos.x * uCRatio;\n" +
                    "gl_Position = uMVPMatrix * scaledPos;\n" +
                    "vTextureCoord = (uSTMatrix * aTextureCoord).xy;\n" +
                    "}\n";

    private final int texTarget;

    public OGLESPreviewFilter(final int texTarget) {
        super(VERTEX_SHADER, createFragmentShaderSourceOESIfNeed(texTarget));
        this.texTarget = texTarget;
    }

    private static String createFragmentShaderSourceOESIfNeed(final int texTarget) {
        if (texTarget == GL_TEXTURE_EXTERNAL_OES) {
            return new StringBuilder()
                    .append("#extension GL_OES_EGL_image_external : require\n")
                    .append(DEFAULT_FRAGMENT_SHADER.replace("sampler2D", "samplerExternalOES"))
                    .toString();
        }
        return DEFAULT_FRAGMENT_SHADER;
    }

    public void draw(final int texName, final float[] mvpMatrix, final float[] stMatrix, final float aspectRatio)
    {
        useProgram();

        OGLES.glUniformMatrix4fv(getHandle("uMVPMatrix"), 1, false, mvpMatrix);
        OGLES.glUniformMatrix4fv(getHandle("uSTMatrix"), 1, false, stMatrix);
        OGLES.glUniform1f(getHandle("uCRatio"), aspectRatio);

        OGLES.glBindBuffer(GLES20.GL_ARRAY_BUFFER, getVertexBufferName());
        OGLES.glEnableVertexAttribArray(getHandle("aPosition"));
        OGLES.glVertexAttribPointer(getHandle("aPosition"), VERTICES_DATA_POSITION_SIZE, GLES20.GL_FLOAT, false, VERTICES_DATA_STRIDE_BYTES, VERTICES_DATA_POSITION_OFFSET);
        OGLES.glEnableVertexAttribArray(getHandle("aTextureCoord"));
        OGLES.glVertexAttribPointer(getHandle("aTextureCoord"), VERTICES_DATA_UV_SIZE, GLES20.GL_FLOAT, false, VERTICES_DATA_STRIDE_BYTES, VERTICES_DATA_UV_OFFSET);

        OGLES.glActiveTexture(GLES20.GL_TEXTURE0);
        OGLES.glBindTexture(texTarget, texName);
        OGLES.glUniform1i(getHandle(DEFAULT_UNIFORM_SAMPLER), 0);

        OGLES.glDrawArrays(GLES20.GL_TRIANGLE_STRIP, 0, 4);

        OGLES.glDisableVertexAttribArray(getHandle("aPosition"));
        OGLES.glDisableVertexAttribArray(getHandle("aTextureCoord"));
        OGLES.glBindBuffer(GLES20.GL_ARRAY_BUFFER, 0);
        OGLES.glBindTexture(GLES20.GL_TEXTURE_2D, 0);

    }
}
