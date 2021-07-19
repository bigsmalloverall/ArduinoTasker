/*
* Multiple tasks example for Arduino Tasker
* 
* This file implements all declared functions from LedBlinkTask.h
* 
* This task blinks led on ledPin around every second (or other interval) indefinitely.
*
* Because it is managed by TaskManager it is not safe to use external pointers.
* 
* by Jakub Wójcik 2021
* jakub.wojcik2017@gmail.com
* 
* https://github.com/bigsmalloverall/ArduinoTasker
*/

#include <Arduino.h>
#include "LedBlinkTask.h"

LedBlinkTask::LedBlinkTask(uint16_t id, uint8_t ledPin, uint32_t frameTime) : Task(id) // Task id passed to Task constructor
{
    _ledPin = ledPin;
    _frameTime = frameTime;  // Default time is 1 000 000 us = 1s
    pinMode(ledPin, OUTPUT); // Set ledPin as output;

    Serial.print("TASK_ID: ");
    Serial.print(id);
    Serial.print("\n LED_PIN: ");
    Serial.println(ledPin);
}

LedBlinkTask::~LedBlinkTask()
{
    // Turn off LED when task is destroyed
    digitalWrite(_ledPin, LOW);
}

void LedBlinkTask::update(uint32_t deltaT)
{
    // Delay without delay() function
    // If time passed is greater than the delay change LED state
    // It might be helpful to think of this as changing frame in animation
    if (_sumDeltaT > _frameTime)
    {
        Serial.print("TASK_ID: ");
        Serial.print(_id);
        Serial.println("\t Blink");
        digitalWrite(_ledPin, _ledState); // Write LED state
        _ledState = !_ledState;           // Change state to opposite
        _sumDeltaT = 0;                   // Reset time passed
    }

    _sumDeltaT += deltaT; // Accumulate how much time has passed
}