// 标准库
#include <Arduino.h>
#include <Wire.h>
#include <ArduinoJson.h>
// 模块库
#include "config.h"
#include "Controller/Controller.h"
#include "OLED/oled.h"
#include "T_H/THSensor.h"
#include "Buzzer/Buzzer.h"
#include "LED/LED.h"
#include "Fan/Fan.h"
#include "Scale/Scale.h"
#include "MQTT/MQTTClient.h"
#include "WIFI/WiFiModule.h"
// 模块设定
OLED oled;
THSensor thSensor(15, 11);
Controller controller;
Buzzer buzzer(2);
LED led(5, 18, 19);
Fan fan(23);
Scale scale(16, 4);
WiFiModule wifiModule("XXZ", "77777777");
WiFiClient espClient;
MQTTClient mqttClient("121.37.134.5", 1883, "esp", "qwexz233", espClient);
// 初始化
void setup()
{
    // 系统初始化
    Serial.begin(115200);
    Wire.begin();
    Serial.println("系统初始化成功！");
    // LED模块初始化
    led.begin();
    Serial.println("LED模块初始化成功！");
    // OLED模块初始化
    if (!oled.begin())
    {
        Serial.println("OLED初始化失败！");
    }
    else
    {
        Serial.println("OLED初始化成功！");
    }
    // DHT11传感器初始化
    thSensor.begin();
    Serial.println("DHT11传感器初始化成功！");
    // 有源蜂鸣器初始化
    buzzer.begin();
    Serial.println("有源蜂鸣器初始化成功！");
    // 风扇初始化
    fan.begin();
    Serial.println("风扇初始化成功！");
    // 称重传感器初始化
    scale.begin();
    Serial.println("称重传感器初始化成功！");
    // WiFi连接
    wifiModule.connect();
    // MQTT客户端初始化
    mqttClient.begin();
}
void loop()
{
    // MQTT客户端连接稳定性检测
    if (!mqttClient.isConnected()) {
        Serial.println("MQTT not connected. Attempting to reconnect...");
        mqttClient.reconnect();
    }
    mqttClient.loop();
    // 数据更新
    thSensor.update();
    float W = scale.getWeight();
    float T = thSensor.getTemperature();
    float H = thSensor.getHumidity();
    // MQTT消息处理
    if(mqttClient.recentTopic != ""){
        if(mqttClient.recentMessage != "\"\""){
        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, mqttClient.recentMessage);
        
        if (error) {
            Serial.print("报文并非JSON格式: ");
            Serial.println(error.c_str());
        }
        led.blinkTwice();
        buzzer.beepTwice();
        // 喂食系统
        if(mqttClient.recentTopic == "Pet/Phone/Feed"){
            if(doc.containsKey("max")){
                controller.setWeightThreshold(doc["max"].as<float>());
            }else if(doc.containsKey("save")){
                String message = "{\"feedValue\": " + String(scale.getWeight(), 0) + "}";
                mqttClient.publish(message.c_str(), "Pet/ESP/Feed");
            }
        }
        // 温湿度控制系统
        else if(mqttClient.recentTopic == "Pet/Phone/Env"){
            if(doc.containsKey("tMax") && doc.containsKey("hMax")){
                controller.setTemperatureThreshold(doc["tMax"].as<float>());
                controller.setHumidityThreshold(doc["hMax"].as<float>());
            }
        }
        // 报警系统
        else if(mqttClient.recentTopic == "Pet/Phone/Alarm"){
            if(doc.containsKey("open")){
                if(doc["open"].as<String>() == "true"){
                    controller.setAlarmSwitch(true);
                }else{
                    controller.setAlarmSwitch(false);
                    oled.setAlarmType(0);
                    led.off();
                    buzzer.deactivate();
                }
            }
        }
        // OLED系统
        else if(mqttClient.recentTopic == "Pet/Phone/OLED"){
            if(doc.containsKey("open")){
                if(doc["open"].as<String>() == "true"){
                    oled.setSwitch(true);
                }else{
                    oled.setSwitch(false);
                }
            }else if(doc.containsKey("font")){
                oled.setFont(doc["font"].as<int>());
            }else if(doc.containsKey("color")){
                if(doc["color"].as<String>() == "true"){
                    oled.setColor(OledColor::INVERTED);
                }else{
                    oled.setColor(OledColor::NORMAL);
                }
            }
        }
        // LED系统
        else if(mqttClient.recentTopic == "Pet/Phone/LED"){
            if(doc.containsKey("open")){
                if(doc["open"].as<String>() == "true"){
                    led.setSwitch(true);
                }else{
                    led.setSwitch(false);
                }
            }else if(doc.containsKey("r")){
                led.setColor(doc["r"].as<int>(), doc["g"].as<int>(), doc["b"].as<int>());
            }
        }
        // 风扇系统
        else if(mqttClient.recentTopic == "Pet/Phone/Fan"){
            if(doc.containsKey("open")){
                if(doc["open"].as<String>() == "true"){
                    fan.setFanSwitch(true);
                }else{
                    fan.setFanSwitch(false);
                }
            }else if(doc.containsKey("state")){
                fan.setPower(doc["state"].as<int>());
            }
        }
        // 蜂鸣器系统
        else if(mqttClient.recentTopic == "Pet/Phone/Buzzer"){
            if(doc.containsKey("open")){
                if(doc["open"].as<String>() == "true"){
                    buzzer.setBuzzerSwitch(true);
                }else{
                    buzzer.setBuzzerSwitch(false);
                }
            }
        }
        }
        mqttClient.recentTopic = "";
        mqttClient.recentMessage = "";
    }
    // 报警检测
    if (controller.getAlarmSwitch())
    {
        if (T > controller.getTemperatureThreshold() || H > controller.getHumidityThreshold() || W > controller.getWeightThreshold())
        {
            buzzer.beepAlarm();
            led.alarm();
            if (H > controller.getHumidityThreshold())
            {
                oled.setAlarmType(3);
            }
            if (T > controller.getTemperatureThreshold())
            {
                oled.setAlarmType(2);
            }
            if (W > controller.getWeightThreshold())
            {
                oled.setAlarmType(1);
            }
        }else{
            oled.setAlarmType(0);
            led.off();
        }
    }
    //模块对数据进行处理
    oled.FinalShow(T, H, W, controller.getWeightThreshold() - W);
    
    static unsigned long lastPublishTime = 0;
    unsigned long currentTime = millis();
    if (currentTime - lastPublishTime >= 10000) {  // 每10秒发送一次
        String message = "{\"t\": " + String(thSensor.getTemperature(), 1) + ", \"h\": " + String(thSensor.getHumidity(), 1) + "}";
        mqttClient.publish(message.c_str(), "Pet/ESP/Env");
        lastPublishTime = currentTime;
    }
    // 高温时风扇开启降温模式
    if(T - controller.getTemperatureThreshold() >= 8){
        fan.setState(255);
    }else if(T - controller.getTemperatureThreshold() > 0){
        fan.setState(((T - controller.getTemperatureThreshold()) * 32));
        Serial.println(((T - controller.getTemperatureThreshold()) * 32));
    }else{
        fan.setState(0);
    }
    // 等待一段时间
    delay(500);
}
