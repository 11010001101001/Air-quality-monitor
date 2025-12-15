#include "SensorsManager.h"
#include <Wire.h>

void SensorsManager::setup()
{
    Serial.begin(115200);
    Wire.begin();
    Wire.setClock(100000);

    bool ok = bme280.begin(0x76);

    if (!ok)
    {
        Serial.println("BME280 not found");
    }

    if (!scd4x.begin())
    {
        Serial.println("SCD4x not found");
    }

    scd4x.startPeriodicMeasurement();
}

SensorsManager::AirQualityData SensorsManager::collectAirQualityData()
{
    float temp = bme280.readTemperature();
    float humidity = bme280.readHumidity();
    float pressure = (bme280.readPressure() / 100.0F) * 0.75006;

    Serial.print("t=");
    Serial.println(temp);
    Serial.print("h=");
    Serial.println(humidity);
    Serial.print("p=");
    Serial.println(pressure);

    uint16_t co2 = 0;
    float internal_temp = 0;
    float internal_humid = 0;

    if (scd4x.readMeasurement())
    {
        co2 = scd4x.getCO2();
        internal_temp = scd4x.getTemperature();
        internal_humid = scd4x.getHumidity();
        Serial.print("co2=");
        Serial.println(co2);
    }
    else
    {
        Serial.println("No new data yet");
    }

    String tempStr = "Temp: " + String(temp) + " C'";
    String humidityStr = "Humid: " + String(humidity) + " %";
    String co2Str = "Co2: " + String(co2) + " ppm";
    String pressureStr = "Press: " + String(pressure) + " mm";

    return SensorsManager::AirQualityData{
        pad(tempStr, defineTempMood(temp)),
        pad(humidityStr, defineHumidityMood(humidity)),
        pad(co2Str, defineCo2Mood(co2)),
        pad(pressureStr, definePressureMood(pressure))};
}

String SensorsManager::pad(String &str, String last)
{
    int lineLen = 19;
    int diff = lineLen - str.length();

    if (diff > 0)
    {
        for (int i = 0; i < diff; i++)
        {
            str += " ";
        }
    }
    str += last;
    return str;
}

String SensorsManager::defineTempMood(float t)
{
    // **Температура (°C)**
    // < 18 — прохладно
    // 18 – 24 — оптимум
    // > 24 — жарко
    if (t < 18)
    {
        return ":Z";
    }
    else if (t >= 18 && t <= 24)
    {
        return ":)";
    }
    else
    {
        return ":P";
    }
}

String SensorsManager::definePressureMood(float p)
{
    // ниже 735 мм рт. ст. (оч незкое)
    // 735 – 755 (понижено)
    // 755 – 765 (норма)
    // выше 765 (повышено)
    if (p < 735)
    {
        return "vv";
    }
    else if (p >= 735 && p <= 755)
    {
        return "v";
    }
    else if (p >= 755 && p <= 765)
    {
        return ":)";
    }
    else
    {
        return "^";
    }
}

String SensorsManager::defineHumidityMood(float h)
{
    // **Влажность (%)**
    // – < 40 — сухо
    // – 40 – 60 — идеал
    // – > 60 — влажно
    if (h < 40)
    {
        return ":(";
    }
    else if (h >= 40 && h <= 60)
    {
        return ":)";
    }
    else
    {
        return ":'(";
    }
}

String SensorsManager::defineCo2Mood(uint16_t co2)
{
    // **CO₂ (ppm)**
    // – 0 – 800 — отлично, воздух свежий
    // – 800 – 1200 — нормально, но стоит проветрить
    // – 1200 – 2000 — плохо, концентрация растёт, снижается внимание
    // – > 2000 — очень плохо, нужно срочно проветрить
    if (co2 < 800)
    {
        return ":)";
    }
    else if (co2 >= 800 && co2 <= 1200)
    {
        return ":|";
    }
    else if (co2 >= 1200 && co2 <= 2000)
    {
        return ":(";
    }
    else
    {
        return ">:(";
    }
}
