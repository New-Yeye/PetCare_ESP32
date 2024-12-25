#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <Arduino.h>
#include <PubSubClient.h>

class MQTTClient {
public:
    MQTTClient(const char* server, uint16_t port, const char* user, const char* password, Client& client);
    void begin();
    void publish(const char* message, const char* topic);
    void subscribe(const char* topic = nullptr);
    void loop();
    bool isConnected();
    void reconnect();

    String recentTopic;   // 最近接收的主题
    String recentMessage; // 最近接收的消息内容

private:
    PubSubClient mqttClient;
    const char* server;
    uint16_t port;
    const char* user;
    const char* password;
    const char* defaultTopic;
};

#endif // MQTT_CLIENT_H 