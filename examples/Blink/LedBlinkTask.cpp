#include "LedBlinkTask.h"

LedBlinkTask::LedBlinkTask(uint16_t id, uint8_t pin, uint32_t frameTime = 1000000) : Task(id)
{
    _ledPin = pin;
    _frameTime = frameTime;
    pinMode(pin, OUTPUT);
}

LedBlinkTask::~LedBlinkTask()
{
    digitalWrite(_ledPin, LOW);
}

void LedBlinkTask::update(uint32_t deltaT)
{
    if (_sumDeltaT > _frameTime)
    {
        digitalWrite(_ledPin, _ledState);
        _ledState = !_ledState;
        _sumDeltaT = 0;
    }

    _sumDeltaT += deltaT;
}

void LedBlinkTask::cache() {}