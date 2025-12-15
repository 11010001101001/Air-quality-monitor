#include "ServerManager.h"

ServerManager::ServerManager()
    : server(80)
{
}

String ServerManager::setup()
{
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout)
    {
        Serial.println("Connecting...");
        delay(1000);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        server.on("/air", [this]()
                  { handleRequest(); });
        server.begin();

        String ip = WiFi.localIP().toString();
        return "Connected " + ip;
    }
    else
    {
        Serial.println("Failed to connect, turning off WiFi...");
        WiFi.disconnect(true);
        WiFi.mode(WIFI_OFF);
        return "Failed to connect, turning off WiFi...";
    }
}

void ServerManager::serveClient()
{
    server.handleClient();
}

void ServerManager::updateAirQualityData(SensorsManager::AirQualityData d)
{
    data = d;
}

void ServerManager::handleRequest()
{
    bool noData = data.temp.isEmpty() && data.humidity.isEmpty() && data.co2.isEmpty() && data.pressure.isEmpty();

    if (noData)
    {
        server.send(400, "text/plain", "No data");
    }
    else
    {
        String json = "{\"temperature\":" + data.temp + "°C" +
                      ",\"humidity\":" + String(data.humidity) + "%" +
                      ",\"co2\":" + String(data.co2) + "ppm" +
                      ",\"pressure\":" + String(data.pressure) + "mm" + "}";
        server.send(200, "application/json", json);
    }
}
