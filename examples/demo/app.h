#pragma once

#include "ui/scenes/select_agent_scene.h"

class App : public MXApplication {
 protected:
  SelectAgentScene *selectAgentScene;

  inline void onInit() override { selectAgentScene = new SelectAgentScene(); }

  inline void onStart() override { selectAgentScene->show(); }
};
