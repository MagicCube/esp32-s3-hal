#include "home_scene.h"

HomeScene* HomeScene::_instance = nullptr;

void HomeScene::onInit() {
  MXScene::onInit();

  root()->bg_black();
}
