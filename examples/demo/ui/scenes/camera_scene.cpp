#include "camera_scene.h"

#include "camera.h"

CameraScene* CameraScene::_instance = nullptr;

void CameraScene::onInit() {
  MXScene::onInit();

  root()->bg_black();
}

void CameraScene::onShow() {
  MXScene::onShow();
  Camera.begin();
  Camera.startLiveView();
}

void CameraScene::onUpdate() {
  MXScene::onUpdate();
  Camera.update();
}

void CameraScene::onDeactivating() {
  MXScene::onDeactivating();
  Camera.end();
}
