/*
* Task Ending example for Arduino Tasker
* 
* This file implements all declared functions from CalculateDataTask.h
* 
* This task will be marked as finished when _sum >= 1 000 000
* but it wont be deleted from memory.
*
* It is safe to have external pointer, but make sure to free them when no loner needed.
* see main file
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#include <Arduino.h>
#include <Task.h>
#include "CalculateDataTask.h"

CalculateDataTask::CalculateDataTask(uint16_t id) : Task(id)
{
    // This marks task as "Do not delete"
    // TaskManager will not delete this task from memory
    this->doNotDelete();
}

CalculateDataTask::~CalculateDataTask()
{
    Serial.print("CalculateDataTask deleted");
}

void CalculateDataTask::update(uint32_t deltaT)
{
    // Add random value to _sum
    _sum += random(deltaT, random(0, 100000));

    if (_sum >= 1000000)
    {
        // Task marked as done
        // See main file
        this->finish();
    }
}

uint32_t CalculateDataTask::getResult()
{
    return _sum;
}