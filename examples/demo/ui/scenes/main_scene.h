#pragma once

#include <mx.h>

LV_IMAGE_DECLARE(img_background);
LV_IMAGE_DECLARE(img_call_agent_scene);
LV_IMAGE_DECLARE(img_home_screen);
LV_IMAGE_DECLARE(img_select_agent_scene);

class MainScene : public MXScene {
 protected:
  inline void onInit() override {
    MXScene::onInit();

    root()->scroll_bar_hidden();
    root()->scroll_snap(LV_SCROLL_SNAP_NONE, LV_SCROLL_SNAP_START);

    root()->add_image(&img_home_screen);
    root()->add_image(&img_select_agent_scene)->y(height());
    root()->add_image(&img_call_agent_scene)->y(height() * 2);
  }
};
