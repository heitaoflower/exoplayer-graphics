package com.heitao.exogfx.egl;

import android.opengl.GLSurfaceView;
import android.util.Log;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;

import static javax.microedition.khronos.egl.EGL10.EGL_NONE;
import static javax.microedition.khronos.egl.EGL10.EGL_NO_CONTEXT;

/**
 * Created by showtime on 9/4/2017.
 */

public class DefaultEGLContextFactory implements GLSurfaceView.EGLContextFactory {
    private static final String TAG = DefaultEGLContextFactory.class.getSimpleName();

    private static final int EGL_CLIETN_VERSION = 2;

    private static final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;

    @Override
    public EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig config) {

        final int[] attributes = new int[]{EGL_CONTEXT_CLIENT_VERSION, EGL_CLIETN_VERSION, EGL_NONE};

        return egl.eglCreateContext(display, config, EGL_NO_CONTEXT, attributes);
    }

    @Override
    public void destroyContext(EGL10 egl, EGLDisplay display, EGLContext context) {
        if (!egl.eglDestroyContext(display, context)) {
            Log.e(TAG, "display: " + display + " context: " + context);
        }
    }
}
