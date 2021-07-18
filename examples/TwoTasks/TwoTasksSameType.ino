/*
* Two tasks of the same type example for Arduino Tasker
* 
* This example shows how to run two (or more) taks of the same type. See CustomTasksPool.h
* This example is the same as Blink, but it blinks with two different LEDs in different intervals
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#define USE_TASKS_POOL // Comment this definition to use alternate tasks definition

#include <Arduino.h>
#include <TaskManager.h>
#include <TasksPool.h>
#include "CustomTaskPool.h"

const uint8_t ledPin = 8;  // LED on pin 8
const uint8_t ledPin2 = 9; // LED on pin 9

using namespace ArduinoTasker;

TaskManager *manager;

void setup()
{
    Serial.begin(9600);
    Serial.begin(9600);
    delay(1000);

    Serial.println("init");

#ifdef USE_TASKS_POOL
    // Use task pool to tell TaskManager what you wan to do
    manager = new TaskManager(new CustomTaskPool());
    manager->startAllTasks(); // This will star task 0 and 1
#else
    // Alternatively you can add tasks manuallty
    manager = new TaskManager();
    manager->startTaskByPointer(new LedBlinkTask(0, ledPin, 1000000)); // This task will blink ledPin every 1 s
    manager->startTaskByPointer(new LedBlinkTask(0, ledPin, 500000)); // This task will blink ledPin2 every 0,5 s
#endif
}

void loop()
{
    manager->update();
}