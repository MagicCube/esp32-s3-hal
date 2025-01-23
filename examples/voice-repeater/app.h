#pragma once

#include "ui/scenes/main_scene.h"

class App : public MXApplication {
 protected:
  MainScene *mainScene;

  inline void onInit() override { mainScene = new MainScene(); }

  inline void onStart() override { mainScene->show(); }
};
