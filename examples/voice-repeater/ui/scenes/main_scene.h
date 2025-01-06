#pragma once

#include <mx.h>

class AudioRecorder;

LV_IMAGE_DECLARE(img_microphone);

static lv_style_t bigRingPressedStyle;
static lv_style_t midRingPressedStyle;

class MainScene : public MXScene {
 private:
  MXObject* _titleLabel = nullptr;
  MXObject* _instructionLabel = nullptr;
  MXObject* _speakButton = nullptr;
  MXObject* _bigRing = nullptr;
  MXObject* _midRing = nullptr;

  AudioRecorder* _audioRecorder = nullptr;

  void _init_pressed_style(lv_style_t* style, int32_t size);
  void _handleSpeakButtonPressed();
  void _handleSpeakButtonReleased();

 public:
  void onInit() override;
  void onUpdate() override;
  void dispose() override;
};
