/*
* Multiple tasks example for Arduino Tasker
* 
* This example shows how to run many (or more) takas of the same or different type. See CustomTasksPool.h
* This example is similar to Blink, but it blinks two different LEDs in different intervals
* there is also one additional task "SerialLoopTask"
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
#include "LedBlinkTask.h"
#include "SerialLoopTask.h"

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
    // Make sure the ids are unique!
    manager = new TaskManager();
    manager->startTaskByPointer(new LedBlinkTask(0, ledPin, 1000000)); // This task will blink ledPin every 1 s
    manager->startTaskByPointer(new LedBlinkTask(1, ledPin2, 500000)); // This task will blink ledPin2 every 0,5 s
    manager->startTaskByPointer(new SerialLoopTask(2));                // This task will print "1000000 loops!" every 1000000 loops
#endif
}

void loop()
{
    manager->update();
}