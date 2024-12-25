#ifndef BUZZER_H
#define BUZZER_H

#include <Arduino.h>

class Buzzer {
public:
    Buzzer(uint8_t pin);
    void begin();
    void activate();
    void deactivate();
    void toggle();
    
    void beepTwice();
    void beepAlarm();
    void setBuzzerSwitch(bool buzzerSwitch);
private:
    uint8_t pin;
    bool buzzerSwitch;
};

#endif // BUZZER_H 