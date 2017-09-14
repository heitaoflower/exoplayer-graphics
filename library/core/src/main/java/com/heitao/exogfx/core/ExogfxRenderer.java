package com.heitao.exogfx.core;

import android.graphics.SurfaceTexture;
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

    private ExogfxSurfaceTexture videoTexture;

    private boolean updateSurface = false;

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

        videoTexture = new ExogfxSurfaceTexture(texName);
        videoTexture.setOnFrameAvailableListener(this);

        Surface surface = new Surface(videoTexture.getSurfaceTexture());

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
                videoTexture.updateTexImage();
                videoTexture.getTransformMatrix(stMatrix);
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
