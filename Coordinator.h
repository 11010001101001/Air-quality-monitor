#pragma once
#include "DisplayManager.h"
#include "SensorsManager.h"
#include "ServerManager.h"

class Coordinator
{
public:
    void setup();
    void loop();

private:
    DisplayManager displayManager;
    SensorsManager sensorsManager;
    ServerManager serverManager;

    String ip;
};