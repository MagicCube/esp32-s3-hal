#pragma once

#include <button.h>
#include <mx.h>

#include "../views/agent_card_roller.h"

class HomeScene : public MXScene {
 public:
  inline static HomeScene* instance() {
    if (_instance == nullptr) {
      _instance = new HomeScene();
      _instance->init();
    }
    return _instance;
  }

 private:
  static HomeScene* _instance;
};
