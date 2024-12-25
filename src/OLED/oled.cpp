#include "oled.h"

static const uint8_t PROGMEM T[] ={
    0x00,0x00,0x23,0xF8,0x12,0x08,0x12,0x08,0x83,0xF8,0x42,0x08,0x42,0x08,0x13,0xF8,0x10,0x00,0x27,0xFC,
    0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x00,0x00,    //  [0], "温",Size:32, W16×H16, addr:0x0000
    0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,0x23,0xE0,0x20,0x00,
    0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E,    //  [1], "度",Size:32, W16×H16, addr:0x0020
};

static const uint8_t PROGMEM H[] = {
    0x00,0x00,0x27,0xF8,0x14,0x08,0x14,0x08,0x87,0xF8,0x44,0x08,0x44,0x08,0x17,0xF8,0x11,0x20,0x21,0x20,
    0xE9,0x24,0x25,0x28,0x23,0x30,0x21,0x20,0x2F,0xFE,0x00,0x00,    //  [0], "湿",Size:32, W16×H16, addr:0x0000
    0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,0x23,0xE0,0x20,0x00,
    0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E,    //  [1], "度",Size:32, W16×H16, addr:0x0020
};

static const uint8_t PROGMEM W[] = {
    0x00,0x10,0x00,0xF8,0x3F,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x1F,0xF0,0x11,0x10,0x1F,0xF0,0x11,0x10,
    0x1F,0xF0,0x01,0x00,0x3F,0xF8,0x01,0x00,0xFF,0xFE,0x00,0x00,    //  [0], "重",Size:32, W16×H16, addr:0x0000
    0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0xFF,0xFE,0x00,0x00,0x1F,0xF0,0x11,0x10,0x1F,0xF0,
    0x11,0x10,0x1F,0xF0,0x01,0x00,0x1F,0xF0,0x01,0x00,0x7F,0xFC,    //  [1], "量",Size:32, W16×H16, addr:0x0020
};

static const uint8_t PROGMEM W_NEED[] = {
    0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x00,0x00,0xFF,0xFE,0x22,0x00,0x3E,0xF8,0x22,0x88,
    0x3E,0x90,0x22,0x50,0x2F,0x20,0xF2,0x50,0x42,0x88,0x03,0x06,    //  [0], "最",Size:32, W16×H16, addr:0x0000
    0x02,0x00,0x02,0x00,0x07,0xF0,0x08,0x20,0x38,0x40,0x04,0x80,0x03,0x40,0x0C,0x80,0x71,0xF8,0x02,0x08,
    0x0C,0x10,0x32,0x20,0x01,0x40,0x01,0x80,0x0E,0x00,0x70,0x00,    //  [1], "多",Size:32, W16×H16, addr:0x0020
};

static const uint8_t PROGMEM Alarm_food[] = {
    0x01,0x00,0x02,0x80,0x04,0x40,0x0A,0x20,0x31,0x18,0xDF,0xF6,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,
    0x10,0x08,0x11,0x90,0x10,0x60,0x12,0x10,0x14,0x08,0x18,0x04,    //  [0], "食",Size:32, W16×H16, addr:0x0000
    0x10,0x80,0x10,0x80,0x50,0x80,0x50,0xFC,0x7D,0x54,0x52,0x54,0x90,0x54,0x10,0x94,0x1C,0x94,0xF1,0x24,
    0x52,0x24,0x10,0x44,0x10,0x44,0x10,0x84,0x11,0x28,0x10,0x10,    //  [1], "物",Size:32, W16×H16, addr:0x0020
    0x10,0x00,0x10,0xF8,0x10,0x88,0x10,0x88,0xFC,0x88,0x11,0x06,0x12,0x00,0x15,0xFC,0x18,0x84,0x30,0x84,
    0xD0,0x48,0x10,0x50,0x10,0x20,0x10,0x50,0x50,0x88,0x23,0x06,    //  [2], "投",Size:32, W16×H16, addr:0x0040
    0x00,0x00,0x03,0xF8,0x7A,0x48,0x4A,0x48,0x4B,0xF8,0x4A,0x48,0x4A,0x48,0x4B,0xF8,0x48,0x00,0x4F,0xFE,
    0x7A,0x40,0x4A,0x44,0x02,0x28,0x02,0x90,0x03,0x08,0x02,0x06,    //  [3], "喂",Size:32, W16×H16, addr:0x0060
    0x08,0x00,0x09,0xFC,0x08,0x44,0x7E,0x44,0x08,0x44,0x08,0x94,0xFF,0x08,0x08,0xFC,0x28,0x84,0x28,0x84,
    0x2E,0x84,0x28,0xFC,0x28,0x00,0x58,0x00,0x4F,0xFE,0x80,0x00,    //  [4], "超",Size:32, W16×H16, addr:0x0080
    0x00,0x00,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0xFF,0xFE,0x00,0x00,0x1F,0xF0,0x11,0x10,0x1F,0xF0,
    0x11,0x10,0x1F,0xF0,0x01,0x00,0x1F,0xF0,0x01,0x00,0x7F,0xFC,    //  [5], "量",Size:32, W16×H16, addr:0x00A0
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [6], "！",Size:32, W16×H16, addr:0x00C0
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [7], "！",Size:32, W16×H16, addr:0x00E0
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [8], "！",Size:32, W16×H16, addr:0x0100
};

