#include "display_st7789_driver.h"

#include <Arduino.h>
#include <ESP_IOExpander.h>
#include <ESP_Panel_Library.h>
#include <SPIFFS.h>

#include "display_conf.h"

#ifdef DISPLAY_ST7789

#include "pin_conf.h"

#define DISPLAY_SPI_FREQ_HZ (80 * 1000 * 1000)

void display_clear(ESP_PanelLcd* display);

ESP_PanelLcd* display_init() {
  // Bus
  ESP_PanelBus_SPI* bus =
      new ESP_PanelBus_SPI(DISPLAY_CS, DISPLAY_DC, DISPLAY_CLK, DISPLAY_MOSI);
  bus->configSpiFreqHz(DISPLAY_SPI_FREQ_HZ);
  bus->begin();

  // LCD
  auto lcd = new ESP_PanelLcd_ST7789(bus, DISPLAY_COLOR_BITS);
  lcd->configColorRgbOrder(false);
  lcd->init();
  lcd->reset();
  lcd->begin();
  lcd->invertColor(true);
  lcd->displayOn();

  clear_screen(lcd);
  show_splash_screen(lcd, "/splash_screen.raw");

  return lcd;
}

void show_splash_screen(ESP_PanelLcd* lcd, const char* fileName) {
  File splash_screen_file = SPIFFS.open(fileName, FILE_READ);
  if (splash_screen_file) {
    Serial.println("Splash screen found");
    Serial.println("File size: " + String(splash_screen_file.size()));
    uint8_t* splash_screen_data = new uint8_t[splash_screen_file.size()];
    splash_screen_file.readBytes((char*)splash_screen_data,
                                 splash_screen_file.size());
    lcd->drawBitmapWaitUntilFinish(DISPLAY_OFFSET_X, DISPLAY_OFFSET_Y,
                                   DISPLAY_RES_WIDTH, DISPLAY_RES_HEIGHT,
                                   splash_screen_data);
    delete[] splash_screen_data;
  }
}

void clear_screen(ESP_PanelLcd* display) {
  int bytes_per_pixel = DISPLAY_COLOR_BITS / 8;
  uint8_t* color_buf = nullptr;
  uint8_t color_buf_count = 2;
  uint16_t color_buf_height = DISPLAY_RES_HEIGHT / color_buf_count;
  uint32_t color_buf_size =
      DISPLAY_RES_WIDTH * color_buf_height * bytes_per_pixel;

  try {
    // Allocate memory for one line
    color_buf = new uint8_t[color_buf_size];
  } catch (std::bad_alloc& e) {
    return;
  }

  memset(color_buf, 0, color_buf_size * sizeof(color_buf[0]));

  for (int i = 0; i < color_buf_count; i++) {
    // Draw the color across the entire screen
    display->drawBitmapWaitUntilFinish(0, i * color_buf_height,
                                       DISPLAY_RES_WIDTH, color_buf_height,
                                       color_buf);
  }

  delete[] color_buf;
}

#endif
