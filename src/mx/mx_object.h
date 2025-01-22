#pragma once

#include <Arduino.h>
#include <lvgl.h>

#include "mx_event.h"
#include "mx_font.h"

inline lv_color_t mx_theme_color_primary() {
  return lv_theme_get_color_primary(lv_screen_active());
}

inline lv_color_t mx_theme_color_secondary() {
  return lv_theme_get_color_secondary(lv_screen_active());
}

class MXScene;

class MXObject {
 public:
  MXObject(lv_obj_t* obj = nullptr);

  MXObject* reset_to_default();

  ~MXObject();

  inline lv_obj_t* lv_object() { return lv_obj; }

  // Add Objects
  MXObject* add_object(const int32_t width = -1, const int32_t height = -1);

  MXObject* add_label(const char* text = nullptr,
                      const MXFontSize fontSize = MX_FONT_SIZE_DEFAULT);

  MXObject* add_button(const char* text = nullptr,
                       const MXFontSize fontSize = MX_FONT_SIZE_DEFAULT);

  MXObject* add_image(const void* src = nullptr);

  // Flex
  MXObject* flex(lv_flex_flow_t flow,
                 lv_flex_align_t justify_content = LV_FLEX_ALIGN_START,
                 lv_flex_align_t align_items = LV_FLEX_ALIGN_START,
                 lv_flex_align_t align_content = LV_FLEX_ALIGN_START);

  inline MXObject* flex_row(
      lv_flex_align_t justify_content = LV_FLEX_ALIGN_START,
      lv_flex_align_t align_items = LV_FLEX_ALIGN_START,
      lv_flex_align_t align_content = LV_FLEX_ALIGN_START) {
    return flex(LV_FLEX_FLOW_ROW, justify_content, align_items, align_content);
  }

  inline MXObject* flex_col(
      lv_flex_align_t justify_content = LV_FLEX_ALIGN_START,
      lv_flex_align_t align_items = LV_FLEX_ALIGN_START,
      lv_flex_align_t align_content = LV_FLEX_ALIGN_START) {
    return flex(LV_FLEX_FLOW_COLUMN, justify_content, align_items,
                align_content);
  }

  MXObject* flex_grow();

  MXObject* gap(const lv_coord_t gap_x, const lv_coord_t gap_y);
  inline MXObject* gap(const lv_coord_t value) { return gap(value, value); }
  inline MXObject* gap_x(const lv_coord_t x) { return gap(x, 0); }
  inline MXObject* gap_y(const lv_coord_t y) { return gap(0, y); }

  // Size
  int32_t w();
  MXObject* w(const int32_t width);
  int32_t h();
  MXObject* h(const int32_t height);
  MXObject* size(const int32_t width, const int32_t height);
  inline MXObject* size(const int32_t length) { return size(length, length); }
  MXObject* w_percent(const int32_t width);
  MXObject* h_percent(const int32_t height);
  MXObject* size_percent(const int32_t width, const int32_t height);
  inline MXObject* size_percent(const int32_t percent) {
    return size_percent(percent, percent);
  }
  MXObject* w_fit();
  MXObject* h_fit();
  MXObject* size_fit();
  MXObject* w_full();
  MXObject* h_full();
  MXObject* size_full();

  // Position
  int32_t x();
  MXObject* x(const int32_t x);
  int32_t y();
  MXObject* y(const int32_t y);
  MXObject* pos(const int32_t x, const int32_t y);

  MXObject* move_foreground();
  MXObject* move_background();

  // Padding
  MXObject* p(const lv_coord_t padding);
  MXObject* p(const lv_coord_t padding_x, const lv_coord_t padding_y);
  MXObject* p_x(const lv_coord_t padding_x);
  MXObject* p_y(const lv_coord_t padding_y);

  // Align
  MXObject* align(const lv_align_t align, const lv_coord_t offset_x = 0,
                  const lv_coord_t offset_y = 0);
  inline MXObject* center(const lv_coord_t offset_x = 0,
                          const lv_coord_t offset_y = 0) {
    return align(LV_ALIGN_CENTER, offset_x, offset_y);
  }
  inline MXObject* center_x(const lv_coord_t offset_x = 0,
                            const lv_coord_t offset_y = 0) {
    return align(LV_ALIGN_TOP_MID, offset_x, offset_y);
  }
  inline MXObject* center_y(const lv_coord_t offset_x = 0,
                            const lv_coord_t offset_y = 0) {
    return align(LV_ALIGN_LEFT_MID, offset_x, offset_y);
  }

  // Border
  MXObject* border(const uint16_t size,
                   const lv_color_t color = lv_color_black(),
                   const lv_border_side_t side = LV_BORDER_SIDE_FULL);
  MXObject* border_none();

