#include "home_scene.h"

#include "select_agent_scene.h"

HomeScene* HomeScene::_instance = nullptr;

LV_IMG_DECLARE(img_home_scene_bg);

void HomeScene::onInit() {
  MXScene::onInit();

  root()->bg_black();

  button = root()
               ->add_button("\uf095")
               ->size(100, 100)
               ->center_x()
               ->y(94)
               ->rounded(26)
               ->bg(rgb(0x31C959))
               ->icon_font(48)
               ->on_click([this](MXEvent* e) {
                 SelectAgentScene::instance()->show();
               });
}