static const uint8_t PROGMEM Alarm_T[] = {
    0x00,0x00,0x23,0xF8,0x12,0x08,0x12,0x08,0x83,0xF8,0x42,0x08,0x42,0x08,0x13,0xF8,0x10,0x00,0x27,0xFC,
    0xE4,0xA4,0x24,0xA4,0x24,0xA4,0x24,0xA4,0x2F,0xFE,0x00,0x00,    //  [0], "温",Size:32, W16×H16, addr:0x0000
    0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,0x23,0xE0,0x20,0x00,
    0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E,    //  [1], "度",Size:32, W16×H16, addr:0x0020
    0x00,0x10,0x20,0x10,0x10,0x10,0x17,0xFE,0x00,0x10,0x00,0x10,0xF2,0x10,0x11,0x10,0x11,0x10,0x10,0x10,
    0x10,0x10,0x10,0x50,0x10,0x20,0x28,0x00,0x47,0xFE,0x00,0x00,    //  [2], "过",Size:32, W16×H16, addr:0x0040
    0x02,0x00,0x01,0x00,0xFF,0xFE,0x00,0x00,0x0F,0xE0,0x08,0x20,0x08,0x20,0x0F,0xE0,0x00,0x00,0x7F,0xFC,
    0x40,0x04,0x4F,0xE4,0x48,0x24,0x48,0x24,0x4F,0xE4,0x40,0x0C,    //  [3], "高",Size:32, W16×H16, addr:0x0060
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [4], "！",Size:32, W16×H16, addr:0x0080
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [5], "！",Size:32, W16×H16, addr:0x00A0
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [6], "！",Size:32, W16×H16, addr:0x00C0
};

static const uint8_t PROGMEM Alarm_H[] = {
    0x00,0x00,0x27,0xF8,0x14,0x08,0x14,0x08,0x87,0xF8,0x44,0x08,0x44,0x08,0x17,0xF8,0x11,0x20,0x21,0x20,
    0xE9,0x24,0x25,0x28,0x23,0x30,0x21,0x20,0x2F,0xFE,0x00,0x00,    //  [0], "湿",Size:32, W16×H16, addr:0x0000
    0x01,0x00,0x00,0x80,0x3F,0xFE,0x22,0x20,0x22,0x20,0x3F,0xFC,0x22,0x20,0x22,0x20,0x23,0xE0,0x20,0x00,
    0x2F,0xF0,0x24,0x10,0x42,0x20,0x41,0xC0,0x86,0x30,0x38,0x0E,    //  [1], "度",Size:32, W16×H16, addr:0x0020
    0x00,0x00,0x7F,0xFC,0x00,0x80,0x00,0x80,0x01,0x00,0x01,0x00,0x03,0x40,0x05,0x20,0x09,0x10,0x11,0x08,
    0x21,0x04,0x41,0x04,0x81,0x00,0x01,0x00,0x01,0x00,0x01,0x00,    //  [2], "不",Size:32, W16×H16, addr:0x0040
    0x00,0x78,0x23,0xC0,0x10,0x40,0x10,0x40,0x07,0xFE,0x00,0x40,0xF0,0x40,0x13,0xF8,0x12,0x08,0x12,0x08,
    0x12,0x08,0x13,0xF8,0x12,0x08,0x28,0x00,0x47,0xFE,0x00,0x00,    //  [3], "适",Size:32, W16×H16, addr:0x0060
    0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x80,0x04,0x1F,0xF0,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,
    0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0xFF,0xFE,0x00,0x00,    //  [4], "宜",Size:32, W16×H16, addr:0x0080
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [5], "！",Size:32, W16×H16, addr:0x00A0
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [6], "！",Size:32, W16×H16, addr:0x00C0
    0x00,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,0x10,0x00,
    0x00,0x00,0x00,0x00,0x10,0x00,0x10,0x00,0x00,0x00,0x00,0x00,    //  [7], "！",Size:32, W16×H16, addr:0x00E0
};

