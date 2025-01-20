#pragma once

#include <mx.h>

#include "../views/status_bar.h"

class SelectAgentScene : public MXScene {
 public:
  void onInit() override {
    MXScene::onInit();

    StatusBar* statusBar = new StatusBar();
    statusBar->init();
    addSubview(statusBar);

    MXView* container = new MXView();
    container->init();
    container->root()->size_full()->scroll_bar_auto();
    addSubview(container);

    for (int i = 0; i < 3; i++) {
      MXView* view = new MXView();
      view->init();
      view->root()->bg(rgb(255, 0, 0));
      view->root()->size(196, 256);
      view->root()->center_x()->y(35 + i * 256 + i * 10);
      container->addSubview(view);
    }
  }
};
