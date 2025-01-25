#include "agent_card.h"

#define AGENT_CARD_W 188
#define AGENT_CARD_H 224

void AgentCard::onInit() {
  MXView::onInit();

  root()
      ->size(AGENT_CARD_W, AGENT_CARD_H)
      ->rounded(AGENT_CARD_W / 10)
      ->clip_content();

  lv_obj_t* lv_card = root()->lv_object();
  lv_obj_set_style_transform_pivot_x(lv_card, AGENT_CARD_W / 2, LV_PART_MAIN);
  lv_obj_set_style_transform_pivot_y(lv_card, AGENT_CARD_H / 2, LV_PART_MAIN);

  background = root()->add_image("/spiffs/agent_card_bg.png");
  nameLabel = root()
                  ->add_label("", MX_FONT_SIZE_3XL)
                  ->center_x()
                  ->y(4)
                  ->text_opacity(0.67);
  avatarImage = root()->add_image()->align(LV_ALIGN_BOTTOM_MID);
}

void AgentCard::setAgentIndex(uint8_t index) {
  currentAgentIndex = index;
  const Agent* agent = AgentManager.agent(currentAgentIndex);
  nameLabel->text(agent->name);
  if (strlen(agent->name) > 10) {
    nameLabel->text(MX_FONT_SIZE_2XL);
  } else {
    nameLabel->text(MX_FONT_SIZE_3XL);
  }
  avatarImage->src(agent->avatar);
}

void AgentCard::translateY(float y) {
  lv_obj_t* lv_card = root()->lv_object();
  lv_obj_set_style_translate_y(lv_card, y, LV_PART_MAIN);
  root()->h(AGENT_CARD_H - y);
}
