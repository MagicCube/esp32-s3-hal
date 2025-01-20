#include "mx_scene.h"

MXScene* MXScene::_activeScene = nullptr;

MXScene::MXScene() : MXView() {}

MXObject* MXScene::createRoot() {
  auto root = new MXObject(lv_obj_create(nullptr));
  root->reset_to_default();
  root->size_full();
  return root;
}

void MXScene::activate() {
  if (!isInitialized()) {
    init();
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
