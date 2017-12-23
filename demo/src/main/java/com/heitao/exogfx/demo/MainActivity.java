package com.heitao.exogfx.demo;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.view.ViewGroup;
import android.widget.RelativeLayout;

import com.heitao.exogfx.view.ExogfxView;

public class MainActivity extends Activity {

    private static String TAG = MainActivity.class.getSimpleName();

    protected ExogfxView exogfxView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        initializeExogfxView();
    }
    @Override
    protected void onNewIntent(Intent intent) {

        setIntent(intent);
    }
    @Override
    protected void onDestroy()
    {
        releaseExogfxView();

        super.onDestroy();
    }
    @Override
    protected void onPause() {
        super.onPause();

        exogfxView.pauseRendering();
    }

    @Override
    protected void onResume() {
        super.onResume();

        exogfxView.resumeRendering();
    }

    private void initializeExogfxView() {

        exogfxView = new ExogfxView(getApplicationContext());
        exogfxView.setLayoutParams(new RelativeLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT));
        ((ScreenWrapperView) findViewById(R.id.layout_movie_wrapper)).addView(exogfxView);
        exogfxView.loadVideo(Uri.parse(Constants.STREAM_URL_MP4_VOD_LONG));
    }

    private void releaseExogfxView()
    {
        ((ScreenWrapperView) findViewById(R.id.layout_movie_wrapper)).removeAllViews();
        exogfxView.release();
        exogfxView = null;
    }
}
