#pragma once

#include "ui/scenes/main_scene.h"

class App : public MXApplication {
 protected:
  MainScene *mainScene;

  MXScene *activeScene;

  inline void onInit() override { mainScene = new MainScene(); }

  inline void onStart() override { mainScene->show(); }
};

App app;
