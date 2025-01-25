#pragma once

#include <lvgl.h>
#include <mx.h>

#include "../views/agent_card_roller.h"

struct AppInfo {
  const char* id = "";
  const char* name = "";
  const char* icon = "";
  const lv_color_t color = lv_color_black();
};

extern AppInfo APP_INFO_LIST[4];

class HomeScene : public MXScene {
 public:
  ~HomeScene() { delete appIconsContainer; }

  inline static HomeScene* instance() {
    if (_instance == nullptr) {
      _instance = new HomeScene();
      _instance->init();
    }
    return _instance;
  }

 protected:
  MXObject* appIconsContainer;
  void onInit() override;

 private:
  static HomeScene* _instance;
};
