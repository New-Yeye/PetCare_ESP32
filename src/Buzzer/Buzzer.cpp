#include "Buzzer.h"

Buzzer::Buzzer(uint8_t pin) : 
    pin(pin), 
    buzzerSwitch(true)
    {}

void Buzzer::begin() {
    pinMode(pin, OUTPUT);
    deactivate();
    beepTwice();
}


void Buzzer::setBuzzerSwitch(bool buzzerSwitch) {
    this->buzzerSwitch = buzzerSwitch;
}

void Buzzer::activate() {
    if (!buzzerSwitch) { return; }
    digitalWrite(pin, HIGH);
}

void Buzzer::deactivate() {
    digitalWrite(pin, LOW);
}

void Buzzer::toggle() {
    if (buzzerSwitch) {
        deactivate();
    } else {
        activate();
    }
}

void Buzzer::beepTwice() {
    if (!buzzerSwitch) { return; }
    activate();
    delay(100); // 蜂鸣器响100毫秒
    deactivate();
    delay(100); // 蜂鸣器静音100毫秒
    activate();
    delay(100); // 蜂鸣器响100毫秒
    deactivate();
}

void Buzzer::beepAlarm() {
    if (!buzzerSwitch) { return; }
    activate();
    delay(1000); // 蜂鸣器响1000毫秒
    deactivate();
}