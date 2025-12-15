#include "DisplayManager.h"

DisplayManager::DisplayManager()
    : display(width, height, &SPI, OLED_DC, OLED_RES, OLED_CS)
{
}

void DisplayManager::displayText(String text, int x, int y)
{
    display.clearDisplay();
    display.setCursor(x, y);
    display.print(text);
    display.display();
}

void DisplayManager::displayAirQualityData(SensorsManager::AirQualityData data)
{
    display.clearDisplay();
    display.setCursor(0, 5);
    display.print(data.temp);

    display.setCursor(0, 20);
    display.print(data.humidity);

    display.setCursor(0, 35);
    display.print(data.pressure);

    display.setCursor(0, 50);
    display.print(data.co2);

    display.display();
}

void DisplayManager::setup()
{
    display.begin(SSD1306_SWITCHCAPVCC, false);
    display.invertDisplay(false);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.ssd1306_command(SSD1306_SETCONTRAST);
    display.ssd1306_command(10); // level from 0 to 255

    display.clearDisplay();
    display.setCursor(5, 20);
    display.print("Air quality measurer");

    display.setCursor(35, 35);
    display.print("Loading...");
    display.display();
}
