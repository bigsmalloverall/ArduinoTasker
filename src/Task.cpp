#include "Task.h"

namespace ArduinoTasker
{
    Task::Task(uint16_t id)
    {
        _id = id;
    }

    uint16_t Task::getId()
    {
        return _id;
    }

    bool Task::isDone()
    {
        return _isDone;
    }

    void Task::finish()
    {
        _isDone = true;
    }

    uint32_t Task::getLastUpdateTime()
    {
        return _lastUpdate;
    }

    void Task::endUpdate()
    {
        _lastUpdate = micros();
    }

    void Task::cache() {

    }

} // namespace ArduinoTasker