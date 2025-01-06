#pragma once

#include <Arduino.h>
#include <ESP_I2S.h>

#include "audio_conf.h"
#include "notes.h"

enum SystemSound {
  SYSTEM_SOUND_HIGHER_BEEP,
  SYSTEM_SOUND_LOWER_BEEP,
  SYSTEM_SOUND_DOUBLE_BEEP,
  SYSTEM_SOUND_STARTUP,
};

class I2SAudio {
 public:
  void begin();

  void mute() const;

  void unmute() const;

  inline I2SClass* out() { return _out; }
  inline I2SClass* in() { return _in; }

  inline size_t write(uint8_t* data, size_t length) const;
  inline size_t read(int16_t* data, size_t length) const;

  void buzz(const float_t frequency, const float_t duration,
            const uint8_t volume = 100) const;

  void playSystemSound(const SystemSound sound, const uint8_t volume = 5) const;

 private:
  I2SClass* _out;
  I2SClass* _in;
};

extern I2SAudio Audio;
