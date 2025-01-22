#include "mx/mx_font.h"

#include <SPIFFS.h>
#include <lvgl.h>

MXFontData mx_font_data_pingfang_medium = {nullptr, 0};
MXFontData mx_font_data_font_awesome = {nullptr, 0};

const lv_font_t *lv_font_pingfang_medium_14 = nullptr;
const lv_font_t *lv_font_pingfang_medium_16 = nullptr;
const lv_font_t *lv_font_pingfang_medium_18 = nullptr;
const lv_font_t *lv_font_pingfang_medium_20 = nullptr;
const lv_font_t *lv_font_pingfang_medium_24 = nullptr;
const lv_font_t *lv_font_pingfang_medium_30 = nullptr;
const lv_font_t *lv_font_pingfang_medium_36 = nullptr;
const lv_font_t *lv_font_pingfang_medium_48 = nullptr;

void preload_font(const char *name, MXFontData &font_data) {
  String path = "/" + String(name) + ".ttf";
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.printf("Failed to load font file '%s'\n", path.c_str());
    return;
  }
  font_data.size = file.size();
  font_data.data = (uint8_t *)malloc(font_data.size);
  file.read(font_data.data, font_data.size);
  file.close();
  Serial.printf("Loaded font file '%s', size: %d\n", path.c_str(),
                font_data.size);
}

void mx_preload_fonts() {
  preload_font("pingfang_medium", mx_font_data_pingfang_medium);
  preload_font("font_awesome", mx_font_data_font_awesome);

  lv_font_pingfang_medium_14 = lv_tiny_ttf_create_data(
      mx_font_data_pingfang_medium.data, mx_font_data_pingfang_medium.size, 14);
  lv_font_pingfang_medium_16 = lv_tiny_ttf_create_data(
      mx_font_data_pingfang_medium.data, mx_font_data_pingfang_medium.size, 16);
  lv_font_pingfang_medium_18 = lv_tiny_ttf_create_data(
      mx_font_data_pingfang_medium.data, mx_font_data_pingfang_medium.size, 18);
  lv_font_pingfang_medium_20 = lv_tiny_ttf_create_data(
      mx_font_data_pingfang_medium.data, mx_font_data_pingfang_medium.size, 20);
  lv_font_pingfang_medium_24 = lv_tiny_ttf_create_data(
      mx_font_data_pingfang_medium.data, mx_font_data_pingfang_medium.size, 24);
  lv_font_pingfang_medium_30 = lv_tiny_ttf_create_data(
      mx_font_data_pingfang_medium.data, mx_font_data_pingfang_medium.size, 30);
  lv_font_pingfang_medium_36 = lv_tiny_ttf_create_data(
      mx_font_data_pingfang_medium.data, mx_font_data_pingfang_medium.size, 36);
  lv_font_pingfang_medium_48 = lv_tiny_ttf_create_data(
      mx_font_data_pingfang_medium.data, mx_font_data_pingfang_medium.size, 48);
}

lv_font_t *make_icon_font(size_t size) {
  return lv_tiny_ttf_create_data(mx_font_data_font_awesome.data,
                                 mx_font_data_font_awesome.size, size);
}
