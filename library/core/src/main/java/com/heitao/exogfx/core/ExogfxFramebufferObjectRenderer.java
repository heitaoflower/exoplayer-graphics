package com.heitao.exogfx.core;

import android.opengl.GLSurfaceView;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by showtime on 9/5/2017.
 */

abstract class ExogfxFramebufferObjectRenderer implements GLSurfaceView.Renderer {

    private static final String TAG = ExogfxFramebufferObjectRenderer.class.getSimpleName();

    private long nativeRenderer;

    public ExogfxFramebufferObjectRenderer()
    {
        NativeLibrary.nativeInitializeContext();
        nativeRenderer = NativeLibrary.nativeCreateRenderer();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        NativeLibrary.nativeOnSurfaceCreated(nativeRenderer);

        onSurfaceCreated(config);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        NativeLibrary.nativeOnSurfaceChanged(nativeRenderer, width, height);

        onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        onDrawFrame();

        NativeLibrary.nativeDrawFrame(nativeRenderer, 1);
    }

    public abstract void onSurfaceCreated(EGLConfig config);

    public abstract void onSurfaceChanged(int width, int height);

    public abstract void onDrawFrame();


}
