/*
* Blink example for Simple Task Manager
* 
* This example shows how to create task that blinks LED every 1 second.
* Begin at LedBlinkTask.h and LedBlinkTask.cpp then see CustomTaskPool.h 
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/SimpleTaskManager
*/

#include <Arduino.h>
#include <pins_arduino.h>
#include <SimpleTaskManager.h>
#include <TasksPool.h>
#include "CustomTaskPool.h"

const uint8_t ledPin = LED_BUILTIN; // Const from pins_arduino can be any arduino pin.

using namespace SimpleTM;

SimpleTaskManager *manager;

void setup()
{
    Serial.begin(9600);
    manager = new SimpleTaskManager(new CustomTaskPool());
    manager->startTask(0);
}

void loop()
{
    manager->update();
}