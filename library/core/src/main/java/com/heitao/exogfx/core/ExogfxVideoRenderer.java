package com.heitao.exogfx.core;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.view.Surface;

import com.google.android.exoplayer2.SimpleExoPlayer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

/**
 * Created by showtime on 9/5/2017.
 */

public class ExogfxVideoRenderer implements GLSurfaceView.Renderer {

    private static final String TAG = ExogfxVideoRenderer.class.getSimpleName();

    private long nativeRenderer;

    private ExogfxVideoTexture videoTexture;

    private SimpleExoPlayer videoPlayer;

    public ExogfxVideoRenderer(Context context)
    {
        NativeLibrary.nativeInitializeContext(context, getClass().getClassLoader());

        nativeRenderer = NativeLibrary.nativeCreateRenderer();

    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {

        videoTexture = new ExogfxVideoTexture();

        Surface surface = new Surface(videoTexture.getSurfaceTexture());

        videoPlayer.setVideoSurface(surface);

        videoTexture.setOnNewFrameListener(new ExogfxVideoTexture.OnNewFrameListener() {
            @Override
            public void onNewFrame() {

            }
        });

        NativeLibrary.nativeOnSurfaceCreated(nativeRenderer, videoTexture.getTexName());

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {

        NativeLibrary.nativeOnSurfaceChanged(nativeRenderer, width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {

        videoTexture.updateTexture();

        NativeLibrary.nativeDrawFrame(nativeRenderer, videoTexture.getTexName(), videoTexture.getStMatrix());
    }

    public void bindPlayer(ExogfxVideoPlayer videoPlayer)
    {
        this.videoPlayer = videoPlayer.getExoPlayer();
    }

    public void onPause() {

        if (videoPlayer != null)
        {
            videoPlayer.clearVideoSurface();
        }

        if (videoTexture != null) {
            videoTexture.release();
        }

        NativeLibrary.nativeOnPause(nativeRenderer);
    }

    public void onResume()
    {
        NativeLibrary.nativeOnResume(nativeRenderer);
    }

    public void release()
    {
        NativeLibrary.nativeDestroyRenderer(nativeRenderer);
    }

}
