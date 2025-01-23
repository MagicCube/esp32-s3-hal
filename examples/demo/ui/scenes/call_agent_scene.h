#pragma once

#include <button.h>
#include <mx.h>

class CallAgentScene : public MXScene {
 public:
  inline static CallAgentScene* instance() {
    if (_instance == nullptr) {
      _instance = new CallAgentScene();
      _instance->init();
    }
    return _instance;
  }

 protected:
  MXObject* interruptButton;
  MXObject* hangUpButton;
  MXObject* avatarFrame;
  MXObject* avatarImage;
  MXObject* nameLabel;
  MXObject* durationLabel;

  void onInit() override;

 private:
  static CallAgentScene* _instance;
};
