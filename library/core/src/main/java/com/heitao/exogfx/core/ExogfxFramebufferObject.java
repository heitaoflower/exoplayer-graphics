package com.heitao.exogfx.core;

import android.opengl.GLES20;

/**
 * Created by showtime on 9/6/2017.
 */

public class ExogfxFramebufferObject {

    private int width;
    private int height;
    private int framebufferName;
    private int renderbufferName;
    private int texName;

    public int getWidth()
    {
        return width;
    }

    public int getHeight()
    {
        return height;
    }

    public int getTexName()
    {
        return texName;
    }

    public void setup(final int width, final int height)
    {
        final int[] params = new int[1];

        NativeLibrary.nativeGlGetIntegerv(GLES20.GL_MAX_TEXTURE_SIZE, params);

        if (width > params[0] || height > params[0])
        {
            throw new IllegalArgumentException("GL_MAX_TEXTURE_SIZE: " + params[0]);
        }

        NativeLibrary.nativeGlGetIntegerv(GLES20.GL_MAX_RENDERBUFFER_SIZE, params);
        if (width > params[0] || height > params[0])
        {
            throw new IllegalArgumentException("GL_MAX_RENDERBUFFER_SIZE: " + params[0]);
        }

        NativeLibrary.nativeGlGetIntegerv(GLES20.GL_FRAMEBUFFER_BINDING, params);
        final int nowFramebuffer = params[0];
        NativeLibrary.nativeGlGetIntegerv(GLES20.GL_RENDERBUFFER_BINDING, params);
        final int nowRenderbuffer = params[0];
        NativeLibrary.nativeGlGetIntegerv(GLES20.GL_TEXTURE_BINDING_2D, params);
        final int nowTexName = params[0];

        release();

        try
        {
            this.width = width;
            this.height = height;

            NativeLibrary.nativeGlGenFramebuffers(params);
            framebufferName = params[0];
            NativeLibrary.nativeGlBindFramebuffer(GLES20.GL_FRAMEBUFFER, framebufferName);

            NativeLibrary.nativeGlGenRenderbuffers(params);
            renderbufferName = params[0];
            NativeLibrary.nativeGlBindRenderbuffer(GLES20.GL_RENDERBUFFER, renderbufferName);
            NativeLibrary.nativeGlRenderbufferStorage(GLES20.GL_RENDERBUFFER, GLES20.GL_DEPTH_COMPONENT16, width, height);
            NativeLibrary.nativeGlFramebufferRenderbuffer(GLES20.GL_FRAMEBUFFER, GLES20.GL_DEPTH_ATTACHMENT, GLES20.GL_RENDERBUFFER, renderbufferName);

            NativeLibrary.nativeGlGenTextures(params);
            texName = params[0];
            NativeLibrary.nativeGlBindTexture(GLES20.GL_TEXTURE_2D, texName);

            NativeLibrary.nativeSetupSampler(GLES20.GL_TEXTURE_2D, GLES20.GL_LINEAR, GLES20.GL_NEAREST);

            NativeLibrary.nativeGlTexImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA, width, height, 0, GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, null);
            NativeLibrary.nativeGlFramebufferTexture2D(GLES20.GL_FRAMEBUFFER, GLES20.GL_COLOR_ATTACHMENT0, GLES20.GL_TEXTURE_2D, texName, 0);

            final int status = NativeLibrary.nativeGlCheckFramebufferStatus(GLES20.GL_FRAMEBUFFER);
            if (status != GLES20.GL_FRAMEBUFFER_COMPLETE)
            {
                throw new RuntimeException("Failed to initialize framebuffer object " + status);
            }
        }catch (final RuntimeException e)
        {
            release();
            throw e;
        }

        NativeLibrary.nativeGlBindFramebuffer(GLES20.GL_FRAMEBUFFER, nowFramebuffer);
        NativeLibrary.nativeGlBindRenderbuffer(GLES20.GL_RENDERBUFFER, nowRenderbuffer);
        NativeLibrary.nativeGlBindTexture(GLES20.GL_TEXTURE_2D, nowTexName);
    }

    public void release()
    {
        final int[] params = new int[1];
        params[0] = texName;
        NativeLibrary.nativeGlDeleteTextures(params);
        texName = 0;

        params[0] = renderbufferName;
        NativeLibrary.nativeGlDeleteRenderbuffers(params);
        renderbufferName = 0;

        params[0] = framebufferName;
        NativeLibrary.nativeGlDeleteFramebuffers(params);
        framebufferName = 0;

    }

    public void enable() { NativeLibrary.nativeGlBindFramebuffer(GLES20.GL_FRAMEBUFFER, framebufferName);}
}
