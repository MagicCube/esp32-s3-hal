#pragma once

#ifdef CAM_D0
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

  inline MXSceneStatusBarMode statusBarMode() const override {
    return STATUS_BAR_MODE_NONE;
  }

 protected:
  void onInit() override;
  void onShow() override;
  void onUpdate() override;
  void onDeactivating() override;

 private:
  static CameraScene* _instance;
};

#endif
