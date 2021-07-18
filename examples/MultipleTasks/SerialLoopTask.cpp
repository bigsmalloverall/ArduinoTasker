/*
* Blink example for Arduino Tasker
* 
* Header file declaring all needed variables and functions.
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