#pragma once

#include "mx/mx_color.h"
#include "mx/mx_event.h"
#include "mx/mx_font.h"
#include "mx/mx_object.h"
#include "mx/mx_scene.h"

inline void mx_loop() {
  if (MXScene::activeScene()) {
    MXScene::activeScene()->update();
  }
}
