/*
* Task Ending example for Simple Task Manager
* 
* Header file declaring all needed variables and functions.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/SimpleTaskManager
*/

#ifndef ARDUINO_TASKER_CALCULATE_DATA_TASK
#define ARDUINO_TASKER_CALCULATE_DATA_TASK

#include <Arduino.h>
#include <Task.h>

class CalculateDataTask : public SimpleTM::Task
{
private:
    uint32_t _sum {0};

public:
    CalculateDataTask(uint16_t id);
    ~CalculateDataTask();
    
    // Update is called every loop from main.cpp
    // deltaT is time in us from last time update() was called
    void update(uint32_t deltaT);

    // Result of _sum
    uint32_t getResult();
};

#endif