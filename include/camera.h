#pragma once

#include <Arduino.h>
#include <esp_camera.h>
#include <pin_conf.h>

#ifdef CAM_D0
class CameraClass {
 public:
  bool initialized() const { return _initialized; }
  inline bool isLiveViewing() const { return _liveViewing; }

  void begin();
  void update();
  void end();

  void startLiveView();
  void stopLiveView();

  uint8_t fps() const { return 24; };

 private:
  bool _initialized = false;
  bool _liveViewing = false;
  time_t _lastUpdateTime = 0;
};

extern CameraClass Camera;

#endif
