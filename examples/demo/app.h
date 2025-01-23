#pragma once

#include "ui/scenes/home_scene.h"
#include "ui/scenes/select_agent_scene.h"
#include "ui/views/status_bar.h"

class App : public MXApplication {
 protected:
  SelectAgentScene* selectAgentScene;

  inline void onInit() override {
    statusBar = new StatusBar();
    statusBar->init();

    selectAgentScene = new SelectAgentScene();
    selectAgentScene->init();
  }

  inline void onStart() override { selectAgentScene->show(); }
};

extern App app;
