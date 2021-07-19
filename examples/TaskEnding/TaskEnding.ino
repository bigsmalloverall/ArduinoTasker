/*
* Task Ending example for Arduino Tasker
* 
* This example shows different ways to end tasks.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#include <Arduino.h>
#include <TaskManager.h>
#include "DoSomethingTask.h"
#include "SerialLoopTask.h"
#include "CalculateDataTask.h"

using namespace ArduinoTasker;

TaskManager manager;

// Global pointer to Task 2 initialised as nullptr
CalculateDataTask *dataTask = nullptr;

void setup()
{
    Serial.begin(9600);
    while (!Serial); // Wait for serial to start
    
    Serial.println("init");

    // Task 0
    // This task will finnish after 1 000 000 loops. TaskManager will delete it form memory.
    manager.startTaskByPointer(new DoSomethingTask(0));
    Serial.println("Task 0 started!");

    // Task 1
    // This task does not have ending condition, but in can be stopped and deleted from memopry manually.
    // See loop() below.
    manager.startTaskByPointer(new SerialLoopTask(1));
    Serial.println("Task 1 started!");

    // Task 2
    // This task will finish after 1 000 000 loops, but it wont be deleted from memory. You need to do it manually. 
    // It is usefoul when task is calculating some data you wan to use later.
    dataTask = new CalculateDataTask(2); // New instance of task
    manager.startTaskByPointer(dataTask);
    Serial.println("Task 2 started!");
}

void loop()
{
    manager.update();

    // Task 1
    // Stop task 1 at random (simulates some external logic)
    // Second part makes sure this if will not be triggered again,
    // so serial print is not printhing the same.
    if ((uint8_t)random(0, 100) > 60 && manager.doesTaskExist(1))
    {
        // If task does not exist this function will do nothing
        // so if this if is triggered again nothing would happen
        manager.stopTask(1);
        Serial.println("Task 1 manually stopped!");
    }
    
    // Task 2
    // Enter if statement only if Task 2 still exists and i's done
    // Internal state is still managed by TaskManager, but we can access task directly
    if (dataTask != nullptr && dataTask->isDone())
    {
        uint32_t result = dataTask->getResult();

        // Output result
        Serial.println("Task 2 result: ");
        Serial.println(result);

        // Cleanup
        // This is important!
        manager.stopTask(2);
        //dataTask = nullptr;
    }
}