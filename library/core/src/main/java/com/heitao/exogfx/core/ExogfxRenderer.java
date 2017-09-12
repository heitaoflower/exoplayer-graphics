package com.heitao.exogfx.core;

import android.graphics.SurfaceTexture;
import android.util.Log;
import android.view.Surface;

import com.google.android.exoplayer2.SimpleExoPlayer;
import com.heitao.exogfx.ogles.OGLES;
import com.heitao.exogfx.view.ExogfxView;

import javax.microedition.khronos.egl.EGLConfig;

/**
 * Created by showtime on 9/7/2017.
 */

public class ExogfxRenderer extends ExogfxFramebufferObjectRenderer implements SurfaceTexture.OnFrameAvailableListener {

    private static final String TAG = ExogfxRenderer.class.getSimpleName();

    private ExogfxSurfaceTexture previewTexture;

    private boolean updateSurface = false;

    private int texName;

    private float[] stMatrix = new float[16];

    private ExogfxView exogfxView;

    private SimpleExoPlayer simpleExoPlayer;

    public ExogfxRenderer(ExogfxView exogfxView)
    {
        super();
        this.exogfxView = exogfxView;
    }

    @Override
    public void onSurfaceCreated(EGLConfig config) {

        int[] textures = new int[1];
        OGLES.glGenTextures(textures);
        texName = textures[0];

        previewTexture = new ExogfxSurfaceTexture(texName);
        previewTexture.setOnFrameAvailableListener(this);

        Surface surface = new Surface(previewTexture.getSurfaceTexture());

        simpleExoPlayer.setVideoSurface(surface);
    }

    @Override
    public void onSurfaceChanged( int width, int height) {

    }

    @Override
    public void onDrawFrame() {

        synchronized (this)
        {
            if (updateSurface)
            {
                previewTexture.updateTexImage();
                previewTexture.getTransformMatrix(stMatrix);
                updateSurface = false;
            }
        }
    }

    @Override
    public void onFrameAvailable(SurfaceTexture surfaceTexture) {

        updateSurface = true;

        exogfxView.requestRender();
    }

    public void setSimpleExoPlayer(SimpleExoPlayer simpleExoPlayer) {
        this.simpleExoPlayer = simpleExoPlayer;
    }
}
