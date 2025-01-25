#pragma once

#include <Arduino.h>

inline String formatTime(tm timeInfo) {
  String timeStr = String(timeInfo.tm_hour < 10 ? "0" : "") +
                   String(timeInfo.tm_hour) + String(":") +
                   String(timeInfo.tm_min < 10 ? "0" : "") +
                   String(timeInfo.tm_min);
  return timeStr;
}

inline String formatTimeSpan(time_t timeSpan) {
  int totalSeconds = timeSpan / 1000;
  int minutes = (totalSeconds % (60 * 60)) / 60;
  int seconds = totalSeconds % 60;
  return (minutes < 10 ? "0" : "") + String(minutes) + ":" +
         (seconds < 10 ? "0" : "") + String(seconds);
}
