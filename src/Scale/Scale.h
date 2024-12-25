#ifndef SCALE_H
#define SCALE_H

#include <Arduino.h>
#include <HX711.h>

class Scale {
public:
    Scale(uint8_t loadCellDoutPin, uint8_t loadCellSckPin);  // 构造函数
    void begin();
    float getWeight();

private:
    HX711 scale;
    uint8_t loadCellDoutPin;
    uint8_t loadCellSckPin;
};

#endif // SCALE_H 