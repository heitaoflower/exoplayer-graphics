package com.heitao.exogfx.core;

import android.opengl.GLSurfaceView;

import com.heitao.exogfx.ogles.OGLES;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by showtime on 9/5/2017.
 */

abstract class ExogfxFramebufferObjectRenderer implements GLSurfaceView.Renderer {

    private static final String TAG = ExogfxFramebufferObjectRenderer.class.getSimpleName();

    private ExogfxFramebufferObject framebufferObject;

    public ExogfxFramebufferObjectRenderer()
    {
        NativeLibrary.nativeInitializeContext();
    }

    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        framebufferObject = new ExogfxFramebufferObject();

        onSurfaceCreated(config);
    }

    public void onSurfaceChanged(GL10 gl, int width, int height) {

        framebufferObject.setup(width, height);
        onSurfaceChanged(width, height);
    }

    public void onDrawFrame(GL10 gl) {

        framebufferObject.enable();

        onDrawFrame(framebufferObject);
    }

    public abstract void onSurfaceCreated(EGLConfig config);

    public abstract void onSurfaceChanged(int width, int height);

    public abstract void onDrawFrame(ExogfxFramebufferObject framebufferObject);


}
