#pragma once

#include <wifi_connector.h>

void wifi_setup() {
  WiFiConnector.addKnownSSID("Henry's Living Room 2.4GHz", "13913954971");
  WiFiConnector.addKnownSSID("Henry's iPhone 14 Pro", "13913954971");
  WiFiConnector.begin();
}

void wifi_loop() { WiFiConnector.update(); }
