#pragma once

#include <lvgl.h>

#include "display_conf.h"
#include "touch_lcd_display.h"

#define DRAW_BUFFER_SIZE \
  (DISPLAY_RES_WIDTH * DISPLAY_RES_HEIGHT * (LV_COLOR_DEPTH / 8) / 5)
uint32_t draw_buffer[DRAW_BUFFER_SIZE];

extern TouchLCDDisplay Display;

inline void lv_setup_display() {
  lv_display_t *disp = lv_display_create(DISPLAY_RES_WIDTH, DISPLAY_RES_HEIGHT);
  lv_display_set_flush_cb(disp, [](lv_display_t *disp, const lv_area_t *area,
                                   unsigned char *px_map) {
    Display.drawBitmap(px_map, area->x1, area->y1, lv_area_get_width(area),
                       lv_area_get_height(area));
    lv_display_flush_ready(disp);
  });
  lv_display_set_buffers(disp, draw_buffer, NULL, sizeof(draw_buffer),
                         LV_DISPLAY_RENDER_MODE_PARTIAL);
}

inline void lv_setup_touch() {
  lv_indev_t *indev = lv_indev_create();
  lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
  lv_indev_set_read_cb(indev, [](lv_indev_t *indev, lv_indev_data_t *data) {
    ESP_PanelTouchPoint point;
    int read_touch_result = Display.readTouchPoints(&point, 1);
    if (read_touch_result > 0) {
      data->point.x = point.x;
      data->point.y = point.y;
      data->state = LV_INDEV_STATE_PRESSED;
    } else {
      data->state = LV_INDEV_STATE_RELEASED;
    }
  });
}

inline void lv_setup_theme() {
  lv_theme_t *th = lv_theme_default_init(
      lv_display_get_default(), /* Use DPI, size, etc. from this display */
      lv_color_make(0x30, 0x6f, 0xff), /* Primary color */
      lv_color_make(0x3f, 0xd4, 0xcf), /* Secondary color */
      true,                            /* Dark theme? */
      &lv_font_montserrat_16);

  lv_display_set_theme(lv_display_get_default(),
                       th); /* Assign theme to display */
  lv_obj_t *active_screen = lv_screen_active();
  if (active_screen) {
    lv_obj_set_style_bg_color(active_screen, lv_color_black(), LV_PART_MAIN);
  }
}

inline void lv_setup() {
  lv_init();
  lv_tick_set_cb([]() { return (uint32_t)(esp_timer_get_time() / 1000); });

  lv_setup_display();
  lv_setup_touch();
  lv_setup_theme();
}

inline void lv_loop() {
  lv_timer_handler();
  delay(5);
}
