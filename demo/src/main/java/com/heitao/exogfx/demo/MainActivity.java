package com.heitao.exogfx.demo;

import android.app.Activity;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.SeekBar;

import com.google.android.exoplayer2.ExoPlayerFactory;
import com.google.android.exoplayer2.SimpleExoPlayer;
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

public class MainActivity extends Activity {

    private static String TAG = MainActivity.class.getSimpleName();

    protected ExogfxView exogfxView;

    private SimpleExoPlayer player;

    private Button button;

    private SeekBar seekBar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        addUIViews();
    }

    @Override
    protected void onStart()
    {
        super.onStart();
    }

    @Override
    protected void onStop()
    {
        super.onStop();
    }

    @Override
    protected void onPause() {
        super.onPause();

        releaseExogfxView();
        releasePlayer();
    }

    @Override
    protected void onResume() {
        super.onResume();

        initializeExoPlayer();
        initializeExogfxView();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }
    private void addUIViews() {
        button = (Button) findViewById(R.id.btn);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                if (player == null) {
                    return;
                }

                if (button.getText().toString().equals("pause")) {
                    player.setPlayWhenReady(false);
                    button.setText(R.string.play);
                } else {
                    player.setPlayWhenReady(true);
                    button.setText(R.string.pause);
                }
            }
        });

        // seekBar
        seekBar = (SeekBar) findViewById(R.id.seekBar);
        seekBar.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if (player == null) {
                    return;
                }

                if (!fromUser) {
                    return;
                }

                player.seekTo(progress * 1000);
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });

        // ListView
        ListView listView = (ListView) findViewById(R.id.list);
    }

    private void initializeExoPlayer() {
        BandwidthMeter bandwidthMeter = new DefaultBandwidthMeter();
        TrackSelection.Factory videoTrackSelectionFactory = new AdaptiveTrackSelection.Factory(bandwidthMeter);
        TrackSelector trackSelector = new DefaultTrackSelector(videoTrackSelectionFactory);

        // Measures bandwidth during playback. Can be null if not required.
        DefaultBandwidthMeter defaultBandwidthMeter = new DefaultBandwidthMeter();
        // Produces DataSource instances through which media data is loaded.
        DataSource.Factory dataSourceFactory = new DefaultDataSourceFactory(this, Util.getUserAgent(this, "yourApplicationName"), defaultBandwidthMeter);
        // Produces Extractor instances for parsing the media data.
        ExtractorsFactory extractorsFactory = new DefaultExtractorsFactory();
        // This is the MediaSource representing the media to be played.
        MediaSource videoSource = new ExtractorMediaSource(Uri.parse(Constants.STREAM_URL_MP4_VOD_LONG), dataSourceFactory, extractorsFactory, null, null);

        // SimpleExoPlayer
        player = ExoPlayerFactory.newSimpleInstance(this, trackSelector);
        // Prepare the player with the source.
        player.prepare(videoSource);
        player.setPlayWhenReady(true);
    }

    private void initializeExogfxView() {

        exogfxView = new ExogfxView(this);
        exogfxView.setSimpleExoPlayer(player);
        exogfxView.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        ((ScreenWrapperView) findViewById(R.id.layout_movie_wrapper)).addView(exogfxView);
        exogfxView.onResume();
    }

    private void releaseExogfxView()
    {
        exogfxView.onPause();
        ((ScreenWrapperView) findViewById(R.id.layout_movie_wrapper)).removeAllViews();
        exogfxView = null;
    }

    private void releasePlayer() {

        player.stop();
        player.release();
        player = null;
    }
}
