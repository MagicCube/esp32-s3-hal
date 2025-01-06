#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "assets/lottie_example.h"

inline void app_main() {
  lv_obj_t* lottie = lv_lottie_create(lv_scr_act());
  lv_lottie_set_src_data(lottie, lottie_example, lottie_example_size);
  const size_t size = 128;
  static uint8_t buf[size * size * 4];
  lv_lottie_set_buffer(lottie, size, size, buf);
  lv_obj_center(lottie);
}
