#pragma once
#include <Adafruit_BME280.h>
#include <SparkFun_SCD4x_Arduino_Library.h>

class SensorsManager
{
public:
    struct Parameter
    {
        String value;
        String displayValue;
    };

    struct AirQualityData
    {
        Parameter temp;
        Parameter humidity;
        Parameter co2;
        Parameter pressure;
    };

    void setup();
    AirQualityData collectAirQualityData();

private:
    Adafruit_BME280 bme280;
    SCD4x scd4x;
    float tempOffset = 3.5;

    String defineTempMood(float t);
    String definePressureMood(float p);
    String defineHumidityMood(float h);
    String defineCo2Mood(uint16_t co2);
    String pad(String &str, String last);
};