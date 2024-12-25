#include "WiFiModule.h"

WiFiModule::WiFiModule(const char* ssid, const char* password)
    : ssid(ssid), password(password) {}

void WiFiModule::connect() {
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
} 