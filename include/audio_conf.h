#pragma once

// e.g. Microphone
#define AUDIO_IN_CHANNELS 1
#define AUDIO_IN_SAMPLE_RATE 8000
#define AUDIO_IN_BIT_DEPTH 16
#define AUDIO_IN_FPS 25
#define AUDIO_IN_FRAME_SIZE \
  AUDIO_IN_SAMPLE_RATE* AUDIO_IN_CHANNELS* AUDIO_IN_BIT_DEPTH / 8 / AUDIO_IN_FPS

// e.g. Speaker
#define AUDIO_OUT_CHANNELS AUDIO_IN_CHANNELS
#define AUDIO_OUT_SAMPLE_RATE AUDIO_IN_SAMPLE_RATE
#define AUDIO_OUT_BIT_DEPTH AUDIO_IN_BIT_DEPTH
#define AUDIO_OUT_FPS AUDIO_IN_FPS
#define AUDIO_OUT_FRAME_SIZE                                           \
  AUDIO_OUT_SAMPLE_RATE* AUDIO_OUT_CHANNELS* AUDIO_OUT_BIT_DEPTH / 8 / \
      AUDIO_OUT_FPS
