#pragma once

#include <display.h>
#include <mx.h>

#include "../../agents/agent_manager.h"
#include "../../utils/scale_map.h"
#include "agent_card.h"

class AgentCardRoller : public MXView {
 public:
  ~AgentCardRoller() {
    for (int i = 0; i < 3; i++) {
      delete cards[i];
      cards[i] = nullptr;
    }
    delete bottom;
    delete opacityScaleMap0;
    delete opacityScaleMap1_0;
    delete opacityScaleMap1_2;
    delete opacityScaleMap2;
    delete translateYScaleMap0;
    delete translateYScaleMap1_0;
    delete translateYScaleMap1_2;
    delete translateYScaleMap2;
  }

  void show();

  void setAgentIndex(uint8_t index);

  void next();

  void prev();

 protected:
  uint8_t currentAgentIndex = 0;
  MXObject* bottom;
  ScaleMap* opacityScaleMap0;
  ScaleMap* opacityScaleMap1_0;
  ScaleMap* opacityScaleMap1_2;
  ScaleMap* opacityScaleMap2;
  ScaleMap* translateYScaleMap0;
  ScaleMap* translateYScaleMap1_0;
  ScaleMap* translateYScaleMap1_2;
  ScaleMap* translateYScaleMap2;

  const float OPACITY_MIN = 0.4;
  const float TRANSLATE_Y_MAX = 24;

  AgentCard* cards[3] = {nullptr, nullptr, nullptr};

  void onInit() override;

  void updateCards();
  void updateCardsWhileScrolling();

  void handleScroll();
  void handleScrollEnd();
};
