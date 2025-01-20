#pragma once

#include "mx.h"

class StatusBar : public MXView {
 public:
  void onInit() override {
    MXView::onInit();

    root()
        ->flex_row(LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER)
        ->w_full()
        ->h(15)
        ->pos(0, 0)
        ->p_x(24)
        ->y(12);

    timeLabel = root()->add_label("12:18");

    right = root()->add_object()->flex_row()->gap(8);
    wifiIndicator = right->add_label(LV_SYMBOL_WIFI);
    batteryIndicator = right->add_label(LV_SYMBOL_BATTERY_FULL);
  }

  ~StatusBar() {
    delete timeLabel;
    delete right;
    delete wifiIndicator;
    delete batteryIndicator;
  }

 protected:
  MXObject *timeLabel;
  MXObject *right;
  MXObject *wifiIndicator;
  MXObject *batteryIndicator;
};
