package com.heitao.exogfx.core;

import android.graphics.SurfaceTexture;

import com.heitao.exogfx.ogles.OGLES;

/**
 * Created by showtime on 9/5/2017.
 */

public class ExogfxVideoTexture {

    private SurfaceTexture surfaceTexture;

    private OnNewFrameListener onNewFrameListener;

    private int texName;

    private float[] stMatrix = new float[16];

    private boolean needUpdateTexture;

    private class UpdateSurfaceListener implements SurfaceTexture.OnFrameAvailableListener {
        @Override
        public void onFrameAvailable(SurfaceTexture surfaceTexture) {

            needUpdateTexture = true;

            if (onNewFrameListener != null) {
                onNewFrameListener.onNewFrame();
            }
        }
    }

    public interface OnNewFrameListener {
        void onNewFrame();
    }

    ExogfxVideoTexture() {

        int[] textures = new int[1];
        OGLES.glGenTextures(textures);
        texName = textures[0];

        surfaceTexture = new SurfaceTexture(texName);

        surfaceTexture.setOnFrameAvailableListener(new UpdateSurfaceListener());

    }

    void setOnNewFrameListener(OnNewFrameListener listener) {
        onNewFrameListener = listener;
    }

    synchronized void updateTexture() {
        if (needUpdateTexture) {
            if (surfaceTexture != null) {

                surfaceTexture.updateTexImage();
                surfaceTexture.getTransformMatrix(stMatrix);
            }

            needUpdateTexture = false;
        }
    }

    SurfaceTexture getSurfaceTexture() {
        return surfaceTexture;
    }

    int getTexName() {
        return texName;
    }

    float[] getStMatrix() {
        return stMatrix;
    }

    void release() {
        if (surfaceTexture != null) {
            surfaceTexture.release();
            surfaceTexture = null;
        }

    }

}
