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

#ifndef ARDUINO_TASKER_CACHE_DATA_TASK
#define ARDUINO_TASKER_CACHE_DATA_TASK

#include <Arduino.h>
#include <Task.h>

class CacheDataTask : public SimpleTM::Task
{
private:
    // This is place for cache to be placed
    // default value [0, ...]
    uint8_t _lottoCodes[6] {0, 0, 0, 0, 0, 0};

public:
    CacheDataTask(uint16_t id);
    
    // Update is called every loop from main.cpp
    // deltaT is time in us from last time update() was called
    void update(uint32_t deltaT);

    // Cache is called before update every loop
    void cache();
};

#endif