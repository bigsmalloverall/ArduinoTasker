#include <TaskManager.h>
#include "CustomTaskPool.h"

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