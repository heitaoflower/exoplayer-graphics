package com.heitao.exogfx.view;

import android.content.Context;
import android.net.Uri;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;

import com.heitao.exogfx.core.ExogfxVideoPlayer;
import com.heitao.exogfx.core.ExogfxVideoRenderer;
import com.heitao.exogfx.core.GLThreadScheduler;
import com.heitao.exogfx.egl.DefaultEGLConfigChooser;
import com.heitao.exogfx.egl.DefaultEGLContextFactory;

/**
 * Created by showtime on 9/3/2017.
 */

public class ExogfxView extends GLSurfaceView {

    private final static String TAG = ExogfxView.class.getSimpleName();

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

        initializeRendering();

        initializeExoPlayer(context);

        renderer.bindPlayer(player);
    }

    private void initializeRendering()
    {
        setEGLContextFactory(new DefaultEGLContextFactory());
        setEGLConfigChooser(new DefaultEGLConfigChooser());

        renderer = new ExogfxVideoRenderer();
        setRenderer(renderer);
    }

    private void initializeExoPlayer(Context context) {

        player = new ExogfxVideoPlayer(context);
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
    }

    @Override
    protected void onDetachedFromWindow()
    {
        super.onDetachedFromWindow();
    }
}
