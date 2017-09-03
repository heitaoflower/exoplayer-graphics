package com.heitao.exogfx.demo;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;

import com.heitao.exogfx.core.NativeLibrary;
import com.heitao.exogfx.view.ExogfxView;

public class MainActivity extends Activity {

    private static String TAG = MainActivity.class.getSimpleName();

    protected ExogfxView graphicsView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Log.i(TAG, "Create New Demo View");
        graphicsView = new ExogfxView(getApplication());
        setContentView(graphicsView);
    }

    @Override
    protected void onPause() {
        super.onPause();

        graphicsView.onPause();
    }

    @Override
    protected void onResume() {
        super.onResume();

        graphicsView.onResume();
    }
}
