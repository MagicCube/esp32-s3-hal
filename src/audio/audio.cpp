#include "audio.h"

#include "drivers/audio_i2s_driver.h"
#include "pin_conf.h"

I2SAudio Audio;

void I2SAudio::begin() {
#if defined(SPEAKER_MUTE_PIN)
  pinMode(SPEAKER_MUTE_PIN, OUTPUT);
#endif
  _out = audio_out_init();
  _in = audio_in_init();
  unmute();
}

void I2SAudio::mute() const {
#if defined(SPEAKER_MUTE_PIN)
  digitalWrite(SPEAKER_MUTE_PIN, LOW);
#endif
}

void I2SAudio::unmute() const {
#if defined(SPEAKER_MUTE_PIN)
  digitalWrite(SPEAKER_MUTE_PIN, HIGH);
#endif
}

const float_t MAX_AMPLITUDE = 32767;
void I2SAudio::buzz(const float_t frequency, const float_t duration,
                    const uint8_t volume) const {
  int16_t amplitude = (MAX_AMPLITUDE * volume) / 100;
  uint32_t totalSamples = AUDIO_OUT_SAMPLE_RATE * duration;
  float_t angularFrequency = 2.0f * M_PI * frequency / AUDIO_OUT_SAMPLE_RATE;
  int16_t* buffer = new int16_t[totalSamples];
  for (uint32_t i = 0; i < totalSamples; i++) {
    buffer[i] = amplitude * sin(angularFrequency * i);
  }
  _out->write(reinterpret_cast<uint8_t*>(buffer),
              totalSamples * sizeof(int16_t));
  delete[] buffer;
}

void I2SAudio::playSystemSound(const SystemSound sound,
                               const uint8_t volume) const {
  switch (sound) {
    case SYSTEM_SOUND_HIGHER_BEEP:
      buzz(NOTE_MI * 7, 0.05, volume);
      break;

    case SYSTEM_SOUND_LOWER_BEEP:
      buzz(NOTE_DO * 7, 0.05, volume);
      break;

    case SYSTEM_SOUND_DOUBLE_BEEP:
      buzz(NOTE_MI * 7, 0.05, volume);
      delay(50);
      buzz(NOTE_MI * 7, 0.05, volume);
      break;

    case SYSTEM_SOUND_STARTUP:
      buzz(NOTE_MI * 7, 0.1, volume);
      buzz(NOTE_DO * 7, 0.1, volume);
      buzz(NOTE_RE * 7, 0.1, volume);
      buzz(NOTE_SO * 7, 0.1, volume);
      break;

    default:
      break;
  }
}
