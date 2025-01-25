#include "mx/mx_font.h"

#include <SPIFFS.h>
#include <lvgl.h>

const lv_font_t *lv_font_pingfang_medium_14 = nullptr;
const lv_font_t *lv_font_pingfang_medium_16 = nullptr;
const lv_font_t *lv_font_pingfang_medium_18 = nullptr;
const lv_font_t *lv_font_pingfang_medium_20 = nullptr;
const lv_font_t *lv_font_pingfang_medium_24 = nullptr;
const lv_font_t *lv_font_pingfang_medium_30 = nullptr;
const lv_font_t *lv_font_pingfang_medium_36 = nullptr;
const lv_font_t *lv_font_pingfang_medium_48 = nullptr;

MXFontData mx_font_data_font_awesome = {nullptr, 0};

MXFontData *preload_font_data(const char *name) {
  MXFontData *font_data = new MXFontData();
  String path = "/" + String(name) + ".ttf";
  File file = SPIFFS.open(path, "r");
  if (!file) {
    Serial.printf("Failed to load font file '%s'\n", path.c_str());
    return nullptr;
  }
  font_data->size = file.size();
  font_data->data = (uint8_t *)malloc(font_data->size);
  file.read(font_data->data, font_data->size);
  file.close();
  Serial.printf("Loaded font file '%s'\n", path.c_str());
  return font_data;
}

void mx_preload_fonts() {
  mx_font_data_font_awesome = *preload_font_data("font_awesome");

  MXFontData *pingfang_medium = preload_font_data("pingfang_medium");
  if (!pingfang_medium) {
    return;
  }

  lv_font_pingfang_medium_14 =
      lv_tiny_ttf_create_data(pingfang_medium->data, pingfang_medium->size, 14);
  lv_font_pingfang_medium_16 =
      lv_tiny_ttf_create_data(pingfang_medium->data, pingfang_medium->size, 16);
  lv_font_pingfang_medium_18 =
      lv_tiny_ttf_create_data(pingfang_medium->data, pingfang_medium->size, 18);
  lv_font_pingfang_medium_20 =
      lv_tiny_ttf_create_data(pingfang_medium->data, pingfang_medium->size, 20);
  lv_font_pingfang_medium_24 =
      lv_tiny_ttf_create_data(pingfang_medium->data, pingfang_medium->size, 24);
  lv_font_pingfang_medium_30 =
      lv_tiny_ttf_create_data(pingfang_medium->data, pingfang_medium->size, 30);
  lv_font_pingfang_medium_36 =
      lv_tiny_ttf_create_data(pingfang_medium->data, pingfang_medium->size, 36);
  lv_font_pingfang_medium_48 =
      lv_tiny_ttf_create_data(pingfang_medium->data, pingfang_medium->size, 48);
}

lv_font_t *make_icon_font(size_t size) {
  return lv_tiny_ttf_create_data(mx_font_data_font_awesome.data,
                                 mx_font_data_font_awesome.size, size);
}
