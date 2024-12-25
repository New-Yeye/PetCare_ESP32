#include "THSensor.h"

THSensor::THSensor() : 
    dht(15, DHT11),
    T(0),
    H(0)
    {}

THSensor::THSensor(int pin, int type) : 
    dht(pin, type),
    T(0),
    H(0)
    {}

void THSensor::begin() {
    dht.begin();
    update();
}

void THSensor::update() {
    T = dht.readTemperature();
    H = dht.readHumidity();
}


// Get
float THSensor::getTemperature() const {
    return T;
}

float THSensor::getHumidity() const {
    return H;
}