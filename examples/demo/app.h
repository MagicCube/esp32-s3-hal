#pragma once

#include "ui/scenes/select_agent_scene.h"

SelectAgentScene *selectAgentScene;

inline void app_main() {
  selectAgentScene = new SelectAgentScene();
  selectAgentScene->show();
}
