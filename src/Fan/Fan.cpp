#include "Fan.h"

Fan::Fan(uint8_t pin) : 
    pin(pin), 
    FanSwitch(false), 
    FanPower(100) 
    {}

void Fan::begin() {
    pinMode(pin, OUTPUT);
}

void Fan::on() {
    analogWrite(pin, FanPower);  // 使用PWM信号控制功率
}

void Fan::off() {
    analogWrite(pin, 255);  // 关闭风扇
}

void Fan::setPower(uint8_t power) {
    FanPower = 255-power;
    if (FanSwitch) {
        on();  // 更新功率
    }
} 

void Fan::setFanSwitch(bool switchState) {
    FanSwitch = switchState;
    if(FanSwitch){
        on();
    }else{
        off();
    }
}

void Fan::setState(uint8_t power) {
    if(FanSwitch) {
        on();
    }else{
        analogWrite(pin, 255-power);
    }
}