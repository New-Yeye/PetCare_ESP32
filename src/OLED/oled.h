#ifndef OLED_H
#define OLED_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED显示参数
#define SCREEN_WIDTH 128    // OLED显示宽度，单位：像素
#define SCREEN_HEIGHT 64    // OLED显示高度，单位：像素
#define OLED_RESET -1       // 复位引脚，-1表示与Arduino共用复位引脚
#define SCREEN_ADDRESS 0x3C // I2C地址，通常为0x3C或0x3D

// OLED显示颜色枚举
enum class OledColor {
    NORMAL,
    INVERTED
};

class OLED {
private:
    Adafruit_SSD1306 ssd1306;  // SSD1306显示控制器
    bool oledSwitch;     // OLED开关状态
    float oledFont;         // OLED字体大小
    OledColor oledColor;       // OLED显示颜色
    int alarmType;

public:
    OLED();

    bool begin();               // 初始化OLED
    void clear();               // 清除显示内容
    void display();             // 刷新显示
    void ShowProgressBar();
    void FinalShow(int T, int H, int W, int W_need);

    void setSwitch(bool state);    // 设置开关状态
    bool getSwitch() const;        // 获取开关状态

    void setFont(float font);         // 设置字体大小
    float getFont() const;            // 获取字体大小

    void setColor(OledColor color);      // 设置显示颜色
    OledColor getColor() const;          // 获取显示颜色

    void setAlarmType(int type);         // 设置报警类型
    int getAlarmType() const;           // 获取报警类型
};

#endif 