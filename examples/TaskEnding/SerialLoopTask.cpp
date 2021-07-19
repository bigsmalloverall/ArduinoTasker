/*
* Task Ending example for Arduino Tasker
* 
* This file implements all declared functions from SerialLoopTask.h
* 
* This task will run indefinitely, until stopeed externally.
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
#include "SerialLoopTask.h"

SerialLoopTask::SerialLoopTask(uint16_t id) : ArduinoTasker::Task(id)
{
    // Making sure that serial is working
    if (!Serial)
    {
        Serial.begin(9600);
    }
}

SerialLoopTask::~SerialLoopTask()
{
    Serial.print("SerialLoopTask deleted");
}

void SerialLoopTask::update(uint32_t deltaT)
{
    if (_accumulatedDt >= _dt)
    {
        Serial.println("=== SerialLoopTask===\nOne second passed!");
        _accumulatedDt = 0;
    }

    _accumulatedDt += deltaT;
}