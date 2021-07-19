/*
* Task Caching example for Arduino Tasker
* 
* This example shows how cache() function can be used inside task
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#include <Arduino.h>
#include <TaskManager.h>
#include "CacheDataTask.h"

using namespace ArduinoTasker;

TaskManager manager;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ; // Wait for serial to start

    Serial.println("init");

    /**
     * Task 0
     * This task needs to calculate some valuse and send them to some external device
     * The process of calculation takes time, sometimes calculations 
     * and simultaneous data sending may affect devices communication.
     * 
     * To avoid that you may use cache() method.
     * Cache is called before update, so you can do your calculations there,
     * and send data in next step.
     * 
     * See CacheDataTask.h and CacheDataTask.cpp
     */
    manager.startTaskByPointer(new CacheDataTask(0));
}

void loop()
{
    manager.update();
}