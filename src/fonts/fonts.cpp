#include "fonts/fonts.h"

#include "fonts/pingfang_medium.h"

const lv_font_t *lv_font_pingfang_medium_14 = nullptr;
const lv_font_t *lv_font_pingfang_medium_16 = nullptr;
const lv_font_t *lv_font_pingfang_medium_18 = nullptr;
const lv_font_t *lv_font_pingfang_medium_20 = nullptr;
const lv_font_t *lv_font_pingfang_medium_24 = nullptr;
const lv_font_t *lv_font_pingfang_medium_30 = nullptr;
const lv_font_t *lv_font_pingfang_medium_36 = nullptr;
const lv_font_t *lv_font_pingfang_medium_48 = nullptr;

void setup_fonts() {
  lv_font_pingfang_medium_14 =
      lv_tiny_ttf_create_data(pingfang_medium, pingfang_medium_size, 14);
  lv_font_pingfang_medium_16 =
      lv_tiny_ttf_create_data(pingfang_medium, pingfang_medium_size, 16);
  lv_font_pingfang_medium_18 =
      lv_tiny_ttf_create_data(pingfang_medium, pingfang_medium_size, 18);
  lv_font_pingfang_medium_20 =
      lv_tiny_ttf_create_data(pingfang_medium, pingfang_medium_size, 20);
  lv_font_pingfang_medium_24 =
      lv_tiny_ttf_create_data(pingfang_medium, pingfang_medium_size, 24);
  lv_font_pingfang_medium_30 =
      lv_tiny_ttf_create_data(pingfang_medium, pingfang_medium_size, 30);
  lv_font_pingfang_medium_36 =
      lv_tiny_ttf_create_data(pingfang_medium, pingfang_medium_size, 36);
  lv_font_pingfang_medium_48 =
      lv_tiny_ttf_create_data(pingfang_medium, pingfang_medium_size, 48);
}
