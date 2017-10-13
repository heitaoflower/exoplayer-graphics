package com.heitao.exogfx.core;

import android.content.Context;
import android.os.Handler;

import com.google.android.exoplayer2.decoder.DecoderInputBuffer;
import com.google.android.exoplayer2.drm.DrmSessionManager;
import com.google.android.exoplayer2.drm.FrameworkMediaCrypto;
import com.google.android.exoplayer2.mediacodec.MediaCodecSelector;
import com.google.android.exoplayer2.video.MediaCodecVideoRenderer;
import com.google.android.exoplayer2.video.VideoRendererEventListener;

/**
 * Created by showtime on 10/11/2017.
 */

public class ExogfxCodecVideoRenderer extends MediaCodecVideoRenderer {

    public ExogfxCodecVideoRenderer(Context context, MediaCodecSelector mediaCodecSelector) {
        super(context, mediaCodecSelector);
    }

    public ExogfxCodecVideoRenderer(Context context, MediaCodecSelector mediaCodecSelector, long allowedJoiningTimeMs) {
        super(context, mediaCodecSelector, allowedJoiningTimeMs);
    }

    public ExogfxCodecVideoRenderer(Context context, MediaCodecSelector mediaCodecSelector,
                                        long allowedJoiningTimeMs, DrmSessionManager<FrameworkMediaCrypto> drmSessionManager,
                                        boolean playClearSamplesWithoutKeys, Handler eventHandler,
                                        VideoRendererEventListener eventListener, int maxDroppedFramesToNotify) {
        super(context, mediaCodecSelector, allowedJoiningTimeMs, drmSessionManager, playClearSamplesWithoutKeys, eventHandler, eventListener, maxDroppedFramesToNotify);
    }

    @Override
    protected void onQueueInputBuffer(DecoderInputBuffer buffer) {

        byte[] data = new byte[20];

        buffer.data.get(data);

        super.onQueueInputBuffer(buffer);
    }
}
