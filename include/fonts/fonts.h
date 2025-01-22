#pragma once

#include <fonts/font_awesome.h>
#include <lvgl.h>

extern const lv_font_t *lv_font_pingfang_medium_14;
extern const lv_font_t *lv_font_pingfang_medium_16;
extern const lv_font_t *lv_font_pingfang_medium_18;
extern const lv_font_t *lv_font_pingfang_medium_20;
extern const lv_font_t *lv_font_pingfang_medium_24;
extern const lv_font_t *lv_font_pingfang_medium_30;
extern const lv_font_t *lv_font_pingfang_medium_36;
extern const lv_font_t *lv_font_pingfang_medium_48;

void setup_fonts();

lv_font_t *make_icon_font(size_t size);
