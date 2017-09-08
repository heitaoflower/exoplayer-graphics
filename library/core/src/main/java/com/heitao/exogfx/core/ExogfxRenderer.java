package com.heitao.exogfx.core;

import android.graphics.SurfaceTexture;
import android.opengl.GLES20;
import android.opengl.Matrix;
import android.view.Surface;

import com.google.android.exoplayer2.SimpleExoPlayer;
import com.heitao.exogfx.ogles.OGLES;
import com.heitao.exogfx.ogles.OGLESUtil;
import com.heitao.exogfx.view.ExogfxView;

import javax.microedition.khronos.egl.EGLConfig;

/**
 * Created by showtime on 9/7/2017.
 */

public class ExogfxRenderer extends ExogfxFramebufferObjectRenderer implements SurfaceTexture.OnFrameAvailableListener {

    private static final String TAG = ExogfxRenderer.class.getSimpleName();

    private ExogfxSurfaceTexture previewTexture;

    private boolean updateSurface = false;

    private int texName;

    private float[] mvpMatrix = new float[16];
    private float[] projectionMatrix = new float[16];
    private float[] modelMatrix = new float[16];
    private float[] viewMatrix = new float[16];
    private float[] stMatrix = new float[16];

    private ExogfxFramebufferObject filterFramebufferObject;

    private OGLESPreviewFilter previewFilter;

    private ExogfxView exogfxView;

    private float aspectRatio = 1f;

    private SimpleExoPlayer simpleExoPlayer;

    public static int loadShader(int type, String shaderCode){

        //创建一个vertex shader类型(GLES20.GL_VERTEX_SHADER)
        //或一个fragment shader类型(GLES20.GL_FRAGMENT_SHADER)
        int shader = GLES20.glCreateShader(type);

        // 将源码添加到shader并编译它
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);

        return shader;
    }
    private Triangle mTriangle;

    public ExogfxRenderer(ExogfxView exogfxView)
    {
        super();
        this.exogfxView = exogfxView;
    }

    @Override
    public void onSurfaceCreated(EGLConfig config) {

//        NativeLibrary.nativeOnSurfaceCreated();
//
//        int[] textures = new int[1];
//        OGLES.glGenTextures(textures);
//        texName = textures[0];
//
//        previewTexture = new ExogfxSurfaceTexture(texName);
//        previewTexture.setOnFrameAvailableListener(this);
//
//        OGLES.glBindTexture(previewTexture.getTextureTarget(), texName);
//        OGLESUtil.setupSampler(previewTexture.getTextureTarget(), GLES20.GL_LINEAR, GLES20.GL_NEAREST);
//        OGLES.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
//
//        filterFramebufferObject = new ExogfxFramebufferObject();
//
//        previewFilter = new OGLESPreviewFilter(previewTexture.getTextureTarget());
//        previewFilter.setup();
//
//        Surface surface = new Surface(previewTexture.getSurfaceTexture());
//
//        simpleExoPlayer.setVideoSurface(surface);
//
//        Matrix.setLookAtM(viewMatrix, 0,
//                0.0f, 0.0f, 5.0f,
//                0.0f, 0.0f, 0.0f,
//                0.0f, 1.0f, 0.0f
//        );

        mTriangle = new Triangle();
    }

    @Override
    public void onSurfaceChanged( int width, int height) {

//        NativeLibrary.nativeInitializeGfx(width, height);
//        NativeLibrary.nativeOnSurfaceChanged();
//
//        filterFramebufferObject.setup(width, height);
//        previewFilter.setFrameSize(width, height);
//
//        aspectRatio = (float) width / height;
//
//        Matrix.frustumM(projectionMatrix, 0, -aspectRatio, aspectRatio, -1, 1, 5, 7);
//        Matrix.setIdentityM(modelMatrix, 0);
    }

    @Override
    public void onDrawFrame(final ExogfxFramebufferObject framebufferObject) {

        synchronized (this)
        {
            if (updateSurface)
            {
                previewTexture.updateTexImage();
                previewTexture.getTransformMatrix(stMatrix);
                updateSurface = false;
            }
        }
        OGLES.glClear(GLES20.GL_COLOR_BUFFER_BIT);

        mTriangle.draw();

//        Matrix.multiplyMM(mvpMatrix, 0, viewMatrix, 0, modelMatrix, 0);
//        Matrix.multiplyMM(mvpMatrix, 0, projectionMatrix, 0, mvpMatrix, 0);
//
//        previewFilter.draw(texName, mvpMatrix, stMatrix, aspectRatio);

    }

    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {

        updateSurface = true;

        exogfxView.requestRender();

    }

    public void setSimpleExoPlayer(SimpleExoPlayer simpleExoPlayer) {
        this.simpleExoPlayer = simpleExoPlayer;
    }
}
