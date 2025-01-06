#pragma once

#include <lvgl.h>

#include "lcd_display.h"

#if DISPLAY_TOUCH_ENABLED == 1

class TouchLCDDisplay : public LCDDisplay {
 public:
  void begin();

  void rotate(const uint16_t degree);

  int readTouchPoints(ESP_PanelTouchPoint* points,
                      const size_t num_points) const;

 protected:
  ESP_PanelTouch* touch = nullptr;
};

extern TouchLCDDisplay Display;

#endif
