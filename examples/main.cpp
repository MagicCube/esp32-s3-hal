#include <Arduino.h>
#include <SPIFFS.h>
#include <audio.h>
#include <display.h>
#include <lvgl.h>
#include <lvgl_port_v9.h>
#include <mx.h>

#include "demo/app.h"
#include "wifi.h"

App app;

void hal_setup() {
  Serial.begin(115200);
  Display.begin();
  Audio.begin();
#ifdef DISPLAY_ST77916
  Display.rotate(180);
#endif
  // Audio.playSystemSound(SYSTEM_SOUND_STARTUP);
  // delay(250);
}

void spiffs_setup() {
  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
}

time_t last_serial_output = 0;
void serial_loop() {
  if (millis() - last_serial_output > 10 * 1000) {
    // Serial.print(".");
    // Print free memory
    Serial.print("Free memory: ");
    Serial.println(esp_get_free_heap_size());

    last_serial_output = millis();
  }
}

void setup() {
  spiffs_setup();
  hal_setup();
  wifi_setup();
  lv_setup();
  mx_setup();
  serial_loop();
}

void loop() {
  serial_loop();
  wifi_loop();
  mx_loop();
  // Always keep `lv_loop()` at the end of the loop
  lv_loop();
}
