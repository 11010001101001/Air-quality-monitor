#pragma once
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "SensorsManager.h"

class ServerManager
{
public:
    ServerManager();
    String setup();
    void serveClient();
    void updateAirQualityData(SensorsManager::AirQualityData data);

private:
    const char *ssid = "TP-Link_27D4";
    const char *password = "78877467";
    const unsigned long timeout = 10000;
    const unsigned long startAttemptTime = millis();

    ESP8266WebServer server;
    SensorsManager::AirQualityData data;

    void handleRequest();
};