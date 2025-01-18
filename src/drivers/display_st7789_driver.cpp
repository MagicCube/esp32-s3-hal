#include "display_st7789_driver.h"

#include <Arduino.h>
#include <ESP_IOExpander.h>
#include <ESP_Panel_Library.h>

#include "assets/splash_280p.h"
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
  // display_clear(lcd);
  lcd->drawBitmapWaitUntilFinish(DISPLAY_OFFSET_X, DISPLAY_OFFSET_Y,
                                 DISPLAY_RES_WIDTH, DISPLAY_RES_HEIGHT,
                                 splash_280p_map);
  // lcd->colorBarTest(DISPLAY_RES_WIDTH, DISPLAY_RES_HEIGHT);
  return lcd;
}

void display_clear(ESP_PanelLcd* display) {
  int bytes_per_pixel = DISPLAY_COLOR_BITS / 8;
  uint8_t* color_buf = nullptr;

  try {
    // Allocate memory for one line
    color_buf = new uint8_t[DISPLAY_RES_WIDTH * bytes_per_pixel];
  } catch (std::bad_alloc& e) {
    return;
  }

  // Fill the buffer with the specified color
  for (int i = 0; i < DISPLAY_RES_WIDTH; i++) {
    color_buf[i * 2] = 0;
    color_buf[i * 2 + 1] = 0;
  }

  // Draw the color across the entire screen
  bool ret = true;
  for (int j = 0; j < DISPLAY_RES_HEIGHT; j++) {
    ret = display->drawBitmapWaitUntilFinish(0 + DISPLAY_OFFSET_X,
                                             j + DISPLAY_OFFSET_Y,
                                             DISPLAY_RES_WIDTH, 1, color_buf);
    if (!ret) {
      break;
    }
  }

  delete[] color_buf;
}

#endif
