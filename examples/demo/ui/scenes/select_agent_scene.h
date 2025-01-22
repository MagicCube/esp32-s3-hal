#pragma once

#include <fonts/font_awesome.h>
#include <mx.h>

#include "../views/agent_card_roller.h"
#include "../views/status_bar.h"

class SelectAgentScene : public MXScene {
 public:
  ~SelectAgentScene() {
    delete agentCardRoller;
    delete statusBar;
    delete callButton;
  }

 protected:
  AgentCardRoller* agentCardRoller;
  StatusBar* statusBar;
  MXObject* callButton;

  void onInit() override {
    MXScene::onInit();

    agentCardRoller = new AgentCardRoller();
    agentCardRoller->init();
    agentCardRoller->root()->size_full();
    addSubview(agentCardRoller);

    statusBar = new StatusBar();
    statusBar->init();
    addSubview(statusBar);

    lv_font_t* lv_font_font_awesome_xl =
        lv_tiny_ttf_create_data(font_awesome, font_awesome_size, 24);
    callButton = root()->add_button("\uf095")->font(lv_font_font_awesome_xl);
    callButton->size(60, 60)
        ->align(LV_ALIGN_BOTTOM_MID, 0, -12)
        ->bg(rgb(0x31C959))
        ->rounded_full();
  }

  void onShow() override {
    MXScene::onShow();

    agentCardRoller->show();
  }
};
