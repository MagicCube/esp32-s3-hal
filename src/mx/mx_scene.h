#pragma once

#include <lvgl.h>

#include "mx_object.h"
#include "mx_view.h"

class MXScene : public MXView {
 public:
  MXScene();

  bool isActive();

  void activate();

  void deactivate();

  void show(lv_scr_load_anim_t animation = LV_SCR_LOAD_ANIM_FADE_ON,
            uint32_t duration = 200, uint32_t delay = 0);

 protected:
  virtual MXObject* createRoot() override;
  virtual inline void onActivating() {};
  virtual inline void onDeactivating() {};
  virtual inline void onShow() {};
};
