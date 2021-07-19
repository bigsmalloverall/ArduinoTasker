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

#ifndef ARDUINO_TASKER_CACHE_DATA_TASK
#define ARDUINO_TASKER_CACHE_DATA_TASK

#include <Arduino.h>
#include <Task.h>

class CacheDataTask : public ArduinoTasker::Task
{
private:
    uint8_t _lottoCodes[6]; // This is place for cache to be placed

public:
    CacheDataTask(uint16_t id);
    
    // Update is called every loop from main.cpp
    // deltaT is time in us from last time update() was called
    void update(uint32_t deltaT);

    // Cache is called before update every loop
    void cache();
};

#endif