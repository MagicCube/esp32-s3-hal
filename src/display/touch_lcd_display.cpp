
#include "display_conf.h"

#if DISPLAY_TOUCH_ENABLED == 1

#include "drivers/touch_cst816s_driver.h"
#include "touch_lcd_display.h"

TouchLCDDisplay Display;

void TouchLCDDisplay::begin() {
  LCDDisplay::begin();

  touch = touch_init();
}

void TouchLCDDisplay::rotate(const uint16_t degree) {
  LCDDisplay::rotate(degree);

  switch (degree) {
    case 0:
      touch->swapXY(false);
      touch->mirrorX(false);
      touch->mirrorY(false);
      break;
    case 90:
      touch->swapXY(true);
      touch->mirrorX(true);
      touch->mirrorY(false);
      break;
    case 180:
      touch->swapXY(false);
      touch->mirrorX(true);
      touch->mirrorY(true);
      break;
    case 270:
      touch->swapXY(true);
      touch->mirrorX(false);
      touch->mirrorY(true);
      break;
    default:
      break;
  }
}

int TouchLCDDisplay::readTouchPoints(ESP_PanelTouchPoint* points,
                                     const size_t num_points) const {
  return touch->readPoints(points, num_points);
}

#endif
