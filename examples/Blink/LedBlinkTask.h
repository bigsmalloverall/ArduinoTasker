#include "Task.h"

class LedBlinkTask : public ArduinoTasker::Task
{
private:
    bool _ledState{false};
    uint8_t _ledPin{0};
    uint32_t _frameTime{0};
    uint32_t _sumDeltaT{0};

public:
    /**
     * @param  id: Task id
     * @param  pin: LED pin
     * @param  delay: Delay in us between state changes
     * @retval 
     */
    LedBlinkTask(uint16_t id, uint8_t pin, uint32_t frameTime = 1000000);
    ~LedBlinkTask();
    void update(uint32_t deltaT);
    void cache();
};
