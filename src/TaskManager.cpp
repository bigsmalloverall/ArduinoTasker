#include "TaskManager.h"

namespace ArduinoTasker
{

    TaskManager::TaskManager(TasksPool *tasksPool)
    {
        _tasksPool = tasksPool;
        TaskManager();
    }

    TaskManager::TaskManager()
    {
        _runningTasks = new LinkedList<Task *>();
    }

    TaskManager::~TaskManager()
    {
        delete _runningTasks;
    }

    Task *TaskManager::fetch(uint16_t id, bool wrapId)
    {
        if (wrapId)
        {
            if (id > _tasksPool->count())
            {
                id = 0;
            }
            else if (id < 0)
            {
                id = _tasksPool->count() - 1;
            }
        }

        return _tasksPool->tasks(id);
    }

    bool TaskManager::startTask(uint16_t id, bool wrapId)
    {
        Task *task = this->fetch(id, wrapId);
        return this->startTaskByPointer(task);
    }

    bool TaskManager::startTaskByPointer(Task *task)
    {
        if (task != nullptr)
        {
            _runningTasks->add(task);
            return true;
        }

        return false;
    }

    void TaskManager::startAllTasks()
    {
        for (uint16_t i = 0; i < _tasksPool->count(); i++)
        {
            this->startTaskByPointer(this->fetch(i, false));
        }
    }

    void TaskManager::stopTask(uint16_t id)
    {
        Task *task = nullptr;

        for (uint16_t i = 0; i < (uint16_t)_runningTasks->size(); i++)
        {
            task = _runningTasks->get(i);

            if (task->getId() == id)
            {
                _runningTasks->remove(i);
            }
        }
    }

    void TaskManager::stopAllTasks()
    {
        _runningTasks->clear();
    }

    uint32_t TaskManager::getDelta(Task *task)
    {
        return (uint32_t)micros() - task->getLastUpdateTime();
    }

    void TaskManager::update()
    {
        Task *task = nullptr;

        for (uint16_t i = 0; i < (uint16_t)_runningTasks->size(); i++)
        {
            task = _runningTasks->get(i);

            if (task != nullptr)
            {
                if (task->isDone())
                {
                    stopTask(task->getId());
                }
                else
                {
                    task->cache();
                    task->update(this->getDelta(task));
                    task->endUpdate();
                }
            }
        }
    }

    void TaskManager::setTasksPool(TasksPool *tasksPool)
    {
        _tasksPool = tasksPool;
    }

} // namespace ArduinoTasker
