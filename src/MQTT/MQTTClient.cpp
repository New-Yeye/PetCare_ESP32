#include "MQTTClient.h"

MQTTClient::MQTTClient(const char* server, uint16_t port, const char* user, const char* password, Client& client): 
    mqttClient(client), 
    server(server), 
    port(port), 
    user(user), 
    password(password), 
    defaultTopic("Pet/Phone/#") 
    {}

void MQTTClient::begin() {
    mqttClient.setServer(server, port);
    mqttClient.setCallback([this](char* topic, byte* payload, unsigned int length) {
        this->recentTopic = String(topic);
        this->recentMessage = String((char*)payload, length);
        Serial.print("Message arrived [");
        Serial.print(this->recentTopic);
        Serial.print("] ");
        Serial.println(this->recentMessage);
    });
    reconnect();
}

void MQTTClient::publish(const char* message, const char* topic) {
    if (!mqttClient.connected()) reconnect();
    mqttClient.publish(topic, message);
}

void MQTTClient::subscribe(const char* topic) {
    if (!topic) topic = defaultTopic;
    if (!mqttClient.connected()) reconnect();
    mqttClient.subscribe(topic);
}

void MQTTClient::loop() {
    if (!mqttClient.connected()) {
        reconnect();
    }
    mqttClient.loop();
}

bool MQTTClient::isConnected() {
    return mqttClient.connected();
}

void MQTTClient::reconnect() {
    while (!mqttClient.connected()) {
        Serial.print("Attempting MQTT connection...");
        if (mqttClient.connect("ESP", user, password)) {
            Serial.println("connected");
            subscribe();
        } else {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
} 