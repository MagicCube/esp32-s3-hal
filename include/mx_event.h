#pragma once

#include <lvgl.h>

#include <functional>

class MXObject;
struct MXEvent;

typedef std::function<void(MXEvent* e)> mx_event_callback_t;

struct MXEvent {
  lv_event_code_t code;
  MXObject* target;
  mx_event_callback_t callback;
};
