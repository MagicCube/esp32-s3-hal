#include "mx_scene.h"

#include "mx_application.h"

MXScene::MXScene() : MXView() {}

bool MXScene::isActive() { return MXApplication::activeScene() == this; }

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
  onActivating();
  MXApplication::activateScene(this);
}

void MXScene::deactivate() {
  if (!isActive()) {
    return;
  }
  onDeactivating();
  if (MXApplication::activeScene() == this) {
    MXApplication::activateScene(nullptr);
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
  onShow();
}
