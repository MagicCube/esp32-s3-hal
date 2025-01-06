#pragma once

#include <mx.h>

class AudioRecorder;

class MainScene : public MXScene {
 protected:
  MXObject* titleLabel = nullptr;
  MXObject* instructionLabel = nullptr;
  MXObject* speakButton = nullptr;
  MXObject* bigRing = nullptr;
  MXObject* midRing = nullptr;
  AudioRecorder* audioRecorder = nullptr;

  void onInit() override;
  void onUpdate() override;
  void onDispose() override;

  void init_pressed_style(lv_style_t* style, int32_t size);
  void handleSpeakButtonPressed();
  void handleSpeakButtonReleased();
};
