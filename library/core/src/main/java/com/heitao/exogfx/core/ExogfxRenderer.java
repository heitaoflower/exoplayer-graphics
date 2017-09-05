package com.heitao.exogfx.core;

import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by showtime on 9/5/2017.
 */

public class ExogfxRenderer implements GLSurfaceView.Renderer {

    private static final String TAG = ExogfxRenderer.class.getSimpleName();

    private ExogfxSurfaceTexture originalTexture;

    private int texName;

    public  ExogfxRenderer()
    {
        NativeLibrary.nativeInitializeContext();
    }

    public void onDrawFrame(GL10 gl) {
        NativeLibrary.nativeDrawFrame();
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        NativeLibrary.nativeGlClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        NativeLibrary.nativeOnSurfaceCreated();

        int[] textures = new int[1];
        NativeLibrary.nativeGlGenTextures(textures);
        texName = textures[0];

        originalTexture = new ExogfxSurfaceTexture(texName);

        NativeLibrary.nativeGlBindTexture(originalTexture.getTextureTarget(), texName);
        NativeLibrary.nativeSetupSampler(originalTexture.getTextureTarget(), GLES20.GL_LINEAR, GLES20.GL_NEAREST);

        Log.d(TAG, "c");
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {
        NativeLibrary.nativeInitializeGfx(width, height);
        NativeLibrary.nativeOnSurfaceChanged();
    }


}
