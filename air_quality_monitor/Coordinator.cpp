#include "Coordinator.h"
#include "DisplayManager.h"
#include "SensorsManager.h"
#include "ServerManager.h"

void Coordinator::setup()
{
    displayManager.setup();
    sensorsManager.setup();

    ip = serverManager.setup();
    displayManager.displayText(ip, 0, 0);

    delay(5000);
    measure();
}

void Coordinator::loop()
{
    serverManager.serveClient();
    unsigned long currentMillis = millis();
    bool isMinuteGone = currentMillis - previousMillis >= minute;

    if (isMinuteGone)
    {
        previousMillis = currentMillis;
        measure();
    }
}

void Coordinator::measure()
{
    SensorsManager::AirQualityData data = sensorsManager.collectAirQualityData();
    serverManager.updateAirQualityData(data);
    displayManager.displayAirQualityData(data);
}
