#pragma once

#include "../../utils/scale_map.h"
#include "agent_card.h"
#include "display.h"
#include "mx.h"

LV_IMAGE_DECLARE(img_agent_card_bottom);

class AgentCardRoller : public MXView {
 public:
  void show() { cards[1]->root()->scroll_into_view(false); }
  ~AgentCardRoller() {
    for (int i = 0; i < 3; i++) {
      delete cards[i];
    }
    delete bottom;
  }

 protected:
  AgentCard* cards[3] = {nullptr, nullptr, nullptr};
  MXObject* bottom;
  ScaleMap* opacityScaleMap0;
  ScaleMap* opacityScaleMap1_0;
  ScaleMap* opacityScaleMap1_2;
  ScaleMap* opacityScaleMap2;
  ScaleMap* translateYScaleMap0;
  ScaleMap* translateYScaleMap1_0;
  ScaleMap* translateYScaleMap1_2;
  ScaleMap* translateYScaleMap2;

  void onInit() override {
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
      cards[i]->setIndex(i);
      addSubview(cards[i]);
    }

    const float opacity_min = 0.4;
    opacityScaleMap0 = new ScaleMap(-4, 192, 1, opacity_min);
    opacityScaleMap1_0 = new ScaleMap(-4, 192, opacity_min, 1);
    opacityScaleMap1_2 = new ScaleMap(192, 388, 1, opacity_min);
    opacityScaleMap2 = new ScaleMap(192, 388, opacity_min, 1);

    const float translate_y_max = 24;
    translateYScaleMap0 = new ScaleMap(-4, 192, 0, translate_y_max);
    translateYScaleMap1_0 = new ScaleMap(-4, 192, translate_y_max, 0);
    translateYScaleMap1_2 = new ScaleMap(192, 388, 0, translate_y_max);
    translateYScaleMap2 = new ScaleMap(192, 388, translate_y_max, 0);

    bottom = root()
                 ->add_image(&img_agent_card_bottom)
                 ->size(img_agent_card_bottom.header.w,
                        img_agent_card_bottom.header.h)
                 ->center_x()
                 ->y(192)
                 ->image_scale(1.1);
    bottom->add_flag(LV_OBJ_FLAG_FLOATING);
  }

  void updateCards() {
    if (cards[0] == nullptr) return;

    int32_t scrollX = root()->scroll_x();
    cards[0]->translateY(translateYScaleMap0->scale(scrollX));
    cards[0]->root()->opacity(opacityScaleMap0->scale(scrollX));
    cards[2]->translateY(translateYScaleMap2->scale(scrollX));
    cards[2]->root()->opacity(opacityScaleMap2->scale(scrollX));
    if (scrollX <= 192) {
      cards[1]->translateY(translateYScaleMap1_0->scale(scrollX));
      cards[1]->root()->opacity(opacityScaleMap1_0->scale(scrollX));
    } else {
      cards[1]->translateY(translateYScaleMap1_2->scale(scrollX));
      cards[1]->root()->opacity(opacityScaleMap1_2->scale(scrollX));
    }
  }

  void handleScroll() { updateCards(); }

  void handleScrollEnd() {
    uint8_t nextIndex = (root()->scroll_x() + 4) / 196;
    // Serial.printf("ScrollEnd: %d\n", nextIndex);
  }
};
