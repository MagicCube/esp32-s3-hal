#include "wifi_connector.h"

#include <WiFi.h>
#include <time.h>

void WiFiConnectorClass::addKnownSSID(const String& ssid,
                                      const String& password) {
  _knownSSIDList.push_back({ssid, password});
}

void WiFiConnectorClass::begin() {
  _scanStartTime = millis();
  scan();
}

void WiFiConnectorClass::end() { setState(WIFI_CONNECTOR_STATE_INITIAL); }

void WiFiConnectorClass::update() {
  if (_state == WIFI_CONNECTOR_STATE_SCANNING) {
    int n = WiFi.scanComplete();
    if (n == WIFI_SCAN_RUNNING) {
      return;
    }
    onScanResult(n);
  } else if (_state == WIFI_CONNECTOR_STATE_CONNECTING) {
    if (WiFi.status() == WL_CONNECTED) {
      _connectedSSID = WiFi.SSID();
      setState(WIFI_CONNECTOR_STATE_CONNECTED);
      onConnected();
      Serial.printf("WiFiConnector is now connected to %s\n",
                    _connectedSSID.c_str());
    }
  }
}

void WiFiConnectorClass::scan() {
  if (_state == WIFI_CONNECTOR_STATE_SCANNING ||
      _state == WIFI_CONNECTOR_STATE_CONNECTING) {
    return;
  }

  setState(WIFI_CONNECTOR_STATE_SCANNING);
  WiFi.scanNetworks(true, false, false, 120UL);

  Serial.printf("WiFiConnector is scanning...");
}

void WiFiConnectorClass::connect(const String& ssid, const String& password) {
  if (_state == WIFI_CONNECTOR_STATE_CONNECTING) {
    return;
  }

  _connectedSSID = "";
  setState(WIFI_CONNECTOR_STATE_CONNECTING);
  WiFi.begin(ssid.c_str(), password.c_str());
  Serial.printf("WiFiConnector is connecting to %s\n", ssid.c_str());
}

void WiFiConnectorClass::setState(WiFiConnectorState newState) {
  _state = newState;
}

void WiFiConnectorClass::onScanResult(int n) {
  for (int i = 0; i < n; i++) {
    String ssid = WiFi.SSID(i);
    auto it = std::find_if(
        _knownSSIDList.begin(), _knownSSIDList.end(),
        [ssid](const KnownSSID& knownSSID) { return knownSSID.ssid == ssid; });
    if (it != _knownSSIDList.end()) {
      WiFi.scanDelete();
      Serial.printf("WiFiConnector found known SSID: %s\nConnecting...\n",
                    ssid.c_str());
      if (_state == WIFI_CONNECTOR_STATE_SCANNING) {
        connect(it->ssid, it->password);
      }
      return;
    }
  }
  WiFi.scanDelete();
  if (millis() - _scanStartTime > SCAN_TIMEOUT) {
    Serial.println("WiFiConnector scan timeout");
    setState(WIFI_CONNECTOR_STATE_INITIAL);
  }
}

void WiFiConnectorClass::onConnected() {
  Serial.println("WiFiConnector is updating time...");
  configTime(8 * 3600, 0, "cn.ntp.org.cn");
}

WiFiConnectorClass WiFiConnector;
