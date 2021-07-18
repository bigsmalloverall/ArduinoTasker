#ifndef ARDUINO_STATUS
#define ARDUINO_STATUS

#include <Arduino.h>

namespace ArduinoTasker
{
    struct Status
    {
        uint8_t isDone : 1;
        uint8_t deleteWhenDone : 1;
    };
    
} // namespace ArduinoTasker


#endif