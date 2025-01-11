#pragma once

#include "mx_color.h"
#include "mx_event.h"
#include "mx_font.h"
#include "mx_object.h"
#include "mx_scene.h"

inline void mx_loop() {
  if (MXScene::activeScene()) {
    MXScene::activeScene()->update();
  }
}
