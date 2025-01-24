#pragma once

#include <Arduino.h>

#include <vector>

enum WiFiConnectorState {
  WIFI_CONNECTOR_STATE_INITIAL,
  WIFI_CONNECTOR_STATE_SCANNING,
  WIFI_CONNECTOR_STATE_CONNECTING,
  WIFI_CONNECTOR_STATE_CONNECTED,
  WIFI_CONNECTOR_STATE_DISCONNECTED,
};

struct KnownSSID {
  String ssid;
  String password;
};

class WiFiConnectorClass {
 public:
  inline WiFiConnectorState state() { return _state; }
  inline String connectedSSID() { return _connectedSSID; }

  void addKnownSSID(const String& ssid, const String& password);

  void begin();
  void end();
  void update();

 protected:
  void setState(WiFiConnectorState newState);
  void scan();
  void connect(const String& ssid, const String& password);
  void onScanResult(int n);

 private:
  WiFiConnectorState _state = WIFI_CONNECTOR_STATE_INITIAL;
  String _connectedSSID = "";
  std::vector<KnownSSID> _knownSSIDList;
};

extern WiFiConnectorClass WiFiConnector;
