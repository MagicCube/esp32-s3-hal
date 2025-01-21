#include "button.h"

Button::Button(uint8_t pin) : _pin(pin), _pressed(false) {}

void Button::begin() {
  pinMode(_pin, INPUT_PULLUP);
  _pressed = digitalRead(_pin) == LOW;
}

void Button::update() {
  bool state = digitalRead(_pin) == LOW;
  if (state != _pressed) {
    _pressed = state;
    if (state) {
      if (_onPressedCallback) {
        _onPressedCallback(
            new MXEvent(LV_EVENT_PRESSED, this, _onPressedCallback));
      }
      _lastPressed = millis();
    } else {
      if (_onReleasedCallback) {
        _onReleasedCallback(new MXEvent(LV_EVENT_RELEASED, this, nullptr));
      }
      if (_onClickCallback && millis() - _lastPressed <= 500) {
        _onClickCallback(new MXEvent(LV_EVENT_CLICKED, this, nullptr));
      }
    }
  }
}

void Button::onPressed(mx_event_callback_t callback) {
  _onPressedCallback = callback;
}

void Button::onReleased(mx_event_callback_t callback) {
  _onReleasedCallback = callback;
}

void Button::onClick(mx_event_callback_t callback) {
  _onClickCallback = callback;
}
