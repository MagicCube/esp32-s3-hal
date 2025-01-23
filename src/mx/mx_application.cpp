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
  if (_instance->statusBar != nullptr) {
    _instance->statusBar->update();
  }
  _instance->onUpdate();
  if (_instance->activeScene() != nullptr) {
    _instance->activeScene()->update();
  }
}

void MXApplication::activateScene(MXScene* scene) {
  if (scene == _activeScene) {
    return;
  }
  if (_activeScene != nullptr) {
    _activeScene->deactivate();
    _activeScene = nullptr;
  }

  _activeScene = scene;

  if (_instance != nullptr && _activeScene != nullptr) {
    lv_obj_set_parent(_instance->statusBar->root()->lv_object(),
                      _activeScene->root()->lv_object());

    _instance->onSceneActivated(scene);
  }
}
