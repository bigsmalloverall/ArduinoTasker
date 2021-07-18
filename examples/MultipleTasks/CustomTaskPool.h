/*
* Blink example for Arduino Tasker
* 
* TasksPool is collection of class templates. 
* It’s main function is to easily iterate through your task and load them to memory only when they are needed.
* 
* In this example there is only one task with unique id of 0.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#ifndef ARDUINO_TASKER_CUSTOM_TASKS_POOL
#define ARDUINO_TASKER_CUSTOM_TASKS_POOL

#include <Arduino.h>
#include <TasksPool.h>
#include <Task.h>
#include "LedBlinkTask.h"
#include "SerialLoopTask.h"

extern const uint8_t ledPin;
extern const uint8_t ledPin2;

class CustomTaskPool : public ArduinoTasker::TasksPool
{
public:
    ArduinoTasker::Task *tasks(uint16_t id)
    {   
        // Make sure the ids are unique!
        switch (id)
        {
            // Case index should be equal to task id
            case 0:
                // Task id as first parameter
                // ledPin is constant from global scope
                // This task will blink ledPin every 1 s
                return new LedBlinkTask(0, ledPin, 1000000);
            
            case 1:
                // ledPin2 is constant from global scope
                // This task will blink ledPin2 every 0,5 s
                return new LedBlinkTask(1, ledPin2, 500000);
            
            case 2:
                // This task will print "1000000 loops!" every 1000000 loops
                return new SerialLoopTask(2);

            default:
                // If id is invalid return nullptr
                // TaskManager function startTask() will return false
                // meaning the task failed to start.
                // It can also be a default task.
                return nullptr;
        }
    }

    uint16_t count()
    {
        // Make sure to update this number!

        // This value needs to be incremented manually and 
        // should be equal to the number of cases in switch
        return 3;
    }
};

#endif