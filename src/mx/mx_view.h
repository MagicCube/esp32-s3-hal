#pragma once

#include "mx_object.h"

class MXView {
 public:
  inline MXView() { _root = createRoot(); }

  void begin();

  ~MXView();

  inline bool isInitialized() const { return _initialized; }
  inline MXObject *root() const { return _root; }

  MXObject *createRoot();

  int32_t width() const;
  int32_t height() const;

  void update();

 protected:
  virtual void onInit();
  virtual void onLayout() {};
  virtual void onUpdate() {};

 private:
  bool _initialized = false;
  MXObject *_root;
};
