#include "agent_card_roller.h"

void AgentCardRoller::onInit() {
  MXView::onInit();

  root()
      ->bg_black()
      ->scrollable(true)
      ->scroll_bar_hidden()
      ->scroll_snap_x(LV_SCROLL_SNAP_CENTER)
      ->add_flag(LV_OBJ_FLAG_SCROLL_ONE)
      ->on_scroll([this](MXEvent* e) { handleScroll(); })
      ->on_scroll_end([this](MXEvent* e) { handleScrollEnd(); });

  for (int i = 0; i < 3; i++) {
    cards[i] = new AgentCard();
    cards[i]->init();
    cards[i]->root()->y(36)->x(200 * i);
    cards[i]->setAgentIndex(i);
    addSubview(cards[i]);
  }

  opacityScaleMap0 = new ScaleMap(-26, 174, 1, OPACITY_MIN);
  opacityScaleMap1_0 = new ScaleMap(-26, 174, OPACITY_MIN, 1);
  opacityScaleMap1_2 = new ScaleMap(174, 374, 1, OPACITY_MIN);
  opacityScaleMap2 = new ScaleMap(174, 374, OPACITY_MIN, 1);

  translateYScaleMap0 = new ScaleMap(-26, 174, 0, TRANSLATE_Y_MAX);
  translateYScaleMap1_0 = new ScaleMap(-26, 174, TRANSLATE_Y_MAX, 0);
  translateYScaleMap1_2 = new ScaleMap(174, 374, 0, TRANSLATE_Y_MAX);
  translateYScaleMap2 = new ScaleMap(174, 374, TRANSLATE_Y_MAX, 0);

  bottom = root()
               ->add_image("/spiffs/agent_card_bottom.png")
               ->size(240 * 1.1, 136 * 1.1)
               ->center_x()
               ->y(Display.height() - 120)
               ->image_scale(1.1);
  bottom->add_flag(LV_OBJ_FLAG_FLOATING);
}

void AgentCardRoller::show() {
  if (currentAgentIndex == 0) {
    setAgentIndex(0);
  }
  updateCards();
}

void AgentCardRoller::setAgentIndex(uint8_t index) {
  currentAgentIndex = index;
  uint8_t prevIndex = (index == 0) ? AgentManager.agentCount() - 1 : index - 1;
  cards[0]->setAgentIndex(prevIndex);
  cards[1]->setAgentIndex(index);
  uint8_t nextIndex = (index == AgentManager.agentCount() - 1) ? 0 : index + 1;
  cards[2]->setAgentIndex(nextIndex);
}

void AgentCardRoller::next() {
  if (cards[2]) {
    cards[2]->root()->scroll_into_view();
  }
}

void AgentCardRoller::prev() {
  if (cards[0]) {
    cards[0]->root()->scroll_into_view();
  }
}

void AgentCardRoller::updateCards() {
  for (int i = 0; i < 3; i++) {
    cards[i]->root()->x(200 * i);
  }
  cards[0]->root()->opacity(OPACITY_MIN);
  cards[0]->translateY(TRANSLATE_Y_MAX);

  cards[1]->root()->opacity(1);
  cards[1]->translateY(0);

  cards[2]->root()->opacity(OPACITY_MIN);
  cards[2]->translateY(TRANSLATE_Y_MAX);

  cards[1]->root()->scroll_into_view(false);
}

void AgentCardRoller::updateCardsWhileScrolling() {
  if (cards[0] == nullptr) return;

  int32_t scrollX = root()->scroll_x();

  cards[0]->translateY(translateYScaleMap0->scale(scrollX));
  cards[0]->root()->opacity(opacityScaleMap0->scale(scrollX));
  cards[2]->translateY(translateYScaleMap2->scale(scrollX));
  cards[2]->root()->opacity(opacityScaleMap2->scale(scrollX));
  if (scrollX <= 174) {
    cards[1]->translateY(translateYScaleMap1_0->scale(scrollX));
    cards[1]->root()->opacity(opacityScaleMap1_0->scale(scrollX));
  } else {
    cards[1]->translateY(translateYScaleMap1_2->scale(scrollX));
    cards[1]->root()->opacity(opacityScaleMap1_2->scale(scrollX));
  }
}

void AgentCardRoller::handleScroll() { updateCardsWhileScrolling(); }

void AgentCardRoller::handleScrollEnd() {
  int32_t scrollX = root()->scroll_x();
  AgentCard* temp[3] = {cards[0], cards[1], cards[2]};
  if (scrollX == -26) {
    // =>
    cards[0] = temp[2];
    cards[1] = temp[0];
    cards[2] = temp[1];
    setAgentIndex(cards[1]->agentIndex());
    updateCards();
  } else if (scrollX == 374) {
    // <=
    cards[0] = temp[1];
    cards[1] = temp[2];
    cards[2] = temp[0];
    setAgentIndex(cards[1]->agentIndex());
    updateCards();
  }
}
