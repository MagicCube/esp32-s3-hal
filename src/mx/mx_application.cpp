#include "mx_application.h"

#include "mx_scene.h"

MXApplication* MXApplication::_instance = nullptr;
MXScene* MXApplication::_activeScene = nullptr;
MXApplication::MXApplication() { _instance = this; }

void MXApplication::init() {
  if (_instance == nullptr) {
    _instance = new MXApplication();
  }
  _instance->onInit();
}

void MXApplication::start() {
  if (_instance == nullptr) {
    return;
  }
  _instance->onStart();
}

void MXApplication::update() {
  if (_instance == nullptr) {
    return;
  }
  _instance->onUpdate();
  if (_instance->activeScene()) {
    _instance->activeScene()->update();
  }
}

void MXApplication::activateScene(MXScene* scene) {
  if (scene == _activeScene) {
    return;
  }
  if (_activeScene) {
    _activeScene->deactivate();
  }
  _activeScene = scene;
}
