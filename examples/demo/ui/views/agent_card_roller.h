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
  ScaleMap* scaleMap0;
  ScaleMap* opacityScaleMap0;
  ScaleMap* scaleMap1_0;
  ScaleMap* opacityScaleMap1_0;
  ScaleMap* scaleMap1_2;
  ScaleMap* opacityScaleMap1_2;
  ScaleMap* scaleMap2;
  ScaleMap* opacityScaleMap2;

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
      cards[i]->root()->y(36)->x(22 + 184 * i);
      cards[i]->setIndex(i);
      addSubview(cards[i]);
    }

    scaleMap0 = new ScaleMap(-4, 192, 1.0, 0.82);
    opacityScaleMap0 = new ScaleMap(-4, 192, 1, 0.4);
    scaleMap1_0 = new ScaleMap(-4, 192, 0.82, 1.0);
    opacityScaleMap1_0 = new ScaleMap(-4, 192, 0.4, 1);
    scaleMap1_2 = new ScaleMap(192, 388, 1.0, 0.82);
    opacityScaleMap1_2 = new ScaleMap(192, 388, 1, 0.4);
    scaleMap2 = new ScaleMap(192, 388, 0.82, 1.0);
    opacityScaleMap2 = new ScaleMap(192, 388, 0.4, 1);

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
    cards[0]->setScale(scaleMap0->scale(scrollX));
    cards[0]->root()->opacity(opacityScaleMap0->scale(scrollX));
    cards[2]->setScale(scaleMap2->scale(scrollX));
    cards[2]->root()->opacity(opacityScaleMap2->scale(scrollX));
    if (scrollX <= 192) {
      cards[1]->setScale(scaleMap1_0->scale(scrollX));
      cards[1]->root()->opacity(opacityScaleMap1_0->scale(scrollX));
    } else {
      cards[1]->setScale(scaleMap1_2->scale(scrollX));
      cards[1]->root()->opacity(opacityScaleMap1_2->scale(scrollX));
    }
  }

  void handleScroll() { updateCards(); }

  void handleScrollEnd() {
    uint8_t nextIndex = (root()->scroll_x() + 4) / 196;
    // Serial.printf("ScrollEnd: %d\n", nextIndex);
  }
};
