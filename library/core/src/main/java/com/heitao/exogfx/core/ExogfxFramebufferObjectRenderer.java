package com.heitao.exogfx.core;

import android.opengl.GLES20;
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
    private OGLESFilter presentFilter;

    public ExogfxFramebufferObjectRenderer()
    {
        NativeLibrary.nativeInitializeContext();
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        framebufferObject = new ExogfxFramebufferObject();
        presentFilter = new OGLESFilter();
        presentFilter.setup();

        onSurfaceCreated(config);
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        framebufferObject.setup(width, height);
        presentFilter.setFrameSize(width, height);

        onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        framebufferObject.enable();
        OGLES.glViewport(0, 0, framebufferObject.getWidth(), framebufferObject.getHeight());

        onDrawFrame(framebufferObject);

        OGLES.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, 0);
        OGLES.glViewport(0, 0, framebufferObject.getWidth(), framebufferObject.getHeight());

        OGLES.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);

        presentFilter.draw(framebufferObject.getTexName(), null);
    }

    public abstract void onSurfaceCreated(EGLConfig config);

    public abstract void onSurfaceChanged(int width, int height);

    public abstract void onDrawFrame(ExogfxFramebufferObject framebufferObject);


}
