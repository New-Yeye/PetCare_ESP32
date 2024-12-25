#ifndef WIFI_MODULE_H
#define WIFI_MODULE_H

#include <Arduino.h>
#include <WiFi.h>  // 使用 ESP32 的 WiFi 库

class WiFiModule {
public:
    WiFiModule(const char* ssid, const char* password);
    void connect();

private:
    const char* ssid;
    const char* password;
};

#endif // WIFI_MODULE_H 