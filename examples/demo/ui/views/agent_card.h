#pragma once

#include "mx.h"

LV_IMAGE_DECLARE(img_agent_card_bg);

#define AGENT_CARD_W 188
#define AGENT_CARD_H 224

class AgentCard : public MXView {
 public:
  ~AgentCard() { delete background; }

  void setIndex(uint8_t index) {
    if (index == 0) {
      nameLabel->text("Optimus Prime");
      avatarImage->src("/spiffs/avatar_optimus_prime.png");
    } else if (index == 1) {
      nameLabel->text("Wukong");
      avatarImage->src("/spiffs/avatar_wukong.png");
    } else if (index == 2) {
      nameLabel->text("张飞");
      avatarImage->src("/spiffs/avatar_zhang_fei.png");
    }
  }

  void translateY(float y) {
    lv_obj_t* lv_card = root()->lv_object();
    lv_obj_set_style_translate_y(lv_card, y, LV_PART_MAIN);
    root()->h(AGENT_CARD_H - y);
  }

 protected:
  MXObject* avatarImage;
  MXObject* nameLabel;
  MXObject* background;

  void onInit() override {
    MXView::onInit();

    root()
        ->size(AGENT_CARD_W, AGENT_CARD_H)
        ->rounded(AGENT_CARD_W / 10)
        ->clip_content();

    lv_obj_t* lv_card = root()->lv_object();
    lv_obj_set_style_transform_pivot_x(lv_card, AGENT_CARD_W / 2, LV_PART_MAIN);
    lv_obj_set_style_transform_pivot_y(lv_card, AGENT_CARD_H / 2, LV_PART_MAIN);

    background = root()->add_image(&img_agent_card_bg);
    nameLabel = root()
                    ->add_label("", MX_FONT_SIZE_3XL)
                    ->center_x()
                    ->y(4)
                    ->text_opacity(0.67);
    avatarImage = root()->add_image()->align(LV_ALIGN_BOTTOM_MID);
  }
};
