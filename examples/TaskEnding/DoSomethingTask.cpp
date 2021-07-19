/*
* Task Ending example for Arduino Tasker
* 
* This file implements all declared functions from DoSomethingTask.h
* 
* This task will be marked as finished when _currentLoop >= 5 000
* and automatically deleted from memory.
*
* Because it is managed by TaskManager it is not safe to use external pointers.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#include <Arduino.h>
#include <Task.h>
#include "DoSomethingTask.h"

DoSomethingTask::DoSomethingTask(uint16_t id) : ArduinoTasker::Task(id)
{
    // Making sure that serial is working
    if (!Serial)
    {
        Serial.begin(9600);
    }
}

DoSomethingTask::~DoSomethingTask() {
    Serial.print("DoSomethingTask deleted");
}

void DoSomethingTask::update(uint32_t deltaT)
{
    if (_currentLoop >= 5000)
    {
        Serial.print("=== DoSomethingTask ===\n5000 loops elapsed, I'm done!");
        this->finish(); // Mark task as finished
    }

    _currentLoop++;
}