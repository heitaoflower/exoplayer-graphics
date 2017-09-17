package com.heitao.exogfx.core;

/**
 * Created by showtime on 9/15/2017.
 */

public interface GLThreadScheduler {

    void queueGlThreadEvent(Runnable runnable);
}
