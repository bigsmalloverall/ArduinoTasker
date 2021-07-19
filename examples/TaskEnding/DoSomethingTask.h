/*
* Task Ending example for Arduino Tasker
* 
* Header file declaring all needed variables and functions.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#ifndef ARDUINO_TASKER_DO_SOMETHING_TASK
#define ARDUINO_TASKER_DO_SOMETHING_TASK

#include <Arduino.h>
#include <Task.h>

class DoSomethingTask : public ArduinoTasker::Task
{
private:
    uint32_t _currentLoop {0}; 

public:
    DoSomethingTask(uint16_t id);
    ~DoSomethingTask();

    // Update is called every loop from main.cpp
    // deltaT is time in us from last time update() was called
    void update(uint32_t deltaT);
};

#endif