package com.heitao.exogfx.core;

import android.content.Context;
import android.net.Uri;

import com.google.android.exoplayer2.ExoPlayerFactory;
import com.google.android.exoplayer2.SimpleExoPlayer;
import com.google.android.exoplayer2.SimpleExoPlayer.VideoListener;
import com.google.android.exoplayer2.extractor.DefaultExtractorsFactory;
import com.google.android.exoplayer2.extractor.ExtractorsFactory;
import com.google.android.exoplayer2.source.ExtractorMediaSource;
import com.google.android.exoplayer2.source.MediaSource;
import com.google.android.exoplayer2.trackselection.AdaptiveTrackSelection;
import com.google.android.exoplayer2.trackselection.DefaultTrackSelector;
import com.google.android.exoplayer2.trackselection.TrackSelection;
import com.google.android.exoplayer2.trackselection.TrackSelector;
import com.google.android.exoplayer2.upstream.BandwidthMeter;
import com.google.android.exoplayer2.upstream.DataSource;
import com.google.android.exoplayer2.upstream.DefaultBandwidthMeter;
import com.google.android.exoplayer2.upstream.DefaultDataSourceFactory;
import com.google.android.exoplayer2.util.Util;
import com.heitao.exogfx.view.ExogfxView;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by showtime on 9/14/2017.
 */

public class ExogfxVideoPlayer implements SimpleExoPlayer.VideoListener  {

    private SimpleExoPlayer exoPlayer;

    private DataSource.Factory dataSourceFactory;
    private ExtractorsFactory extractorsFactory;

    private List<VideoListener> videoListeners = null;

    public ExogfxVideoPlayer(Context context)
    {
        videoListeners = new ArrayList<>();

        initializeExoPlayer(context);
    }

    private void initializeExoPlayer(Context context) {

        BandwidthMeter bandwidthMeter = new DefaultBandwidthMeter();
        TrackSelection.Factory videoTrackSelectionFactory = new AdaptiveTrackSelection.Factory(bandwidthMeter);
        TrackSelector trackSelector = new DefaultTrackSelector(videoTrackSelectionFactory);

        DefaultBandwidthMeter defaultBandwidthMeter = new DefaultBandwidthMeter();

        dataSourceFactory = new DefaultDataSourceFactory(context, Util.getUserAgent(context, ExogfxView.class.getSimpleName()), defaultBandwidthMeter);
        extractorsFactory = new DefaultExtractorsFactory();

        exoPlayer = ExoPlayerFactory.newSimpleInstance(new ExogfxRenderersFactory(context), trackSelector);
        exoPlayer.setPlayWhenReady(true);
        exoPlayer.addVideoListener(this);
    }

    public void openUri(final Uri uri)
    {
        MediaSource mediaSource = buildMediaSource(uri);

        exoPlayer.prepare(mediaSource);
    }

    public void onPause()
    {
        exoPlayer.setPlayWhenReady(false);
    }

    public void onResume()
    {
        exoPlayer.setPlayWhenReady(true);
    }

    public void release()
    {
        exoPlayer.removeVideoListener(this);
        exoPlayer.stop();
        exoPlayer.release();
    }

    public SimpleExoPlayer getExoPlayer()
    {
        return exoPlayer;
    }

    @Override
    public void onVideoSizeChanged(int width, int height, int unappliedRotationDegrees, float pixelWidthHeightRatio) {

        for (final VideoListener listener : ExogfxVideoPlayer.this.videoListeners) {
            listener.onVideoSizeChanged(width, height, unappliedRotationDegrees, pixelWidthHeightRatio);
        }
    }

    @Override
    public void onRenderedFirstFrame() {
        for (final VideoListener listener : ExogfxVideoPlayer.this.videoListeners) {
            listener.onRenderedFirstFrame();
        }
    }

    public void registerVideoListener(final VideoListener listener)
    {
        videoListeners.add(listener);
    }

    public void unregisterVideoListener(final VideoListener listener)
    {
        videoListeners.remove(listener);
    }

    public synchronized MediaSource buildMediaSource(final Uri uri)
    {
        return new ExtractorMediaSource(uri, dataSourceFactory, extractorsFactory, null, null);
    }

}
