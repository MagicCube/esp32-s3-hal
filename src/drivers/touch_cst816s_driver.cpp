#include "touch_cst816s_driver.h"

#include <Arduino.h>
#include <ESP_IOExpander.h>
#include <ESP_Panel_Library.h>

#include "display_conf.h"
#include "pin_conf.h"

ESP_PanelTouch* touch_init() {
  ESP_PanelBus_I2C* bus = new ESP_PanelBus_I2C(
      TOUCH_SCL, TOUCH_SDA, ESP_LCD_TOUCH_IO_I2C_CST816S_CONFIG());
  bus->configI2cFreqHz(400000);
  bus->begin();

  auto touch = new ESP_PanelTouch_CST816S(
      bus, DISPLAY_RES_WIDTH, DISPLAY_RES_HEIGHT, TOUCH_RST, TOUCH_INT);
  touch->init();
  touch->begin();
  return touch;
}
