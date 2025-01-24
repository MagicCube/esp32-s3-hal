#pragma once

#include <time.h>

bool wifi_connected = false;

void wifi_setup() {
  WiFiConnector.addKnownSSID("Henry's Living Room 2.4GHz", "13913954971");
  WiFiConnector.addKnownSSID("Henry's iPhone 14 Pro", "13913954971");
  WiFiConnector.begin();
}

void wifi_loop() {
  WiFiConnector.update();
  if (!wifi_connected &&
      WiFiConnector.state() == WIFI_CONNECTOR_STATE_CONNECTED) {
    wifi_connected = true;
  }
}
