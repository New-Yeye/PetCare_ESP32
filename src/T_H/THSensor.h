#ifndef TH_SENSOR_H
#define TH_SENSOR_H

#include <DHT.h>

class THSensor {
private:
    DHT dht;
    float T;
    float H;

public:
    THSensor();
    THSensor(int pin, int type);  // 构造函数声明
    void begin();
    void update();

    float getTemperature() const;
    float getHumidity() const;
};

#endif 