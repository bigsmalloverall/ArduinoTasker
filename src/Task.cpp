#include "Task.h"

namespace SimpleTM
{
    Task::Task(uint16_t id, bool deleteWhenDone)
    {
        _id = id;

        _status = {0, deleteWhenDone ? (uint8_t)1 : (uint8_t)0};
    }

    Task::~Task()
    {
#ifdef ARDUINO_TASKER_DEBUG
        Serial.print("Task ");
        Serial.print(this->getId());
        Serial.println(" deleted");
#endif
    }

    uint16_t Task::getId()
    {
        return _id;
    }

    bool Task::isDone()
    {
        bool isDone = _status.isDone;
        return isDone;
    }

    bool Task::canBeDeleted()
    {
        bool deleteWhenDone = _status.deleteWhenDone;
        return deleteWhenDone;
    }

    void Task::doNotDelete()
    {
#ifdef ARDUINO_TASKER_DEBUG
        Serial.print("Task ");
        Serial.print(this->getId());
        Serial.println(" marked as \"Do not delete\"");
#endif
        _status.deleteWhenDone = 0;
    }

    void Task::finish()
    {
#ifdef ARDUINO_TASKER_DEBUG
        Serial.print("Task ");
        Serial.print(this->getId());
        Serial.println(" is done");
#endif
        _status.isDone = 1;
    }

    uint32_t Task::getLastUpdateTime()
    {
        return _lastUpdate;
    }

    void Task::endUpdate()
    {
        _lastUpdate = micros();
    }

    void Task::cache()
    {
    }

} // namespace SimpleTM