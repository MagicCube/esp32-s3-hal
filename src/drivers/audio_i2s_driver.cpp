#include "audio_i2s_driver.h"

#include <Arduino.h>
#include <ESP_I2S.h>

#include "audio_conf.h"
#include "pin_conf.h"

I2SClass *audio_out_init() {
  i2s_data_bit_width_t data_bit_width = I2S_DATA_BIT_WIDTH_16BIT;
  if (AUDIO_OUT_BIT_DEPTH == 8) {
    data_bit_width = I2S_DATA_BIT_WIDTH_8BIT;
  } else if (AUDIO_OUT_BIT_DEPTH == 16) {
    data_bit_width = I2S_DATA_BIT_WIDTH_16BIT;
  } else if (AUDIO_OUT_BIT_DEPTH == 24) {
    data_bit_width = I2S_DATA_BIT_WIDTH_24BIT;
  } else {
    data_bit_width = I2S_DATA_BIT_WIDTH_32BIT;
  }

  i2s_slot_mode_t slot_mode = I2S_SLOT_MODE_MONO;
  if (AUDIO_OUT_CHANNELS != 1) {
    slot_mode = I2S_SLOT_MODE_STEREO;
  }

  I2SClass *i2s = new I2SClass();
  i2s->setPins(SPEAKER_I2S_BCK, SPEAKER_I2S_WS, SPEAKER_I2S_DO);
  i2s->begin(I2S_MODE_STD, AUDIO_OUT_SAMPLE_RATE, data_bit_width, slot_mode,
             slot_mode == I2S_SLOT_MODE_STEREO ? I2S_STD_SLOT_BOTH
                                               : I2S_STD_SLOT_LEFT);
  return i2s;
}

I2SClass *audio_in_init() {
  i2s_data_bit_width_t data_bit_width = I2S_DATA_BIT_WIDTH_16BIT;
  if (AUDIO_IN_BIT_DEPTH == 8) {
    data_bit_width = I2S_DATA_BIT_WIDTH_8BIT;
  } else if (AUDIO_IN_BIT_DEPTH == 16) {
    data_bit_width = I2S_DATA_BIT_WIDTH_16BIT;
  } else if (AUDIO_IN_BIT_DEPTH == 24) {
    data_bit_width = I2S_DATA_BIT_WIDTH_24BIT;
  } else {
    data_bit_width = I2S_DATA_BIT_WIDTH_32BIT;
  }

  i2s_slot_mode_t slot_mode = I2S_SLOT_MODE_MONO;
  if (AUDIO_IN_CHANNELS != 1) {
    slot_mode = I2S_SLOT_MODE_STEREO;
  }

  I2SClass *i2s = new I2SClass();
  i2s->setPins(MIC_I2S_SCK, MIC_I2S_WS, -1, MIC_I2S_SD);
  i2s->begin(I2S_MODE_STD, AUDIO_IN_SAMPLE_RATE, data_bit_width, slot_mode,
             slot_mode == I2S_SLOT_MODE_STEREO ? I2S_STD_SLOT_BOTH
                                               : I2S_STD_SLOT_LEFT);
  return i2s;
}
