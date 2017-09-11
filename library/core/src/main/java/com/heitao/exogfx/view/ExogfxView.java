package com.heitao.exogfx.view;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.google.android.exoplayer2.SimpleExoPlayer;
import com.heitao.exogfx.core.ExogfxRenderer;
import com.heitao.exogfx.egl.DefaultEGLConfigChooser;
import com.heitao.exogfx.egl.DefaultEGLContextFactory;

/**
 * Created by showtime on 9/3/2017.
 */

public class ExogfxView extends GLSurfaceView implements SimpleExoPlayer.VideoListener {

    private final static String TAG = ExogfxView.class.getSimpleName();

    private ExogfxRenderer renderer;

    private SimpleExoPlayer player;

    private float videoAspect = 1.0f;

    private PlayerScaleType playerScaleType = PlayerScaleType.RESIZE_FIT_WIDTH;

    public ExogfxView(Context context) {
        this(context, null);
    }

    public ExogfxView(Context context, AttributeSet attrs) {
        super(context, attrs);

        setEGLContextFactory(new DefaultEGLContextFactory());
        setEGLConfigChooser(new DefaultEGLConfigChooser());

        renderer = new ExogfxRenderer(this);
        setRenderer(renderer);

        setRenderMode(RENDERMODE_WHEN_DIRTY);
    }

    public ExogfxView setSimpleExoPlayer(final SimpleExoPlayer player) {
        if (this.player != null) {
            this.player.removeVideoListener(this);
            this.player.release();
            this.player = null;
        }

        this.player = player;
        this.player.addVideoListener(this);
        this.renderer.setSimpleExoPlayer(player);

        return this;
    }

    public void setFilter() {

    }

    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);

        int measuredWidth = getMeasuredWidth();
        int measuredHeight = getMeasuredHeight();

        int viewWidth = measuredWidth;
        int viewHeight = measuredHeight;

        switch (playerScaleType) {
            case RESIZE_FIT_WIDTH: {
                viewHeight = (int) (measuredWidth / videoAspect);
                break;
            }
            case RESIZE_FIT_HEIGHT: {
                viewWidth = (int) (measuredHeight * videoAspect);
                break;
            }
        }

        setMeasuredDimension(viewWidth, viewHeight);
    }

    @Override
    public void onVideoSizeChanged(int width, int height, int unappliedRotationDegrees, float pixelWidthHeightRatio) {
        videoAspect = ((float) width / height) * pixelWidthHeightRatio;

        requestLayout();
    }

    @Override
    public void onRenderedFirstFrame() {

    }
}
