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

    delay(8000);
}

void Coordinator::loop()
{
    SensorsManager::AirQualityData data = sensorsManager.collectAirQualityData();
    serverManager.updateAirQualityData(data);
    serverManager.serveClient();
    displayManager.displayAirQualityData(data);

    delay(60000);
}
