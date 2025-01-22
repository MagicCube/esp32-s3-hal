#pragma once

#include "mx.h"

LV_IMAGE_DECLARE(img_agent_card_bg);
LV_IMAGE_DECLARE(img_agent_amy);
LV_IMAGE_DECLARE(img_agent_bunny);
LV_IMAGE_DECLARE(img_agent_einstein);

class AgentCard : public MXView {
 public:
  ~AgentCard() { delete background; }

  void setIndex(uint8_t index) {
    if (index == 0) {
      nameLabel->text("绵羊兔");
      image->src(&img_agent_bunny);
    } else if (index == 1) {
      nameLabel->text("艾米");
      image->src(&img_agent_amy);
    } else if (index == 2) {
      nameLabel->text("爱因斯坦");
      image->src(&img_agent_einstein);
    }
  }

  void translateY(float y) {
    lv_obj_t* lv_card = root()->lv_object();
    lv_obj_set_style_translate_y(lv_card, y, LV_PART_MAIN);
    root()->h(img_agent_card_bg.header.h - y);
  }

 protected:
  MXObject* image;
  MXObject* nameLabel;
  MXObject* background;

  void onInit() override {
    MXView::onInit();

    root()
        ->size(img_agent_card_bg.header.w, img_agent_card_bg.header.h)
        ->rounded(img_agent_card_bg.header.w / 10)
        ->clip_content();

    lv_obj_t* lv_card = root()->lv_object();
    lv_obj_set_style_transform_pivot_x(lv_card, img_agent_card_bg.header.w / 2,
                                       LV_PART_MAIN);
    lv_obj_set_style_transform_pivot_y(lv_card, img_agent_card_bg.header.h / 2,
                                       LV_PART_MAIN);

    background = root()->add_image(&img_agent_card_bg);
    nameLabel = root()
                    ->add_label("", MX_FONT_SIZE_3XL)
                    ->center_x()
                    ->y(4)
                    ->text_opacity(0.67);
    image = root()->add_image(&img_agent_amy)->align(LV_ALIGN_BOTTOM_MID);
  }
};
