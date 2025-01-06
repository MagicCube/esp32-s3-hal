#pragma once

#include <mx.h>

class AudioRecorder;

class MainScene : public MXScene {
 public:
  void onInit() override;
  void onUpdate() override;
  void dispose() override;

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
};
