#pragma once

#include <mx.h>
#include <wifi_connector.h>

class StatusBar : public MXView {
 public:
  void onInit() override;

  ~StatusBar() {
    delete timeLabel;
    delete right;
    delete wifiIndicator;
  }

 protected:
  MXObject *timeLabel;
  MXObject *right;
  MXObject *wifiIndicator;

  void onUpdate() override;

 private:
  time_t _nextUpdateTime = 0;
  WiFiConnectorState _lastWiFiState = WIFI_CONNECTOR_STATE_INITIAL;
  uint8_t _animationFrameIndex = 0;
  time_t _lastAnimationUpdateTime = 0;

  inline uint8_t _nextAnimationFrame() {
    _animationFrameIndex = (_animationFrameIndex + 1);
    if (_animationFrameIndex >= 6) {
      _animationFrameIndex = 0;
    }
    return _animationFrameIndex;
  }

  void _updateTime();
  void _updateWiFI();
};
