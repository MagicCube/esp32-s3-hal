#include <Arduino.h>
#include <audio.h>
#include <display.h>
#include <lv_integration.h>
#include <lvgl.h>

#include "voice-repeater/app.h"

void hal_setup() {
  Serial.begin(115200);
  Audio.begin();
  Audio.playSystemSound(SYSTEM_SOUND_STARTUP);
  Display.begin();
#ifdef DISPLAY_ST77916
  Display.rotate(180);
#endif
}

void setup() {
  hal_setup();
  lv_setup();
  app_main();
}

time_t last_serial_output = 0;
void serial_loop() {
  if (millis() - last_serial_output > 5 * 1000) {
    // Serial.print(".");
    // Print free memory
    Serial.print("Free memory: ");
    Serial.println(esp_get_free_heap_size());

    last_serial_output = millis();
  }
}

void loop() {
  serial_loop();
  mx_loop();

  // Always keep `lv_loop()` at the end of the loop
  lv_loop();
}
