#ifndef ARDUINO_TASKS_TASK
#define ARDUINO_TASKS_TASK

#include <Arduino.h>

namespace ArduinoTasker
{
    class Task
    {
    public:
        /**
         * @brief  Task constructor
         * @param  id: id of task
         */
        Task(uint16_t id);

        /**
         * @retval id of task
         */
        uint16_t getId();

        /**
         * @retval Snapshot of millis() counter from last update call
         */
        uint32_t getLastUpdateTime();

        /**
         * @retval If this task has finished
         */
        bool isDone();

        /**
         * @brief  Stops task execution, prepares it to be deleted
         * @note   
         */
        void finish();

        /**
         * @brief Update states like I/O
         * @note   It can be used for calculations if CPU has small RAM
         * @param  deltaT: Time in us from last update
         */
        virtual void update(uint32_t deltaT) = 0;

        /**
         * @brief  Allows to cache in memory all necessary calculations before update if CPU has enough RAM. It is useful if sending the data is time sensitive.
         */
        void cache();

        // Saves millis() to _lastUpdate
        void endUpdate();

    protected:
        bool _isDone{false};
        uint16_t _id;
        uint32_t _lastUpdate{0};
    };

} // namespace ArduinoTasker

#endif