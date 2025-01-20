#pragma once

#include <lvgl.h>

#include "mx_object.h"

class MXView {
 public:
  MXView();
  virtual ~MXView();

  inline bool isInitialized() const { return _initialized; }

 protected:
  bool _initialized = false;
};