  // Background
  MXObject* bg(const lv_color_t color, const float opacity = 1);
  MXObject* bg_opacity(const float opacity);
  inline MXObject* bg_transparent() { return bg(lv_color_black(), 0); }
  inline MXObject* bg_primary(const float opacity = 1) {
    return bg(mx_theme_color_primary(), opacity);
  }
  inline MXObject* bg_secondary(const float opacity = 1) {
    return bg(mx_theme_color_secondary(), opacity);
  }
  inline MXObject* bg_white(const float opacity = 1) {
    return bg(lv_color_white(), opacity);
  }
  inline MXObject* bg_black(const float opacity = 1) {
    return bg(lv_color_black(), opacity);
  }

  // Opacity
  MXObject* opacity(const float opacity);

  // Font
  MXObject* font(const lv_font_t* font);

  MXObject* icon_font(const size_t size);

  // Text
  MXObject* text(const char* text);
  inline MXObject* text(String str) { return text(str.c_str()); };
  MXObject* text_format(const char* format, ...);

  // Text Style
  MXObject* text(const MXFontSize size);
  MXObject* text(const lv_color_t color, const float opacity = 1);
  inline MXObject* text_primary(const float opacity = 1) {
    return text(mx_theme_color_primary(), opacity);
  }
  inline MXObject* text_secondary() { return text(lv_color_white(), 0.6); }
  inline MXObject* text_tertiary() { return text(lv_color_white(), 0.33); }
  inline MXObject* text_white(const float opacity = 1) {
    return text(lv_color_white(), opacity);
  }
  inline MXObject* text_black(const float opacity = 1) {
    return text(lv_color_black(), opacity);
  }
  MXObject* text_opacity(const float opacity);
  MXObject* text_align(const lv_text_align_t align);
  inline MXObject* text_center() { return text_align(LV_TEXT_ALIGN_CENTER); }
  MXObject* text_letter_space(const lv_coord_t space);

  // Corner
  MXObject* rounded(const lv_coord_t radius);
  inline MXObject* rounded_full(const uint16_t diameter = 0) {
    if (diameter > 0) {
      size(diameter, diameter);
    }
    return rounded(LV_RADIUS_CIRCLE);
  }

  // Clip
  MXObject* clip_content();

  // Visibility
  MXObject* show();
  MXObject* hide();
  MXObject* toggle();
  inline MXObject* toggle(bool visible) {
    if (visible) {
      show();
    } else {
      hide();
    }
    return this;
  }

  // Style
  MXObject* add_style(const lv_style_t* style);
  MXObject* remove_style(const lv_style_t* style);

  // Flag
  MXObject* add_flag(const lv_obj_flag_t flag);
  MXObject* remove_flag(const lv_obj_flag_t flag);

  // Clickable
  MXObject* clickable(bool value);

  // Scrollable
  int32_t scroll_x();
  int32_t scroll_y();
  MXObject* scrollable(bool value);
  MXObject* scroll_to_x(const int32_t x, bool animate = true);
  MXObject* scroll_to_y(const int32_t y, bool animate = true);
  MXObject* scroll_bar(lv_scrollbar_mode_t mode);
  inline MXObject* scroll_bar_hidden() {
    return scroll_bar(LV_SCROLLBAR_MODE_OFF);
  }
  inline MXObject* scroll_bar_auto() {
    return scroll_bar(LV_SCROLLBAR_MODE_AUTO);
  }
  inline MXObject* scroll_bar_active() {
    return scroll_bar(LV_SCROLLBAR_MODE_ACTIVE);
  }
  inline MXObject* scroll_bar_on() { return scroll_bar(LV_SCROLLBAR_MODE_ON); }
  MXObject* scroll_into_view(bool animate = true);
  MXObject* scroll_snap_x(const lv_scroll_snap_t snap_x);
  MXObject* scroll_snap_y(const lv_scroll_snap_t snap_y);
  MXObject* scroll_snap(const lv_scroll_snap_t snap_x,
                        const lv_scroll_snap_t snap_y);

  // Events
  MXObject* on(const lv_event_code_t event, const mx_event_callback_t callback);
  inline MXObject* on_click(const mx_event_callback_t callback) {
    return on(LV_EVENT_CLICKED, callback);
  }
  inline MXObject* on_pressed(const mx_event_callback_t callback) {
    return on(LV_EVENT_PRESSED, callback);
  }
  inline MXObject* on_released(const mx_event_callback_t callback) {
    return on(LV_EVENT_RELEASED, callback);
  }
  inline MXObject* on_scroll(const mx_event_callback_t callback) {
    return on(LV_EVENT_SCROLL, callback);
  }
  inline MXObject* on_scroll_begin(const mx_event_callback_t callback) {
    return on(LV_EVENT_SCROLL_BEGIN, callback);
  }
  inline MXObject* on_scroll_end(const mx_event_callback_t callback) {
    return on(LV_EVENT_SCROLL_END, callback);
  }

  // Image
  MXObject* src(const void* src);
  MXObject* image_pivot(const lv_coord_t x, const lv_coord_t y);
  MXObject* image_scale(const float scale);
  MXObject* image_rotate(const float degrees);

 protected:
  lv_obj_t* lv_obj;

  lv_obj_t* get_text_obj();
};

MXObject* mx();
MXObject* mx(lv_obj_t* lv_obj);
MXObject* mx(MXScene* scene);
