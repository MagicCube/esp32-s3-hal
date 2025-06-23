#pragma once

#include <Arduino.h>
#include <lvgl.h>

enum MXFontSize {
  MX_FONT_SIZE_14 = 14,
  MX_FONT_SIZE_16 = 16,
  MX_FONT_SIZE_18 = 18,
  MX_FONT_SIZE_20 = 20,
  MX_FONT_SIZE_24 = 24,
  MX_FONT_SIZE_30 = 30,
  MX_FONT_SIZE_36 = 36,
  MX_FONT_SIZE_48 = 48,
  MX_FONT_SIZE_64 = 64,
};

#define MX_FONT_SIZE_SM MX_FONT_SIZE_14
#define MX_FONT_SIZE_DEFAULT MX_FONT_SIZE_16
#define MX_FONT_SIZE_LG MX_FONT_SIZE_18
#define MX_FONT_SIZE_XL MX_FONT_SIZE_20
#define MX_FONT_SIZE_2XL MX_FONT_SIZE_24
#define MX_FONT_SIZE_3XL MX_FONT_SIZE_30
#define MX_FONT_SIZE_4XL MX_FONT_SIZE_36
#define MX_FONT_SIZE_5XL MX_FONT_SIZE_48
#define MX_FONT_SIZE_6XL MX_FONT_SIZE_64

struct MXFontData {
  uint8_t *data = nullptr;
  size_t size = 0;

  ~MXFontData() {
    if (data) {
      delete[] data;
    }
  }
};

extern MXFontData mx_font_data_font_awesome;

extern const lv_font_t *lv_font_pingfang_regular_14;
extern const lv_font_t *lv_font_pingfang_regular_16;
extern const lv_font_t *lv_font_pingfang_regular_18;
extern const lv_font_t *lv_font_pingfang_regular_20;
extern const lv_font_t *lv_font_pingfang_regular_24;
extern const lv_font_t *lv_font_pingfang_regular_30;
extern const lv_font_t *lv_font_pingfang_regular_36;
extern const lv_font_t *lv_font_pingfang_regular_48;
extern const lv_font_t *lv_font_pingfang_regular_64;

void mx_preload_fonts();

lv_font_t *make_icon_font(size_t size);
