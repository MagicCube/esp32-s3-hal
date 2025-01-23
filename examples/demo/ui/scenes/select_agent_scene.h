#pragma once

#include <button.h>
#include <mx.h>

#include "../views/agent_card_roller.h"
#include "../views/status_bar.h"

class SelectAgentScene : public MXScene {
 public:
  ~SelectAgentScene() {
    delete agentCardRoller;
    delete statusBar;
    delete callButton;
    delete rollButton;
  }

 protected:
  AgentCardRoller* agentCardRoller;
  StatusBar* statusBar;
  MXObject* callButton;
  Button* rollButton;

  void onInit() override {
    MXScene::onInit();

    agentCardRoller = new AgentCardRoller();
    agentCardRoller->init();
    agentCardRoller->root()->size_full();
    addSubview(agentCardRoller);

    statusBar = new StatusBar();
    statusBar->init();
    addSubview(statusBar);

    callButton = root()->add_button("\uf095")->icon_font(24);
    callButton->size(60, 60)
        ->align(LV_ALIGN_BOTTOM_MID, 0, -12)
        ->bg(rgb(0x31C959))
        ->rounded_full();

    rollButton = new Button(0);
    rollButton->begin();
    rollButton->onClick([this](MXEvent* e) { agentCardRoller->prev(); });
  }

  void onShow() override {
    MXScene::onShow();

    agentCardRoller->show();
  }

  void onUpdate() override {
    MXScene::onUpdate();

    rollButton->update();
  }
};
