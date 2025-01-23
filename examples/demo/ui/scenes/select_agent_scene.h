#pragma once

#include <button.h>
#include <mx.h>

#include "../views/agent_card_roller.h"

class SelectAgentScene : public MXScene {
 public:
  inline static SelectAgentScene* instance() {
    if (_instance == nullptr) {
      _instance = new SelectAgentScene();
      _instance->init();
    }
    return _instance;
  }

  inline ~SelectAgentScene() {
    delete agentCardRoller;
    delete callButton;
    delete rollButton;
  }

 protected:
  AgentCardRoller* agentCardRoller;
  MXObject* callButton;
  Button* rollButton;

  void onInit() override;
  void onUpdate() override;
  void handleCallButtonClick();

 private:
  static SelectAgentScene* _instance;
};
