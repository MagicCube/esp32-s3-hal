#pragma once

#include <mx.h>

LV_IMAGE_DECLARE(img_call_agent_scene);
LV_IMAGE_DECLARE(img_home_screen);
LV_IMAGE_DECLARE(img_select_agent_scene);

class SelectAgentScene : public MXScene {
 protected:
  inline void onInit() override {
    MXScene::onInit();
    root()->bg(rgb(0x040920));

    MXObject *time = root()->add_label("12:18");
    time->align(LV_ALIGN_TOP_LEFT, 16, 12);
  }
};
