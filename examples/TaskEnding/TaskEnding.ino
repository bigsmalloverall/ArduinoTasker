/*
* Task Ending example for Simple Task Manager
* 
* This example shows different ways to end tasks.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/SimpleTaskManager
*/

#include <Arduino.h>
#include <SimpleTaskManager.h>
#include "DoSomethingTask.h"
#include "SerialLoopTask.h"
#include "CalculateDataTask.h"

using namespace SimpleTM;

SimpleTaskManager manager;

// Global pointer to Task 2 initialised as nullptr
CalculateDataTask *dataTask = nullptr;

void setup()
{
    Serial.begin(9600);
    while (!Serial); // Wait for serial to start
    
    Serial.println("init");

    // Task 0
    // This task will finnish after 5000 loops. SimpleTaskManager will delete it form memory.
    manager.startTaskByPointer(new DoSomethingTask(0));
    Serial.println("Task 0 started!");

    // Task 1
    // This task does not have ending condition, but in can be stopped and deleted from memopry manually.
    // See loop() below.
    manager.startTaskByPointer(new SerialLoopTask(1));
    Serial.println("Task 1 started!");

    // Task 2
    // This task will finish after internal variable _sum has value >= 1 000 000, 
    // but it wont be deleted from memory. You need to do it manually, see loop() below.
    // It is usefoul when task is calculating some data you want to use it later.
    dataTask = new CalculateDataTask(2); // New instance of task
    manager.startTaskByPointer(dataTask);
    Serial.println("Task 2 started!");
}

void loop()
{
    manager.update();

    // Task 1
    // Stop task 1 at random point (simulates some external logic)
    // Second part makes sure this if statement will not be triggered again
    if ((uint8_t)random(0, 100) > 60 && manager.doesTaskExist(1))
    {
        // If task does not exist this function will do nothing
        // so if this if statement is triggered again nothing bad would happen
        manager.stopTask(1);

        Serial.println("Task 1 manually stopped!");
    }
    
    // Task 2
    // Enter if statement only if Task 2 still exists and is done
    // Internal state is still managed by SimpleTaskManager, but we can access task directly
    if (dataTask != nullptr && dataTask->isDone())
    {
        uint32_t result = dataTask->getResult();

        // Output result
        Serial.print("Task 2 result: ");
        Serial.println(result);

        // Cleanup
        // This is important!
        manager.removeTaskFromRunningTasks(dataTask->getId());
        delete dataTask;
        dataTask = nullptr;

        Serial.println("Task 2 manually stopped and deleted!");
    }
}