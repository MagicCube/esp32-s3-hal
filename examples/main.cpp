#include <Arduino.h>
#include <audio.h>
#include <display.h>
#include <lvgl.h>
#include <lvgl_port_v9.h>
#include <mx.h>

#include "demo/app.h"

void hal_setup() {
  Serial.begin(115200);
  Display.begin();
  Audio.begin();
  Audio.playSystemSound(SYSTEM_SOUND_STARTUP);
#ifdef DISPLAY_ST77916
  Display.rotate(180);
#endif
  delay(500);
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
