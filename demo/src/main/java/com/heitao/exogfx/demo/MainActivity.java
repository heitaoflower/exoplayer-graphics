package com.heitao.exogfx.demo;

import android.app.Activity;
import android.os.Bundle;

import com.heitao.exogfx.core.NativeLibrary;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        NativeLibrary.init();
    }
}
