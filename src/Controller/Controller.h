#ifndef CONTROLLER_H
#define CONTROLLER_H

class Controller {
private:
    float T_L; // 温度阈值
    float H_L; // 湿度阈值
    float W_L; // 重量阈值
    bool AlarmSwitch; // 报警开关

public:
    Controller(); // 构造函数
    void Update(float T_A, float H_A);

    // Get and Set
    void setTemperatureThreshold(float threshold);
    float getTemperatureThreshold() const;
    void setHumidityThreshold(float threshold);
    float getHumidityThreshold() const;
    void setWeightThreshold(float threshold);
    float getWeightThreshold() const;
    void setAlarmSwitch(bool state);
    bool getAlarmSwitch() const;
};

#endif 