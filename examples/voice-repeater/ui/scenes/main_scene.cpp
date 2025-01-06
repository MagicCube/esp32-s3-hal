#include "main_scene.h"

#include <audio.h>

#include "../../core/audio_recorder.h"

#define BUTTON_BG_COLOR rgb(0xFF2C55)
#define SCENE_BG_COLOR rgb(0x000000)

const char* INSTRUCTION_TEXT =
    "Press and hold to record.\nRelease to stop and play.";

void MainScene::onInit() {
  MXScene::onInit();

  _audioRecorder = new AudioRecorder();

  root()->bg(SCENE_BG_COLOR).scrollable(false);

  _titleLabel =
      &root()->label("VoiceRepeater", MX_FONT_SIZE_XL).center_x(0, 46);
  _instructionLabel = &root()
                           ->label()
                           .text(INSTRUCTION_TEXT)
                           .text(MX_FONT_SIZE_SM)
                           .text_secondary()
                           .text_center()
                           .center_x(0, 82);

  _bigRing = &root()
                  ->object()
                  .size(256)
                  .center(0, 96)
                  .bg(BUTTON_BG_COLOR, 0.15)
                  .rounded_full()
                  .clickable(false);
  _midRing = &_bigRing->object()
                  .size(200)
                  .center()
                  .bg(BUTTON_BG_COLOR, 0.15)
                  .rounded_full()
                  .clickable(false);
  _speakButton =
      &_bigRing->button()
           .size(144)
           .center()
           .bg(BUTTON_BG_COLOR)
           .rounded_full()
           .onClick([](MXEvent* e) { Serial.println("Clicked"); })
           .onPressed([this](MXEvent* e) { this->_handleSpeakButtonPressed(); })
           .onReleased(
               [this](MXEvent* e) { this->_handleSpeakButtonReleased(); });
  _speakButton->image(&img_microphone).center(0).clickable(false);

  _init_pressed_style(&bigRingPressedStyle, 40);
  _init_pressed_style(&midRingPressedStyle, 16);
}

void MainScene::_init_pressed_style(lv_style_t* style, int32_t size) {
  lv_style_init(style);
  lv_style_set_transform_width(style, size);
  lv_style_set_transform_height(style, size);
}

void MainScene::onUpdate() {
  MXScene::onUpdate();
  _audioRecorder->update();
}

void MainScene::dispose() {
  MXScene::dispose();

  delete _titleLabel;
  _titleLabel = nullptr;
  delete _instructionLabel;
  _instructionLabel = nullptr;
  delete _bigRing;
  _bigRing = nullptr;
  delete _midRing;
  _midRing = nullptr;
  delete _speakButton;
  _speakButton = nullptr;
  delete _audioRecorder;
  _audioRecorder = nullptr;
}

void MainScene::_handleSpeakButtonPressed() {
  _instructionLabel->text(
      "Recording...\n"
      "Release to stop and play.");

  _bigRing->add_style(&bigRingPressedStyle);
  _midRing->add_style(&midRingPressedStyle);

  Audio.playSystemSound(SYSTEM_SOUND_HIGHER_BEEP);
  _audioRecorder->record();
}

void MainScene::_handleSpeakButtonReleased() {
  _instructionLabel->text(INSTRUCTION_TEXT);

  _bigRing->remove_style(&bigRingPressedStyle);
  _midRing->remove_style(&midRingPressedStyle);

  Audio.playSystemSound(SYSTEM_SOUND_LOWER_BEEP);
  _audioRecorder->play();
  Audio.playSystemSound(SYSTEM_SOUND_LOWER_BEEP);
}
