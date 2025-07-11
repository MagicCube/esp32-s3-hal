#include "mx_object.h"

#include "mx_color.h"
#include "mx_scene.h"

MXObject::MXObject(lv_obj_t* obj) : lv_obj(obj) {
  if (obj == nullptr) {
    lv_obj = lv_obj_create(nullptr);
    reset_to_default();
  }
}

MXObject::~MXObject() {
  if (lv_obj) {
    lv_obj_delete_async(lv_obj);
  }
}

MXObject* MXObject::reset_to_default() {
  p(0);
  border_none();
  rounded(0);
  bg_transparent();
  scrollable(false);
  transform_origin_center();
  return this;
}

MXObject* MXObject::add_object(const int32_t width, const int32_t height) {
  lv_obj_t* lv_object = lv_obj_create(lv_obj);
  MXObject* object = new MXObject(lv_object);
  if (width >= 0) {
    object->w(width);
  } else {
    object->w_fit();
  }
  if (height >= 0) {
    object->h(height);
  } else {
    object->h_fit();
  }
  object->reset_to_default();
  return object;
}

MXObject* MXObject::add_label(const char* text, const MXFontSize fontSize) {
  lv_obj_t* lv_label = lv_label_create(lv_obj);
  MXObject* label = new MXObject(lv_label);
  if (text != nullptr) {
    label->text(text);
  } else {
    label->text("");
  }
  label->text(fontSize);
  return label;
}

MXObject* MXObject::add_button(const char* text, const MXFontSize fontSize) {
  lv_obj_t* lv_button = lv_btn_create(lv_obj);
  MXObject* button = new MXObject(lv_button);
  if (text != nullptr) {
    lv_obj_t* lv_label = lv_label_create(lv_button);
    lv_obj_align(lv_label, LV_ALIGN_CENTER, 0, 0);
    button->text(text);
    button->text(fontSize);
  }
  return button;
}

MXObject* MXObject::add_image(const void* src) {
  lv_obj_t* lv_image = lv_img_create(lv_obj);
  MXObject* image = new MXObject(lv_image);
  if (src != nullptr) {
    image->src(src);
  }
  return image;
}

