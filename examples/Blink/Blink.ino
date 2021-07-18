/*
* Blink example for Arduino Tasker
* 
* This example shows how to create task that blinks LED every 1 second.
* Begin at LedBlinkTask.h and LedBlinkTask.cpp then see CustomTaskPool.h 
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#include <Arduino.h>
#include <TaskManager.h>
#include <TasksPool.h>
#include "CustomTaskPool.h"

using namespace ArduinoTasker;

TaskManager *manager;

void setup()
{
    Serial.begin(9600);
    Serial.begin(9600);
    delay(1000);
    
    Serial.println("init");
    manager = new TaskManager(new CustomTaskPool());
    manager->startTask(0);
}

void loop()
{
    manager->update();
}