package com.heitao.exogfx.core;

import android.opengl.GLES20;

import com.heitao.exogfx.ogles.OGLES;
import com.heitao.exogfx.ogles.OGLESUtil;

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

        OGLES.glGetIntegerv(GLES20.GL_MAX_TEXTURE_SIZE, params);

        if (width > params[0] || height > params[0])
        {
            throw new IllegalArgumentException("GL_MAX_TEXTURE_SIZE: " + params[0]);
        }

        OGLES.glGetIntegerv(GLES20.GL_MAX_RENDERBUFFER_SIZE, params);
        if (width > params[0] || height > params[0])
        {
            throw new IllegalArgumentException("GL_MAX_RENDERBUFFER_SIZE: " + params[0]);
        }

        OGLES.glGetIntegerv(GLES20.GL_FRAMEBUFFER_BINDING, params);
        final int currentFramebuffer = params[0];
        OGLES.glGetIntegerv(GLES20.GL_RENDERBUFFER_BINDING, params);
        final int currentRenderbuffer = params[0];
        OGLES.glGetIntegerv(GLES20.GL_TEXTURE_BINDING_2D, params);
        final int currentRenderTexName = params[0];

        release();

        try
        {
            this.width = width;
            this.height = height;

            OGLES.glGenFramebuffers(params);
            framebufferName = params[0];
            OGLES.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, framebufferName);

            OGLES.glGenRenderbuffers(params);
            renderbufferName = params[0];
            OGLES.glBindRenderbuffer(GLES20.GL_RENDERBUFFER, renderbufferName);
            OGLES.glRenderbufferStorage(GLES20.GL_RENDERBUFFER, GLES20.GL_DEPTH_COMPONENT16, width, height);
            OGLES.glFramebufferRenderbuffer(GLES20.GL_FRAMEBUFFER, GLES20.GL_DEPTH_ATTACHMENT, GLES20.GL_RENDERBUFFER, renderbufferName);

            OGLES.glGenTextures(params);
            texName = params[0];
            OGLES.glBindTexture(GLES20.GL_TEXTURE_2D, texName);

            OGLESUtil.setupSampler(GLES20.GL_TEXTURE_2D, GLES20.GL_LINEAR, GLES20.GL_NEAREST);

            OGLES.glTexImage2D(GLES20.GL_TEXTURE_2D, 0, GLES20.GL_RGBA, width, height, 0, GLES20.GL_RGBA, GLES20.GL_UNSIGNED_BYTE, null);
            OGLES.glFramebufferTexture2D(GLES20.GL_FRAMEBUFFER, GLES20.GL_COLOR_ATTACHMENT0, GLES20.GL_TEXTURE_2D, texName, 0);

            final int status = OGLES.glCheckFramebufferStatus(GLES20.GL_FRAMEBUFFER);
            if (status != GLES20.GL_FRAMEBUFFER_COMPLETE)
            {
                throw new RuntimeException("Failed to initialize framebuffer object " + status);
            }
        }catch (final RuntimeException e)
        {
            release();
            throw e;
        }

        OGLES.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, currentFramebuffer);
        OGLES.glBindRenderbuffer(GLES20.GL_RENDERBUFFER, currentRenderbuffer);
        OGLES.glBindTexture(GLES20.GL_TEXTURE_2D, currentRenderTexName);
    }

    public void release()
    {
        final int[] params = new int[1];
        params[0] = texName;
        OGLES.glDeleteTextures(params);
        texName = 0;

        params[0] = renderbufferName;
        OGLES.glDeleteRenderbuffers(params);
        renderbufferName = 0;

        params[0] = framebufferName;
        OGLES.glDeleteFramebuffers(params);
        framebufferName = 0;

    }

    public void enable() { OGLES.glBindFramebuffer(GLES20.GL_FRAMEBUFFER, framebufferName);}
}
