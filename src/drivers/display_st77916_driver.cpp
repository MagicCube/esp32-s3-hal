#include "display_st77916_driver.h"

#include <Arduino.h>
#include <ESP_IOExpander.h>
#include <ESP_Panel_Library.h>

#include "display_conf.h"

#ifdef DISPLAY_ST77916

#include "pin_conf.h"

#define DISPLAY_SPI_FREQ_HZ (80 * 1000 * 1000)

void display_clear(ESP_PanelLcd* display);

ESP_PanelLcd* display_init() {
  // Bus
  ESP_PanelBus_QSPI* bus =
      new ESP_PanelBus_QSPI(DISPLAY_CS, DISPLAY_SCK, DISPLAY_SDA0, DISPLAY_SDA1,
                            DISPLAY_SDA2, DISPLAY_SDA3);
  bus->configQspiFreqHz(DISPLAY_SPI_FREQ_HZ);
  bus->begin();

  // LCD
  auto lcd = new ESP_PanelLcd_ST77916(bus, DISPLAY_COLOR_BITS, DISPLAY_RST);
  lcd->configColorRgbOrder(false);
  lcd->init();
  lcd->reset();
  lcd->begin();
  lcd->invertColor(true);
  lcd->displayOn();
  display_clear(lcd);
  return lcd;
}

void display_clear(ESP_PanelLcd* display) {
  int bytes_per_pixel = DISPLAY_COLOR_BITS / 8;
  uint8_t* color_buf = nullptr;
  uint8_t color_buf_count = 10;
  uint16_t color_buf_height = DISPLAY_PHYSICAL_RES_HEIGHT / color_buf_count;
  uint32_t color_buf_size =
      DISPLAY_PHYSICAL_RES_WIDTH * color_buf_height * bytes_per_pixel;

  try {
    // Allocate memory for one line
    color_buf = new uint8_t[color_buf_size];
  } catch (std::bad_alloc& e) {
    return;
  }

  for (int i = 0; i < color_buf_size; i++) {
    color_buf[i] = 0;
  }

  for (int i = 0; i < color_buf_count; i++) {
    // Draw the color across the entire screen
    display->drawBitmapWaitUntilFinish(0, i * color_buf_height,
                                       DISPLAY_PHYSICAL_RES_WIDTH,
                                       color_buf_height, color_buf);
  }

  delete[] color_buf;
}

#endif
