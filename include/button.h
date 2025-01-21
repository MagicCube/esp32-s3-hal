#pragma once

#include "mx/mx_object.h"

class Button : public MXObject {
 public:
  Button(uint8_t pin);

  inline bool isPressed() { return _pressed; }

  void begin();
  void update();

  void onPressed(mx_event_callback_t callback);
  void onReleased(mx_event_callback_t callback);
  void onClick(mx_event_callback_t callback);

 private:
  uint8_t _pin;
  bool _pressed;
  time_t _lastPressed;
  mx_event_callback_t _onPressedCallback;
  mx_event_callback_t _onReleasedCallback;
  mx_event_callback_t _onClickCallback;
};
