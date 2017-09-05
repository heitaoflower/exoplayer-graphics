package com.heitao.exogfx.core;

import android.graphics.SurfaceTexture;

/**
 * Created by showtime on 9/5/2017.
 */

public class ExogfxSurfaceTexture implements SurfaceTexture.OnFrameAvailableListener {

    private static final int GL_TEXTURE_EXTERNAL_OES = 0x8D65;

    private SurfaceTexture surfaceTexture;
    private SurfaceTexture.OnFrameAvailableListener onFrameAvailableListener;

    ExogfxSurfaceTexture(final int texName)
    {
        surfaceTexture = new SurfaceTexture(texName);
        surfaceTexture.setOnFrameAvailableListener(this);
    }

    void setOnFrameAvailableListener(final SurfaceTexture.OnFrameAvailableListener listener)
    {
        onFrameAvailableListener = listener;
    }

    int getTextureTarget()
    {
        return GL_TEXTURE_EXTERNAL_OES;
    }

    void updateTexImage()
    {
        surfaceTexture.updateTexImage();
    }

    void getTransformMatrix(final float[] mtx)
    {
        surfaceTexture.getTransformMatrix(mtx);
    }

    SurfaceTexture getSurfaceTexture()
    {
        return surfaceTexture;
    }

    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {
        if (onFrameAvailableListener != null)
        {
            onFrameAvailableListener.onFrameAvailable(this.surfaceTexture);
        }
    }

    public void release()
    {
        surfaceTexture.release();
    }

}
