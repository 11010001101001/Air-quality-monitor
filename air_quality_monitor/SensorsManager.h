#pragma once
#include <Adafruit_BME280.h>
#include <SparkFun_SCD4x_Arduino_Library.h>

class SensorsManager
{
public:
    struct TempData
    {
        String value;
        String displayValue;
    };

    struct HumidityData
    {
        String value;
        String displayValue;
    };

    struct PressureData
    {
        String value;
        String displayValue;
    };

    struct Co2Data
    {
        String value;
        String displayValue;
    };

    struct AirQualityData
    {
        TempData temp;
        HumidityData humidity;
        Co2Data co2;
        PressureData pressure;
    };

    void setup();
    AirQualityData collectAirQualityData();

private:
    Adafruit_BME280 bme280;
    SCD4x scd4x;

    String defineTempMood(float t);
    String definePressureMood(float p);
    String defineHumidityMood(float h);
    String defineCo2Mood(uint16_t co2);
    String pad(String &str, String last);
};