package com.heitao.exogfx.view;

import android.content.Context;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.google.android.exoplayer2.SimpleExoPlayer;
import com.heitao.exogfx.core.ExogfxVideoPlayer;
import com.heitao.exogfx.core.ExogfxVideoRenderer;
import com.heitao.exogfx.core.GLThreadScheduler;
import com.heitao.exogfx.egl.DefaultEGLConfigChooser;
import com.heitao.exogfx.egl.DefaultEGLContextFactory;

/**
 * Created by showtime on 9/3/2017.
 */

public class ExogfxView extends GLSurfaceView{

    public enum PlayerScaleType {
        RESIZE_FIT_WIDTH,
        RESIZE_FIT_HEIGHT,
        RESIZE_NONE
    }

    private final static String TAG = ExogfxView.class.getSimpleName();

    private float videoAspect = 1f;

    private PlayerScaleType playerScaleType = PlayerScaleType.RESIZE_FIT_WIDTH;

    private ExogfxVideoRenderer renderer;

    private ExogfxVideoPlayer player;

    private GLThreadScheduler scheduler;

    public ExogfxView(Context context) {
        this(context, null);


    }

    public ExogfxView(Context context, AttributeSet attrs) {
        super(context, attrs);

        scheduler = new GLThreadScheduler() {
            @Override
            public void queueGlThreadEvent(Runnable runnable) {
                queueEvent(runnable);
            }
        };

        initializeVideoPlayer(context);

        initializeVideoRenderer(context);

        renderer.bindPlayer(player);
    }

    private void initializeVideoRenderer(Context context)
    {
        setEGLContextFactory(new DefaultEGLContextFactory());
        setEGLConfigChooser(new DefaultEGLConfigChooser());

        renderer = new ExogfxVideoRenderer(context);
        setRenderer(renderer);
    }

    private void initializeVideoPlayer(Context context) {

        player = new ExogfxVideoPlayer(context);
        player.getExoPlayer().addVideoListener(new SimpleExoPlayer.VideoListener() {
            @Override
            public void onVideoSizeChanged(int width, int height, int unappliedRotationDegrees, float pixelWidthHeightRatio) {
                videoAspect = ((float) width / height) * pixelWidthHeightRatio;
                requestLayout();
            }

            @Override
            public void onRenderedFirstFrame() {

            }
        });
    }

    public void loadVideo(Uri uri)
    {
        player.openUri(uri);
    }

    public void pauseRendering()
    {
        onPause();

        player.onPause();
        renderer.onPause();
    }

    public void resumeRendering()
    {
        onResume();

        player.onResume();
        renderer.onResume();
    }

    public void release()
    {
        player.onPause();
        player.release();

        renderer.onPause();
        renderer.release();
    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

        int measuredWidth = getMeasuredWidth();
        int measuredHeight = getMeasuredHeight();

        int viewWidth = measuredWidth;
        int viewHeight = measuredHeight;

        switch (playerScaleType) {
            case RESIZE_FIT_WIDTH:
                viewHeight = (int) (measuredWidth / videoAspect);
                break;
            case RESIZE_FIT_HEIGHT:
                viewWidth = (int) (measuredHeight * videoAspect);
                break;
        }

        setMeasuredDimension(viewWidth, viewHeight);
    }

    @Override
    protected void onDetachedFromWindow()
    {
        super.onDetachedFromWindow();
    }
}