MXObject* MXObject::flex(lv_flex_flow_t flow, lv_flex_align_t justify_content,
                         lv_flex_align_t align_items,
                         lv_flex_align_t align_content) {
  lv_obj_set_flex_flow(lv_obj, flow);
  lv_obj_set_flex_align(lv_obj, justify_content, align_content, align_items);
  lv_obj_set_style_pad_column(lv_obj, 0, LV_PART_MAIN);
  lv_obj_set_style_pad_row(lv_obj, 0, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::flex_grow() {
  lv_obj_set_flex_grow(lv_obj, 1);
  return this;
}

MXObject* MXObject::gap(const lv_coord_t gap_x, const lv_coord_t gap_y) {
  lv_obj_set_style_pad_column(lv_obj, gap_x, LV_PART_MAIN);
  lv_obj_set_style_pad_row(lv_obj, gap_y, LV_PART_MAIN);
  return this;
}

int32_t MXObject::w() { return lv_obj_get_width(lv_obj); }

MXObject* MXObject::w(const int32_t width) {
  lv_obj_set_width(lv_obj, width);
  return this;
}

int32_t MXObject::h() { return lv_obj_get_height(lv_obj); }

MXObject* MXObject::h(const int32_t height) {
  lv_obj_set_height(lv_obj, height);
  return this;
}

MXObject* MXObject::size(const int32_t width, const int32_t height) {
  lv_obj_set_size(lv_obj, width, height);
  return this;
}

MXObject* MXObject::w_percent(const int32_t width) {
  lv_obj_set_width(lv_obj, lv_pct(width));
  return this;
}

MXObject* MXObject::h_percent(const int32_t height) {
  lv_obj_set_height(lv_obj, lv_pct(height));
  return this;
}

MXObject* MXObject::size_percent(const int32_t width, const int32_t height) {
  lv_obj_set_size(lv_obj, lv_pct(width), lv_pct(height));
  return this;
}

MXObject* MXObject::w_fit() {
  lv_obj_set_width(lv_obj, LV_SIZE_CONTENT);
  return this;
}

MXObject* MXObject::h_fit() {
  lv_obj_set_height(lv_obj, LV_SIZE_CONTENT);
  return this;
}

MXObject* MXObject::size_fit() {
  lv_obj_set_size(lv_obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
  return this;
}

MXObject* MXObject::w_full() {
  w_percent(100);
  return this;
}

MXObject* MXObject::h_full() {
  h_percent(100);
  return this;
}

MXObject* MXObject::size_full() {
  size_percent(100, 100);
  return this;
}

int32_t MXObject::x() { return lv_obj_get_x(lv_obj); }

MXObject* MXObject::x(const int32_t x) {
  lv_obj_set_x(lv_obj, x);
  return this;
}

int32_t MXObject::y() { return lv_obj_get_y(lv_obj); }

MXObject* MXObject::y(const int32_t y) {
  lv_obj_set_y(lv_obj, y);
  return this;
}

MXObject* MXObject::pos(const int32_t x, const int32_t y) {
  lv_obj_set_pos(lv_obj, x, y);
  return this;
}

MXObject* MXObject::move_foreground() {
  lv_obj_move_foreground(lv_obj);
  return this;
}

MXObject* MXObject::move_background() {
  lv_obj_move_background(lv_obj);
  return this;
}

MXObject* MXObject::p(const lv_coord_t padding) {
  lv_obj_set_style_pad_all(lv_obj, padding, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::p(const lv_coord_t padding_x, const lv_coord_t padding_y) {
  p_x(padding_x);
  p_y(padding_y);
  return this;
}

MXObject* MXObject::p_x(const lv_coord_t padding_x) {
  lv_obj_set_style_pad_hor(lv_obj, padding_x, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::p_y(const lv_coord_t padding_y) {
  lv_obj_set_style_pad_ver(lv_obj, padding_y, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::align(const lv_align_t align, const lv_coord_t offset_x,
                          const lv_coord_t offset_y) {
  lv_obj_align(lv_obj, align, offset_x, offset_y);
  return this;
}

MXObject* MXObject::border(const uint16_t size, const lv_color_t color,
                           const float opacity, const lv_border_side_t side) {
  if (size == 0) {
    lv_obj_set_style_border_width(lv_obj, 0, LV_PART_MAIN);
    lv_obj_set_style_border_side(lv_obj, LV_BORDER_SIDE_NONE, LV_PART_MAIN);
  } else {
    lv_obj_set_style_border_width(lv_obj, size, LV_PART_MAIN);
    lv_obj_set_style_border_side(lv_obj, side, LV_PART_MAIN);
    lv_obj_set_style_border_color(lv_obj, color, LV_PART_MAIN);
    lv_obj_set_style_border_opa(lv_obj, opacity * 255, LV_PART_MAIN);
  }
  return this;
}

MXObject* MXObject::border_none() {
  border(0);
  return this;
}

MXObject* MXObject::bg(const lv_color_t color, const float opacity) {
  lv_obj_set_style_bg_color(lv_obj, color, LV_PART_MAIN);
  bg_opacity(opacity);
  return this;
}

MXObject* MXObject::bg_opacity(const float opacity) {
  lv_obj_set_style_bg_opa(lv_obj, opacity * 255, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::opacity(const float opacity) {
  lv_obj_set_style_opa(lv_obj, opacity * 255, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::font(const lv_font_t* font) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_font(text_obj, font, LV_PART_MAIN);
  }
  return this;
}

MXObject* MXObject::icon_font(const size_t size) {
  lv_font_t* f = make_icon_font(size);
  font(f);
  return this;
}

MXObject* MXObject::text(const char* text) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_label_set_text(text_obj, text);
  } else {
    lv_label_set_text(text_obj, "");
  }
  return this;
}

MXObject* MXObject::text_format(const char* format, ...) {
  va_list args;
  va_start(args, format);
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_label_set_text_fmt(text_obj, format, args);
  }
  va_end(args);
  return this;
}

MXObject* MXObject::text(const MXFontSize size) {
  switch (size) {
    case MX_FONT_SIZE_14:
      font(lv_font_pingfang_regular_14);
      break;
    case MX_FONT_SIZE_16:
      font(lv_font_pingfang_regular_16);
      break;
    case MX_FONT_SIZE_18:
      font(lv_font_pingfang_regular_18);
      break;
    case MX_FONT_SIZE_20:
      font(lv_font_pingfang_regular_20);
      break;
    case MX_FONT_SIZE_24:
      font(lv_font_pingfang_regular_24);
      break;
    case MX_FONT_SIZE_30:
      font(lv_font_pingfang_regular_30);
      break;
    case MX_FONT_SIZE_36:
      font(lv_font_pingfang_regular_36);
      break;
    case MX_FONT_SIZE_48:
      font(lv_font_pingfang_regular_48);
      break;
    default:
      font(lv_font_pingfang_regular_16);
      break;
  }
  return this;
}

MXObject* MXObject::text(const lv_color_t color, const float opacity) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_color(text_obj, color, LV_PART_MAIN);
    lv_obj_set_style_text_opa(text_obj, opacity * 255, LV_PART_MAIN);
  }
  return this;
}

MXObject* MXObject::text_opacity(const float opacity) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_opa(text_obj, opacity * 255, LV_PART_MAIN);
  }
  return this;
}

MXObject* MXObject::text_align(const lv_text_align_t align) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_align(text_obj, align, LV_PART_MAIN);
  }
  return this;
}

MXObject* MXObject::text_letter_space(const lv_coord_t space) {
  auto text_obj = get_text_obj();
  if (text_obj != nullptr) {
    lv_obj_set_style_text_letter_space(text_obj, space, LV_PART_MAIN);
  }
  return this;
}

MXObject* MXObject::rounded(const lv_coord_t radius) {
  lv_obj_set_style_radius(lv_obj, radius, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::transform_origin(const lv_coord_t x, const lv_coord_t y) {
  lv_obj_set_style_transform_pivot_x(lv_obj, x, LV_PART_MAIN);
  lv_obj_set_style_transform_pivot_y(lv_obj, y, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::transform_rotate(const float degrees) {
  lv_obj_set_style_transform_angle(lv_obj, degrees * 10, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::transform_scale(const float scale) {
  lv_obj_set_style_transform_scale(lv_obj, scale * LV_SCALE_NONE, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::clip_content() {
  lv_obj_set_style_clip_corner(lv_obj, true, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::show() {
  remove_flag(LV_OBJ_FLAG_HIDDEN);
  return this;
}

MXObject* MXObject::hide() {
  add_flag(LV_OBJ_FLAG_HIDDEN);
  return this;
}

MXObject* MXObject::toggle() {
  bool hidden = lv_obj_has_flag(lv_obj, LV_OBJ_FLAG_HIDDEN);
  return this->toggle(!hidden);
}

lv_obj_t* MXObject::get_text_obj() {
  if (lv_obj_check_type(lv_obj, &lv_button_class)) {
    return lv_obj_get_child(lv_obj, 0);
  } else if (lv_obj_check_type(lv_obj, &lv_label_class)) {
    return lv_obj;
  }
  return nullptr;
}

MXObject* MXObject::add_style(const lv_style_t* style) {
  lv_obj_add_style(lv_obj, style, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::remove_style(const lv_style_t* style) {
  lv_obj_remove_style(lv_obj, style, LV_PART_MAIN);
  return this;
}

MXObject* MXObject::add_flag(const lv_obj_flag_t flag) {
  lv_obj_add_flag(lv_obj, flag);
  return this;
}

MXObject* MXObject::remove_flag(const lv_obj_flag_t flag) {
  lv_obj_clear_flag(lv_obj, flag);
  return this;
}

MXObject* MXObject::clickable(bool value = true) {
  if (value) {
    lv_obj_add_flag(lv_obj, LV_OBJ_FLAG_CLICKABLE);
  } else {
    lv_obj_clear_flag(lv_obj, LV_OBJ_FLAG_CLICKABLE);
  }
  return this;
}

int32_t MXObject::scroll_x() { return lv_obj_get_scroll_x(lv_obj); }
int32_t MXObject::scroll_y() { return lv_obj_get_scroll_y(lv_obj); }

MXObject* MXObject::scrollable(bool value = true) {
  if (value) {
    add_flag(LV_OBJ_FLAG_SCROLLABLE);
  } else {
    remove_flag(LV_OBJ_FLAG_SCROLLABLE);
  }
  return this;
}

MXObject* MXObject::scroll_to_x(const int32_t x, bool animate) {
  lv_obj_scroll_to_x(lv_obj, x, animate ? LV_ANIM_ON : LV_ANIM_OFF);
  return this;
}

MXObject* MXObject::scroll_to_y(const int32_t y, bool animate) {
  lv_obj_scroll_to_y(lv_obj, y, animate ? LV_ANIM_ON : LV_ANIM_OFF);
  return this;
}

MXObject* MXObject::scroll_bar(lv_scrollbar_mode_t mode) {
  lv_obj_set_scrollbar_mode(lv_obj, mode);
  return this;
}

MXObject* MXObject::scroll_into_view(bool animate) {
  lv_obj_scroll_to_view(lv_obj, animate ? LV_ANIM_ON : LV_ANIM_OFF);
  return this;
}

MXObject* MXObject::scroll_snap_x(const lv_scroll_snap_t snap_x) {
  lv_obj_set_scroll_snap_x(lv_obj, snap_x);
  return this;
}

MXObject* MXObject::scroll_snap_y(const lv_scroll_snap_t snap_y) {
  lv_obj_set_scroll_snap_y(lv_obj, snap_y);
  return this;
}

MXObject* MXObject::scroll_snap(const lv_scroll_snap_t snap_x,
                                const lv_scroll_snap_t snap_y) {
  scroll_snap_x(snap_x);
  scroll_snap_y(snap_y);
  return this;
}

MXObject* MXObject::on(const lv_event_code_t event,
                       const mx_event_callback_t callback) {
  MXEvent* mx_event = new MXEvent{event, this, callback};
  lv_obj_add_event_cb(
      lv_obj,
      [](lv_event_t* lv_event) {
        MXEvent* mx_event = (MXEvent*)lv_event_get_user_data(lv_event);
        mx_event->callback(mx_event);
      },
      event, mx_event);
  return this;
}

MXObject* MXObject::src(const void* src) {
  lv_img_set_src(lv_obj, src);
  return this;
}

MXObject* MXObject::image_origin(const lv_coord_t x, const lv_coord_t y) {
  lv_img_set_pivot(lv_obj, x, y);
  return this;
}

MXObject* MXObject::image_scale(const float scale) {
  lv_image_set_scale(lv_obj, 255 * scale);
  return this;
}

MXObject* MXObject::image_rotate(const float degrees) {
  lv_img_set_angle(lv_obj, degrees * 10);
  return this;
}

MXObject* mx() {
  MXObject* obj = new MXObject(lv_scr_act());
  return obj;
}

MXObject* mx(lv_obj_t* lv_obj) {
  MXObject* obj = new MXObject(lv_obj);
  return obj;
}

MXObject* mx(MXScene* scene) { return scene->root(); }
