#include "Controller.h"

Controller::Controller() : 
    T_L(30), 
    H_L(70), 
    W_L(99), 

    AlarmSwitch(true) 
    {}


// Get and Set
void Controller::setTemperatureThreshold(float threshold) {
    T_L = threshold;
}

float Controller::getTemperatureThreshold() const {
    return T_L;
}

void Controller::setHumidityThreshold(float threshold) {
    H_L = threshold;
}

float Controller::getHumidityThreshold() const {
    return H_L;
}

void Controller::setWeightThreshold(float threshold) {
    W_L = threshold;
}

float Controller::getWeightThreshold() const {
    return W_L;
}

void Controller::setAlarmSwitch(bool state) {
    AlarmSwitch = state;
}

bool Controller::getAlarmSwitch() const {
    return AlarmSwitch;
} 