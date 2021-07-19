/*
* Task Ending example for Simple Task Manager
* 
* This file implements all declared functions from SerialLoopTask.h
* 
* This task will run indefinitely, until stopeed externally.
* 
* Because it is managed by SimpleTaskManager it is not safe to use external pointers.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/SimpleTaskManager
*/

#include <Arduino.h>
#include <Task.h>
#include "SerialLoopTask.h"

SerialLoopTask::SerialLoopTask(uint16_t id) : SimpleTM::Task(id)
{

}

SerialLoopTask::~SerialLoopTask()
{
    Serial.print("Task ");
    Serial.print(this->getId());
    Serial.println(" deleted");
}

void SerialLoopTask::update(uint32_t deltaT)
{
    if (_accumulatedDt >= _dt)
    {
        Serial.println("=== SerialLoopTask===\n1 seconds passed!\n");
        _accumulatedDt = 0;
    }

    _accumulatedDt += deltaT;
}