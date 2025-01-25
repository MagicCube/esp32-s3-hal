#include "status_bar.h"

#include <utils/time_formatter.h>

void StatusBar::onInit() {
  MXView::onInit();

  root()
      ->flex_row(LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER)
      ->w_full()
      ->h(17)
      ->pos(0, 0)
      ->p_x(24)
      ->y(12);

  timeLabel = root()->add_label()->font(&lv_font_montserrat_14);

  right = root()->add_object()->flex_row()->gap(8);
  wifiIndicator = right->add_label()->h(17)->p_y(0)->text_opacity(0.4)->font(
      &lv_font_montserrat_12);
}

void StatusBar::onUpdate() {
  _updateTime();
  _updateWiFI();
}

void StatusBar::_updateTime() {
  if (WiFiConnector.state() != WIFI_CONNECTOR_STATE_CONNECTED) {
    timeLabel->text("");
    return;
  }
  if (_nextUpdateTime == 0 || millis() > _nextUpdateTime) {
    struct tm timeInfo;
    if (!getLocalTime(&timeInfo, 1000 / 30)) {
      timeLabel->text("");
      return;
    }
    timeLabel->text(formatTime(timeInfo))->text_opacity(1);
    _nextUpdateTime = millis() + (60 - timeInfo.tm_sec + 1) * 1000;
  }
}

void StatusBar::_updateWiFI() {
  WiFiConnectorState state = WiFiConnector.state();
  if (state != WIFI_CONNECTOR_STATE_CONNECTING &&
      state != WIFI_CONNECTOR_STATE_SCANNING && _lastWiFiState == state) {
    return;
  }
  switch (state) {
    case WIFI_CONNECTOR_STATE_SCANNING:
      if (millis() > _lastAnimationUpdateTime + 300) {
        _lastAnimationUpdateTime = millis();
        switch (_nextAnimationFrame() % 3) {
          case 0:
            wifiIndicator->text(".")->text_opacity(0.5);
            break;
          case 1:
            wifiIndicator->text(". .  ")->text_opacity(0.5);
            break;
          case 2:
            wifiIndicator->text(". . .")->text_opacity(0.5);
            break;
        }
      }
      break;
    case WIFI_CONNECTOR_STATE_CONNECTING:
      if (millis() > _lastAnimationUpdateTime + 300) {
        _lastAnimationUpdateTime = millis();
        switch (_nextAnimationFrame() % 2) {
          case 0:
            wifiIndicator->text(LV_SYMBOL_WIFI)->text_opacity(0.2);
            break;
          case 1:
            wifiIndicator->text(LV_SYMBOL_WIFI)->text_opacity(0.5);
            break;
        }
      }
      break;
    case WIFI_CONNECTOR_STATE_CONNECTED:
      wifiIndicator->text(LV_SYMBOL_WIFI)->text_opacity(1);
      break;
    case WIFI_CONNECTOR_STATE_DISCONNECTED:
      wifiIndicator->text("!")->text(rgb(0xff0000));
      break;
  }
  _lastWiFiState = WiFiConnector.state();
}
