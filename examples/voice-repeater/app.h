#pragma once

#include "ui/scenes/main_scene.h"

MainScene *mainScene;

inline void app_main() {
  mainScene = new MainScene();
  mainScene->show();
}
