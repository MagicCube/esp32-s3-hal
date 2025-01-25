#pragma once

#include <button.h>
#include <mx.h>

#include "ui/scenes/home_scene.h"
#include "ui/views/status_bar.h"

class App : public MXApplication {
 protected:
  Button* homeButton;

  inline void onInit() override {
    statusBar = new StatusBar();
    statusBar->init();

    HomeScene::instance()->init();

    homeButton = new Button(0);
    homeButton->onClick([this](MXEvent* e) { handleHomeButtonClick(); });
    homeButton->begin();
  }

  inline void onStart() override { HomeScene::instance()->show(); }

  inline void onUpdate() override { homeButton->update(); }

  inline void handleHomeButtonClick() { HomeScene::instance()->show(); }
};

extern App app;