// OLED配置
OLED::OLED() : 
    ssd1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET),
    oledSwitch(true),
    oledFont(1),
    oledColor(OledColor::NORMAL),
    alarmType(0)
    {}

bool OLED::begin()
{
    // 初始化OLED显示屏
    if (!ssd1306.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
    {
        Serial.println(F("SSD1306初始化失败"));
        return false;
    }
    ShowProgressBar();
    setColor(OledColor::NORMAL);
    return true;
}

void OLED::clear()
{
    ssd1306.clearDisplay(); // 清除显示内容
}

// 显示
void OLED::display()
{
    if (oledSwitch)
    { // 仅在开启状态下刷新显示
        ssd1306.display();
    }
}

void OLED::ShowProgressBar()
{
    int i;
    ssd1306.setTextSize(2);
    ssd1306.setTextColor(SSD1306_WHITE);

    for (i = 0; i < 118; i++)
    {
        clear();

        ssd1306.setCursor(18, 48);
        ssd1306.println("loading...");

        ssd1306.drawRoundRect(0, 20, 128, 20, 5, SSD1306_WHITE);
        ssd1306.fillRoundRect(5, 25, i, 10, 2, SSD1306_WHITE);
        display();
        delay(30);
    }
}

void OLED::FinalShow(int T, int H, int W, int W_need)
{
    if(!oledSwitch){
        return;
    }

    clear();

    ssd1306.setTextSize(oledFont);  // 设置文本大小
    ssd1306.setTextColor(SSD1306_WHITE);  // 设置文本颜色

    // 显示“温度”汉字
    ssd1306.drawBitmap(0, 0, ::T, 16, 16, SSD1306_WHITE);  // 显示“温”
    ssd1306.drawBitmap(16, 0, ::T + 32, 16, 16, SSD1306_WHITE);  // 显示“度”

    // 显示温度值
    int textHeight = 8 * oledFont;  // 计算文本高度
    ssd1306.setCursor(34-oledFont, 0 + (16 - textHeight)/2 +2);  // 调整垂直位置以居中显示
    ssd1306.print(T);

    // 显示“湿度”汉字
    ssd1306.drawBitmap(64, 0, ::H, 16, 16, SSD1306_WHITE);  // 显示“湿”
    ssd1306.drawBitmap(80, 0, ::H + 32, 16, 16, SSD1306_WHITE);  // 显示“度”

    // 显示湿度值
    ssd1306.setCursor(98-oledFont, 0 + (16 - textHeight)/2 +2);  // 调整垂直位置以居中显示
    ssd1306.print(H);

    // 显示“重量”汉字
    ssd1306.drawBitmap(0, 24, ::W, 16, 16, SSD1306_WHITE);  // 显示“重”
    ssd1306.drawBitmap(16, 24, ::W + 32, 16, 16, SSD1306_WHITE);  // 显示“量”

    // 显示重量值
    ssd1306.setCursor(34-oledFont, 24 + (16 - textHeight)/2 +2);  // 调整垂直位置以居中显示
    ssd1306.print(W);

    // 显示“需求”汉字
    ssd1306.drawBitmap(64, 24, ::W_NEED, 16, 16, SSD1306_WHITE);  // 显示“还”
    ssd1306.drawBitmap(80, 24, ::W_NEED + 32, 16, 16, SSD1306_WHITE);  // 显示“需”

    // 显示需求值
    ssd1306.setCursor(98-oledFont, 24 + (16 - textHeight)/2 +2);  // 调整垂直位置以居中显示
    ssd1306.print(W_need);

    // 显示报警信息
    switch (alarmType)
    {
    case 1: // 食物投喂超量报警
        // 绘制警告图标(三角形带感叹号)
        ssd1306.fillTriangle(4, 60, 12, 48, 20, 60, SSD1306_WHITE); // 三角形外框
        ssd1306.fillRect(11, 52, 2, 4, SSD1306_BLACK); // 感叹号竖线
        ssd1306.fillRect(11, 57, 2, 2, SSD1306_BLACK); // 感叹号点
        
        ssd1306.drawBitmap(24, 48, ::Alarm_food, 16, 16, SSD1306_WHITE);  // 显示"食"
        ssd1306.drawBitmap(40, 48, ::Alarm_food + 32, 16, 16, SSD1306_WHITE);  // 显示"物"
        ssd1306.drawBitmap(56, 48, ::Alarm_food + 64, 16, 16, SSD1306_WHITE);  // 显示"投"
        ssd1306.drawBitmap(72, 48, ::Alarm_food + 96, 16, 16, SSD1306_WHITE);  // 显示"喂"
        ssd1306.drawBitmap(88, 48, ::Alarm_food + 128, 16, 16, SSD1306_WHITE);  // 显示"超"
        ssd1306.drawBitmap(104, 48, ::Alarm_food + 160, 16, 16, SSD1306_WHITE);  // 显示"量"
        break;
    case 2: // 温度过高报警
        // 绘制警告图标
        ssd1306.fillTriangle(4, 60, 12, 48, 20, 60, SSD1306_WHITE);
        ssd1306.fillRect(11, 52, 2, 4, SSD1306_BLACK);
        ssd1306.fillRect(11, 57, 2, 2, SSD1306_BLACK);
        
        ssd1306.drawBitmap(24, 48, ::Alarm_T, 16, 16, SSD1306_WHITE);  // 显示"温"
        ssd1306.drawBitmap(40, 48, ::Alarm_T + 32, 16, 16, SSD1306_WHITE);  // 显示"度"
        ssd1306.drawBitmap(56, 48, ::Alarm_T + 64, 16, 16, SSD1306_WHITE);  // 显示"过"
        ssd1306.drawBitmap(72, 48, ::Alarm_T + 96, 16, 16, SSD1306_WHITE);  // 显示"高"
        break;
    case 3: // 湿度不适宜报警
        // 绘制警告图标
        ssd1306.fillTriangle(4, 60, 12, 48, 20, 60, SSD1306_WHITE);
        ssd1306.fillRect(11, 52, 2, 4, SSD1306_BLACK);
        ssd1306.fillRect(11, 57, 2, 2, SSD1306_BLACK);
        
        ssd1306.drawBitmap(24, 48, ::Alarm_H, 16, 16, SSD1306_WHITE);  // 显示"湿"
        ssd1306.drawBitmap(40, 48, ::Alarm_H + 32, 16, 16, SSD1306_WHITE);  // 显示"度"
        ssd1306.drawBitmap(56, 48, ::Alarm_H + 64, 16, 16, SSD1306_WHITE);  // 显示"不"
        ssd1306.drawBitmap(72, 48, ::Alarm_H + 96, 16, 16, SSD1306_WHITE);  // 显示"适"
        ssd1306.drawBitmap(88, 48, ::Alarm_H + 128, 16, 16, SSD1306_WHITE);  // 显示"宜"
        break;
    default:
        break;
    }

    // 刷新显示
    ssd1306.display();
}


// OLED状态设置
void OLED::setSwitch(bool state)
{
    oledSwitch = state;
    if (!oledSwitch)
    { // 关闭时清除显示
        ssd1306.clearDisplay();
        ssd1306.display();
    }
}

bool OLED::getSwitch() const
{
    return oledSwitch;
}

void OLED::setFont(float font)
{
    oledFont = font;
}

float OLED::getFont() const
{
    return oledFont;
}

void OLED::setColor(OledColor color)
{
    oledColor = color;
    if (oledColor == OledColor::NORMAL)
    {
        ssd1306.invertDisplay(false);
    }
    else
    {
        ssd1306.invertDisplay(true);
    }
}

OledColor OLED::getColor() const
{
    return oledColor;
}

void OLED::setAlarmType(int type)
{
    alarmType = type;
}

int OLED::getAlarmType() const
{
    return alarmType;
}