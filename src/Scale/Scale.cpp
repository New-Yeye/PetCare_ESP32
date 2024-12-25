#include "Scale.h"

Scale::Scale(uint8_t loadCellDoutPin, uint8_t loadCellSckPin) : 
    loadCellDoutPin(loadCellDoutPin), 
    loadCellSckPin(loadCellSckPin)
    {}

void Scale::begin() {
    scale.begin(loadCellDoutPin, loadCellSckPin);
    scale.set_scale(1000);  // 设置初始比例因子
    scale.tare();       // 重置秤，忽略已有的重量
}

float Scale::getWeight() {
    return scale.get_units(10);  // 读取重量，可以调整参数以改善精度
} 