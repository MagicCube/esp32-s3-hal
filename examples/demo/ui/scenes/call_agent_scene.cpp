#include "call_agent_scene.h"

CallAgentScene* CallAgentScene::_instance = nullptr;

void CallAgentScene::onInit() {
  root()->bg_black();

  durationLabel = root()
                      ->add_label("00:00", MX_FONT_SIZE_SM)
                      ->w_full()
                      ->center_x(0, 28)
                      ->text_center()
                      ->text_secondary();
  nameLabel = root()
                  ->add_label("Amy", MX_FONT_SIZE_XL)
                  ->w_full()
                  ->center_x(0, 48)
                  ->text_center();
  avatarFrame = root()
                    ->add_object()
                    ->size(108, 108)
                    ->center_x(0, 82)
                    ->rounded(20)
                    ->clip_content()
                    ->border(8, lv_color_white(), 0.175);
  avatarImage =
      avatarFrame->add_image("/spiffs/avatar_wukong.png")->size_full();
  interruptButton = root()
                        ->add_button("\uf130")
                        ->icon_font(24)
                        ->size(60, 60)
                        ->align(LV_ALIGN_BOTTOM_LEFT, 16, -12)
                        ->text_white()
                        ->bg_white(0.2)
                        ->rounded_full();
  hangUpButton = root()
                     ->add_button("\uf095")
                     ->icon_font(24)
                     ->size(60, 60)
                     ->align(LV_ALIGN_BOTTOM_RIGHT, -16, -12)
                     ->text(rgb(0xFF3B2F))
                     ->bg_white()
                     ->rounded_full()
                     ->transform_origin_center()
                     ->transform_rotate(135);
}
