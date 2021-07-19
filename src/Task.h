#ifndef ARDUINO_TASKS_TASK
#define ARDUINO_TASKS_TASK

#include <Arduino.h>
#include <Status.h>

namespace ArduinoTasker
{
    class Task
    {
    public:
        /**
         * @brief  Task constructor
         * @param  id: id of task
         */
        Task(uint16_t id, bool deleteWhenDone = true);

        /**
         * @brief  Destructor
         */
        virtual ~Task();

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
         * @retval If this task should be deleted from memory
         */
        bool canBeDeleted();

        /**
         * @brief Marks taks as don not delete. So it is not deleted when it's finished
         */
        void doNotDelete();

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
        Status _status; // Bit field
        uint16_t _id;
        uint32_t _lastUpdate{0};
    };

} // namespace ArduinoTasker

#endif