#pragma once

#include <mx.h>

class CameraScene : public MXScene {
 public:
  inline static CameraScene* instance() {
    if (_instance == nullptr) {
      _instance = new CameraScene();
      _instance->init();
    }
    return _instance;
  }

 protected:
  void onInit() override;
  void onShow() override;
  void onUpdate() override;
  void onDeactivating() override;

 private:
  static CameraScene* _instance;
};
