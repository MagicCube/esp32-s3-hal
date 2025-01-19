#include "main_scene.h"

#include <audio.h>

#include "../../core/audio_recorder.h"

#define BUTTON_BG_COLOR rgb(0xFF2C55)
#define SCENE_BG_COLOR rgb(0x000000)

LV_IMAGE_DECLARE(img_microphone);

const char* INSTRUCTION_TEXT =
    "Press and hold to record.\nRelease to stop and play.";

static lv_style_t bigRingPressedStyle;
static lv_style_t midRingPressedStyle;

void MainScene::onInit() {
  MXScene::onInit();

  audioRecorder = new AudioRecorder();

  root()->bg(SCENE_BG_COLOR)->scrollable(false);

  titleLabel =
      root()->add_label("VoiceRepeater", MX_FONT_SIZE_XL)->center_x(0, 46);
  instructionLabel = root()
                         ->add_label()
                         ->text(INSTRUCTION_TEXT)
                         ->text(MX_FONT_SIZE_SM)
                         ->text_secondary()
                         ->text_center()
                         ->center_x(0, 82);

  bigRing = root()
                ->add_object()
                ->size(256)
                ->center(0, 96)
                ->bg(BUTTON_BG_COLOR, 0.15)
                ->rounded_full()
                ->clickable(false);
  midRing = bigRing->add_object()
                ->size(200)
                ->center()
                ->bg(BUTTON_BG_COLOR, 0.15)
                ->rounded_full()
                ->clickable(false);
  speakButton =
      bigRing->add_button()
          ->size(144)
          ->center()
          ->bg(BUTTON_BG_COLOR)
          ->rounded_full()
          ->onClick([](MXEvent* e) { Serial.println("Clicked"); })
          ->onPressed([this](MXEvent* e) { this->handleSpeakButtonPressed(); })
          ->onReleased(
              [this](MXEvent* e) { this->handleSpeakButtonReleased(); });
  speakButton->add_image(&img_microphone)->center(0)->clickable(false);

  init_pressed_style(&bigRingPressedStyle, 40);
  init_pressed_style(&midRingPressedStyle, 16);
}

void MainScene::init_pressed_style(lv_style_t* style, int32_t size) {
  lv_style_init(style);
  lv_style_set_transform_width(style, size);
  lv_style_set_transform_height(style, size);
}

MainScene::~MainScene() {
  MXScene::~MXScene();
  delete titleLabel;
  titleLabel = nullptr;
  delete instructionLabel;
  instructionLabel = nullptr;
  delete bigRing;
  bigRing = nullptr;
  delete midRing;
  midRing = nullptr;
  delete speakButton;
  speakButton = nullptr;
  delete audioRecorder;
  audioRecorder = nullptr;
}

void MainScene::onUpdate() {
  MXScene::onUpdate();
  audioRecorder->update();
}

void MainScene::handleSpeakButtonPressed() {
  instructionLabel->text(
      "Recording...\n"
      "Release to stop and play.");

  bigRing->add_style(&bigRingPressedStyle);
  midRing->add_style(&midRingPressedStyle);

  Audio.playSystemSound(SYSTEM_SOUND_HIGHER_BEEP);
  audioRecorder->record();
}

void MainScene::handleSpeakButtonReleased() {
  instructionLabel->text(INSTRUCTION_TEXT);

  bigRing->remove_style(&bigRingPressedStyle);
  midRing->remove_style(&midRingPressedStyle);

  Audio.playSystemSound(SYSTEM_SOUND_LOWER_BEEP);
  audioRecorder->play();
  Audio.playSystemSound(SYSTEM_SOUND_LOWER_BEEP);
}
