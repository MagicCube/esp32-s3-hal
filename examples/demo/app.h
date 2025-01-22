#pragma once

#include "ui/scenes/select_agent_scene.h"
#include "ui/views/status_bar.h"

SelectAgentScene *selectAgentScene;
StatusBar *statusBar;

inline void app_preload() {}

inline void app_main() {
  selectAgentScene = new SelectAgentScene();
  selectAgentScene->show();
}

inline void app_loop() {}
