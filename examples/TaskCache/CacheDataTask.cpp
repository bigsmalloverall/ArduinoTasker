/*
* Task Ending example for Arduino Tasker
* 
* This file implements all declared functions from CacheDataTask.h
* 
* This task needs to calculate some valuse and send them to some external device
* The process of calculation takes time, sometimes calculations 
* and simultaneous data sending may affect devices communication.
* 
* To avoid that you may use cache() method.
* Cache is called before update, so you can do your calculations there,
* and send data in next step.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#include <Arduino.h>
#include <Task.h>
#include "CacheDataTask.h"

CacheDataTask::CacheDataTask(uint16_t id) : Task(id)
{
}

void CacheDataTask::update(uint32_t deltaT)
{
    // Update just sends cached data
    
    Serial.print("New lotto code: ");

    for (uint8_t i = 0; i < 6; i++)
    {
        Serial.print(_lottoCodes[i]);
    }

    Serial.println();
}

void CacheDataTask::cache()
{
    // Cache calculates 6 "hard to crack" lottery numbers before they are send to external device
    for (uint8_t i = 0; i < 6; i++)
    {
        // Delay simulates hard to calculate task
        // In real usecase it is strongly advised to never use delay()!
        delay(500);
        _lottoCodes[i] = random(1, 49);
    }
}