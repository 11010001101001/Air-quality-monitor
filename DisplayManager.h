#pragma once
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "SensorsManager.h"

class DisplayManager
{
public:
    DisplayManager();
    void setup();
    void displayText(String data, int x, int y);
    void displayAirQualityData(SensorsManager::AirQualityData data);

private:
    const int width = 128;
    const int height = 64;
    const int OLED_DC = D3;
    const int OLED_RES = D4;
    const int OLED_CS = D8;

    Adafruit_SSD1306 display;
};