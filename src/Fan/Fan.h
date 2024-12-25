#ifndef FAN_H
#define FAN_H

#include <Arduino.h>

class Fan {
public:
    Fan(uint8_t pin);  // 构造函数
    void begin();
    void on();
    void off();
    void setPower(uint8_t power);  // 设置风扇功率
    void setFanSwitch(bool FanSwitch);
    void setState(uint8_t power);

private:
    uint8_t pin;       // 控制风扇的引脚
    bool FanSwitch;    // 风扇开关状态
    uint8_t FanPower;  // 风扇功率
};

#endif // FAN_H 