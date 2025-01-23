#pragma once

#include <Arduino.h>

#include "agent.h"

class AgentManagerClass {
 public:
  inline const Agent* agents() const { return _agents; }

  inline size_t agentCount() const { return sizeof(_agents) / sizeof(Agent); }

  inline const Agent* agent(const uint8_t index) {
    if (index >= agentCount()) {
      return nullptr;
    }
    return &_agents[index];
  }

 private:
  const Agent _agents[7] = {
      {"amy", "Amy", "/spiffs/avatar_amy.png"},
      {"bunny", "绵羊兔", "/spiffs/avatar_bunny.png"},
      {"einstein", "爱因斯坦", "/spiffs/avatar_einstein.png"},
      {"harry_potter", "哈利波特", "/spiffs/avatar_harry_potter.png"},
      {"optimus_prime", "擎天柱", "/spiffs/avatar_optimus_prime.png"},
      {"wukong", "孙悟空", "/spiffs/avatar_wukong.png"},
      {"zhang_fei", "张飞", "/spiffs/avatar_zhang_fei.png"},
  };
};

extern AgentManagerClass AgentManager;
