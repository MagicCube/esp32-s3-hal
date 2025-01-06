#include "mx_scene.h"

MXScene* MXScene::_activeScene = nullptr;

void MXScene::begin() {
  if (isInitialized()) {
    return;
  }
  onInit();
  _initialized = true;
  onLayout();
}

MXObject* MXScene::createRoot() {
  auto root = new MXObject();
  root->bg(MX_SCENE_DEFAULT_BG);
  return root;
}

void MXScene::activate() {
  if (!isInitialized()) {
    begin();
  }
  if (isActive()) {
    return;
  }
  if (_activeScene) {
    _activeScene->deactivate();
    _activeScene = nullptr;
  }
  onActivating();
  _activeScene = this;
}

void MXScene::deactivate() {
  if (!isActive()) {
    return;
  }
  onDeactivating();
  if (_activeScene == this) {
    _activeScene = nullptr;
  }
}

void MXScene::show(lv_scr_load_anim_t animation, uint32_t duration,
                   uint32_t delay) {
  if (!isActive()) {
    activate();
  }
  if (animation == LV_SCR_LOAD_ANIM_NONE) {
    lv_screen_load(root()->lv_object());
  } else {
    lv_screen_load_anim(root()->lv_object(), animation, duration, delay, false);
  }
  onShown();
}
