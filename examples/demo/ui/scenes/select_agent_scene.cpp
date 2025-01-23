#include "select_agent_scene.h"

#include "./call_agent_scene.h"

SelectAgentScene* SelectAgentScene::_instance = nullptr;

void SelectAgentScene::onInit() {
  MXScene::onInit();

  root()->bg_black();

  agentCardRoller = new AgentCardRoller();
  agentCardRoller->init();
  agentCardRoller->root()->size_full();
  addSubview(agentCardRoller);

  callButton = root()
                   ->add_button("\uf095")
                   ->icon_font(24)
                   ->size(60, 60)
                   ->align(LV_ALIGN_BOTTOM_MID, 0, -12)
                   ->bg(rgb(0x31C959))
                   ->rounded_full()
                   ->on_click([this](MXEvent* e) { handleCallButtonClick(); });

  rollButton = new Button(0);
  rollButton->begin();
  rollButton->onClick([this](MXEvent* e) { agentCardRoller->prev(); });

  agentCardRoller->show();
}

void SelectAgentScene::onUpdate() {
  MXScene::onUpdate();

  rollButton->update();
}

void SelectAgentScene::handleCallButtonClick() {
  CallAgentScene::instance()->show();
}
