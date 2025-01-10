#pragma once

#include <lvgl.h>

#include "mx_object.h"

#define MX_SCENE_DEFAULT_BG lv_color_black()

class MXScene {
 public:
  MXScene() {}

  inline static MXScene* activeScene() { return _activeScene; }

  inline bool isInitialized() const { return _initialized; }
  inline bool isActive() const { return _activeScene == this; }
  inline MXObject* root() const { return _root; }
  inline int32_t width() const { return lv_obj_get_width(_root->lv_object()); }
  inline int32_t height() const {
    return lv_obj_get_height(_root->lv_object());
  }

  void begin();
  virtual inline void dispose() {
    if (_root) {
      delete _root;
      _root = nullptr;
    }
  }
  inline ~MXScene() { dispose(); }

  void activate();

  void deactivate();

  inline void update() { onUpdate(); }

  void show(lv_scr_load_anim_t animation = LV_SCR_LOAD_ANIM_FADE_ON,
            uint32_t duration = 200, uint32_t delay = 0);

 protected:
  virtual MXObject* createRoot();
  virtual inline void onInit() { _root = createRoot(); };
  virtual inline void onDispose() {
    delete _root;
    _root = nullptr;
  };
  virtual inline void onLayout() {};
  virtual inline void onActivating() {};
  virtual inline void onDeactivating() {};
  virtual inline void onShown() {};
  virtual inline void onUpdate() {};

 private:
  bool _initialized = false;
  MXObject* _root;

  static MXScene* _activeScene;
};
