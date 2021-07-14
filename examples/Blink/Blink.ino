#include <Arduino.h>

#include <TaskManager.h>
#include <TasksPool.h>
#include <Task.h>
#include "LedBlinkTask.h"

#define LED_PIN 13

using namespace ArduinoTasker;

class Tasks : public TasksPool
{
public:
    Task *tasks(uint16_t id)
    {
        switch (id)
        {
        case 0:
            return new LedBlinkTask(0, LED_PIN);

        default:
            return nullptr;
        }
    }

    uint16_t count()
    {
        return 1;
    }
};

TaskManager *manager;

void setup()
{
    manager = new TaskManager(new Tasks());
    manager->startTask(0);
}

void loop()
{
    manager->update();
}