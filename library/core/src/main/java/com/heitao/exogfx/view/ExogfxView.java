package com.heitao.exogfx.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.Log;

import com.heitao.exogfx.core.NativeLibrary;
import com.heitao.exogfx.egl.DefaultEGLConfigChooser;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by showtime on 9/3/2017.
 */

public class ExogfxView extends GLSurfaceView {

    protected int[] value = new int[1];

    public ExogfxView(Context context) {
        super(context);

        setEGLContextFactory(new ContextFactory());

        setEGLConfigChooser(new DefaultEGLConfigChooser());

        setRenderer(new Renderer());
    }

    private static class ContextFactory implements GLSurfaceView.EGLContextFactory
    {
        @Override
        public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig eglConfig) {
            final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

            int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE};

            EGLContext context = egl.eglCreateContext(display, eglConfig, EGL10.EGL_NO_CONTEXT, attrib_list);

            return context;
        }

        @Override
        public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
            egl.eglDestroyContext(display, context);
        }
    }


    private static class Renderer implements GLSurfaceView.Renderer
    {
        public void onDrawFrame(GL10 gl)
        {
            NativeLibrary.nativeDrawFrame();
        }

        public void onSurfaceChanged(GL10 gl, int width, int height)
        {
            NativeLibrary.nativeInitializeGfx(width,height);
        }

        public void onSurfaceCreated(GL10 gl, EGLConfig config)
        {

        }
    }
}
