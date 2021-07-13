#ifndef ARDUINO_TASKS_POOL
#define ARDUINO_TASKS_POOL

#include <Arduino.h>
#include "ArduinoTasker/Task.h"

namespace ArduinoTasker
{
    class TasksPool {
        public:
        /**
         * @brief  Pool of all tasks
         * @note   Each task should be instanced only when it is demmanded, the goal is to use as little memory as possible.
         * @param  id: Task to be initiated
         * @retval Pointer to new Task
         */
        virtual Task* tasks(uint16_t id) = 0;

        /**
         * @retval Amount of tasks in the pool
         */
        virtual uint16_t count() = 0;

    };
    
} // namespace ArduinoTasker

#endif