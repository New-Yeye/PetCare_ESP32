#include "LED.h"

LED::LED(uint8_t pinR, uint8_t pinG, uint8_t pinB) : 
    pinR(pinR), 
    pinG(pinG), 
    pinB(pinB), 
    LEDSwitch(true), 
    colorR(0), 
    colorG(255), 
    colorB(0) 
    {}

void LED::begin() {
    pinMode(pinR, OUTPUT);
    pinMode(pinG, OUTPUT);
    pinMode(pinB, OUTPUT);
    colorfulBlink();
}

void LED::on() {
    if (!LEDSwitch) { return; }
    analogWrite(pinR, colorR);
    analogWrite(pinG, colorG);
    analogWrite(pinB, colorB);
}

void LED::off() {
    analogWrite(pinR, 0);
    analogWrite(pinG, 0);
    analogWrite(pinB, 0);
}

void LED::setColor(uint8_t r, uint8_t g, uint8_t b) {
    colorR = r;
    colorG = g;
    colorB = b;
    if (LEDSwitch) {
        on();  // 更新颜色
    }
} 

void LED::blinkTwice() {
    if (!LEDSwitch) { return; }
    on();
    delay(400);
    off();
    delay(200);
    on();
    delay(400);
    off();
}

void LED::alarm() {
    if (!LEDSwitch) { return; }
    analogWrite(pinR, 255);
}

void LED::colorfulBlink() {
    // 红色
    analogWrite(pinR, 255);
    analogWrite(pinG, 0);
    analogWrite(pinB, 0);
    delay(200);
    
    // 橙色
    analogWrite(pinR, 255);
    analogWrite(pinG, 127);
    analogWrite(pinB, 0);
    delay(200);
    
    // 黄色
    analogWrite(pinR, 255);
    analogWrite(pinG, 255);
    analogWrite(pinB, 0);
    delay(200);
    
    // 绿色
    analogWrite(pinR, 0);
    analogWrite(pinG, 255);
    analogWrite(pinB, 0);
    delay(200);
    
    // 蓝色
    analogWrite(pinR, 0);
    analogWrite(pinG, 0);
    analogWrite(pinB, 255);
    delay(200);
    
    // 靛蓝色
    analogWrite(pinR, 75);
    analogWrite(pinG, 0);
    analogWrite(pinB, 130);
    delay(200);
    
    // 紫色
    analogWrite(pinR, 148);
    analogWrite(pinG, 0);
    analogWrite(pinB, 211);
    delay(200);
    
    // 最后关闭LED
    off();
}

void LED::setSwitch(bool state){
    LEDSwitch = state;
    if(LEDSwitch){
        colorfulBlink();
    }else{
        off();
    }
}