#include <Arduino.h>
#include <audio.h>
#include <display.h>
#include <lv_integration.h>
#include <lvgl.h>

void hal_setup() {
  Serial.begin(115200);
  Audio.begin();
  Audio.playSystemSound(SYSTEM_SOUND_STARTUP);
  Display.begin();
#ifdef DISPLAY_ST77916
  Display.rotate(180);
#endif
}

void ui_setup() {
  lv_obj_t* button = lv_button_create(lv_screen_active());
  uint16_t size = min(Display.width(), Display.height()) / 2;
  lv_obj_set_size(button, size, size);
  lv_obj_set_style_radius(button, LV_RADIUS_CIRCLE, LV_PART_MAIN);
  lv_obj_center(button);

  lv_obj_t* buttonLabel = lv_label_create(button);
  lv_label_set_text(buttonLabel, "Click");
  lv_obj_set_style_text_font(buttonLabel, &lv_font_montserrat_24, LV_PART_MAIN);
  lv_obj_center(buttonLabel);

  lv_obj_add_event_cb(
      button,
      [](lv_event_t* e) {
        lv_obj_t* label = (lv_obj_t*)lv_event_get_user_data(e);
        lv_label_set_text(label, "Clicked");
      },
      LV_EVENT_CLICKED, buttonLabel);
}

void setup() {
  hal_setup();
  lv_setup();
  ui_setup();
}

void loop() { lv_loop(); }
