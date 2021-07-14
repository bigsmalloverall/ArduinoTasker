#include <TaskManager.h>
#include "CustomTaskPool.h"
#include "LedBlinkTask.h"

#define LED_PIN 13

using namespace ArduinoTasker;

TaskManager *manager;

void setup()
{
    manager = new TaskManager(new CustomTaskPool());
    manager->startTask(0);
}

void loop()
{
    manager->update();
}