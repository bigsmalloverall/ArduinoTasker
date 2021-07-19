/*
* Multiple tasks example for Simple Task Manager
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

    // Making sure that serial is working
    if (!Serial)
    {
        Serial.begin(9600);
    }
}

void SerialLoopTask::update(uint32_t deltaT)
{
    if (_currentLoop >= _loops)
    {
        Serial.print(_loops);
        Serial.println(" loops!");

        _currentLoop = 0;
    }

    _currentLoop++;
}