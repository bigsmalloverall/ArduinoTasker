#ifndef ARDUINO_STATUS
#define ARDUINO_STATUS

#include <Arduino.h>

namespace SimpleTM
{
    struct Status
    {
        uint8_t isDone : 1;
        uint8_t deleteWhenDone : 1;
    };
    
} // namespace SimpleTM


#endif