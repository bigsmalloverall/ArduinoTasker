#ifndef ARDUINO_TASKS_MANAGER
#define ARDUINO_TASKS_MANAGER

#include <Arduino.h>
#include "LinkedList.h"
#include "Task.h"
#include "TasksPool.h"

namespace ArduinoTasker
{
    class TaskManager
    {
    public:
        TaskManager(TasksPool *tasksPool);
        TaskManager();
        ~TaskManager();

        /**
         * @brief  Fetches task from TasksPool
         * @param  id: id of task
         * @param  wrapId: If id i bigger than tasks number then wrap it to 0 and if it is <0 wrap it to tasks count
         * @retval Pointer to new Task
         */
        Task *fetch(uint16_t id, bool wrapId = false);

        /**
         * @brief  Adds new instance of task with given id from TasksPool to memory and runs it
         * @param  id: id of task
         * @param  wrapId: If id i bigger than tasks number then wrap it to 0 and if it is <0 wrap it to tasks count
         */
        bool startTask(uint16_t id, bool wrapId = false);

        /**
         * @brief  Adds new instance of task with given id from TasksPool to memory and runs it
         * @warning Task bust be instanced by new keyword!
         * @param  task: Instance of task
         */
        bool startTaskByPointer(Task *task);

        /**
         * @brief  Adds new instance of all tass from TasksPool to memory and runs them
         */
        void startAllTasks();

        /**
         * @brief  Removes task with given id from memory if exists
         * @param  id: id of task
         */
        void stopTask(uint16_t id);

        /**
         * @brief  Removes all task from memory
         */
        void stopAllTasks();

        /**
         * @brief  Calls cache then update function in all running tasks.
         */
        void update();

        /**
         * @brief Sets _taskPool
         */
        void setTasksPool(TasksPool *tasksPool);

    protected:
        TasksPool *_tasksPool = nullptr;
        LinkedList<Task *> *_runningTasks;

        /**
         * @retval Delta time from last task setp in us 
         */
        uint32_t getDelta(Task *task);
    };

} // namespace ArduinoTasker

#endif