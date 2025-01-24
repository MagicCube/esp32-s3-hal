#pragma once

#include <Arduino.h>

inline String formatTime(tm timeInfo) {
  String timeStr =
      String(timeInfo.tm_hour < 10 ? "0" : "") + String(timeInfo.tm_hour) +
      ":" + String(timeInfo.tm_min < 10 ? "0" : "") + String(timeInfo.tm_min);
  return timeStr;
}
