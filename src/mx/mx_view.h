#pragma once

#include <lvgl.h>

#include <vector>

#include "mx_object.h"

class MXView {
 public:
  MXView();
  virtual ~MXView();

  inline bool isInitialized() const { return _initialized; }
  inline MXObject* root() const { return _root; }
  inline int32_t width() const { return lv_obj_get_width(_root->lv_object()); }
  inline int32_t height() const {
    return lv_obj_get_height(_root->lv_object());
  }
  inline std::vector<MXView*> subviews() const { return _subviews; }

  void init();
  void update();
  void addSubview(MXView* subview);
  void removeSubview(MXView* subview);

 protected:
  MXObject* _root;
  virtual MXObject* createRoot();
  virtual inline void onInit() {};
  virtual inline void onLayout() {};
  virtual inline void onUpdate() {}

 private:
  bool _initialized = false;
  MXView* _parentView = nullptr;
  std::vector<MXView*> _subviews;
};
