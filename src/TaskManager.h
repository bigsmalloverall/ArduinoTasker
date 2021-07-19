#ifndef ARDUINO_TASKS_MANAGER
#define ARDUINO_TASKS_MANAGER

#include <Arduino.h>
#include <LinkedList.h>
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
         * @param  task: Instance of task
         */
        bool startTaskByPointer(Task *task);

        /**
         * @brief  Adds new instance of all tasks from TasksPool to memory and runs them.
         * @warning Works only when TasksPool is set!
         */
        void startAllTasks();

        /**
         * @brief  Removes task with given id from memory if exists
         * @param  id: id of task
         * @retval True - task stopped, False - task marked as "Do not delete" or does not exist 
         */
        bool stopTask(uint16_t id);

        /**
         * @brief  Removes all task from memory if the are not marked as "Do not delete"
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

        /**
         * @brief  Is given task done
         * @param  id: id of task
         * @retval True - task done, False - task is running or does not exist
         */
        bool isTaskDone(uint16_t id);

        /**
         * @brief  Is given task running
         * @param  id: id of task
         * @retval True - task is running, False - task does not exist or is done
         */
        bool isTaskRunning(uint16_t id);

        /**
         * @brief  Is given task exist in running task buffer
         * @param  id: id of task
         * @retval True - task is exists, False - task does not exist
         */
        bool doesTaskExist(uint16_t id);

        /**
         * @brief  Get running task by id
         * @param  id: id of task
         * @retval Pointer to task or nullptr
         */
        Task *getTask(uint16_t id);


        /**
         * @brief  Removes task (if exist) from list of running tasks
         * @param  id: of task
         */
        void removeTaskFromRunningTasks(uint16_t id);

    protected:
        TasksPool *_tasksPool = nullptr;
        LinkedList<Task *> *_runningTasks;

        /**
         * @retval Delta time from last task setp in us 
         */
        uint32_t getDelta(Task *task);

        /**
         * @brief  Removes task with given id from _runningTasks at position pos
         * @param  id: id of task
         * @param pos: index of task in _runningTasks list
         * @retval True - task stopped, False - task marked as "Do not delete" or does not exist 
         */
        bool stopTask(uint16_t id, uint16_t pos);
    };

} // namespace ArduinoTasker

#endif