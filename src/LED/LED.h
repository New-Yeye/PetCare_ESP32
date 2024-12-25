#ifndef LED_H
#define LED_H

#include <Arduino.h>

class LED {
public:
    LED(uint8_t pinR, uint8_t pinG, uint8_t pinB);  // 构造函数
    void begin();
    void on();
    void off();
    void setColor(uint8_t r, uint8_t g, uint8_t b);  // 设置颜色
    void blinkTwice();
    void alarm();
    void colorfulBlink();
    void setSwitch(bool state);

private:
    uint8_t pinR, pinG, pinB;  // RGB 引脚
    bool LEDSwitch;            // LED 开关状态
    uint8_t colorR, colorG, colorB;  // 当前颜色值
};

#endif // LED_H 