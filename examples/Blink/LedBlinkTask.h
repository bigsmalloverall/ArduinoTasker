#include <Task.h>

class LedBlinkTask : public ArduinoTasker::Task
{
private:
    // Internal state cholders:
    bool _ledState{false};  // Current state of LED
    uint8_t _ledPin{0};     // Pin of LED
    uint32_t _frameTime{0}; // Delay duration
    uint32_t _sumDeltaT{0}; // Delay interval

public:

    // id: Task id
    // pin: LED pin
    // delay: Delay in us between state changes
    LedBlinkTask(uint16_t id, uint8_t ledPin, uint32_t frameTime = 1000000);
    ~LedBlinkTask();

    // Update is called every loop from main.cpp
    // deltaT is time in us from last time update() was called
    void update(uint32_t deltaT);
};