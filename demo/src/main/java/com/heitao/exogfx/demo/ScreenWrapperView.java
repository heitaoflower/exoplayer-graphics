package com.heitao.exogfx.demo;

import android.content.Context;
import android.support.annotation.AttrRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.AttributeSet;
import android.widget.FrameLayout;

/**
 * Created by showtime on 9/4/2017.
 */

public class ScreenWrapperView extends FrameLayout {

    public ScreenWrapperView(@NonNull Context context) {
        super(context);
    }

    public ScreenWrapperView(@NonNull Context context, @Nullable AttributeSet attrs) {
        super(context, attrs);
    }

    public ScreenWrapperView(@NonNull Context context, @Nullable AttributeSet attrs, @AttrRes int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

}
