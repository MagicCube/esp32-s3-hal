#pragma once

#include <button.h>
#include <mx.h>

#include "../views/agent_card_roller.h"

class HomeScene : public MXScene {
 public:
  ~HomeScene() { delete button; }

  inline static HomeScene* instance() {
    if (_instance == nullptr) {
      _instance = new HomeScene();
      _instance->init();
    }
    return _instance;
  }

 protected:
  MXObject* button;
  void onInit() override;

 private:
  static HomeScene* _instance;
};
