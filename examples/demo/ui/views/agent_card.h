#pragma once

#include "agents/agent_manager.h"
#include "mx.h"

class AgentCard : public MXView {
 public:
  inline ~AgentCard() { delete background; }

  inline uint8_t agentIndex() { return currentAgentIndex; }

  void setAgentIndex(uint8_t index);

  void translateY(float y);

 protected:
  uint8_t currentAgentIndex;
  MXObject* avatarImage;
  MXObject* nameLabel;
  MXObject* background;

  void onInit() override;
};
