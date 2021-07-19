#include "TaskManager.h"

namespace ArduinoTasker
{
    TaskManager::TaskManager(TasksPool *tasksPool)
    {
        _tasksPool = tasksPool;
        _runningTasks = new LinkedList<Task *>();
    }

    TaskManager::TaskManager()
    {
        _runningTasks = new LinkedList<Task *>();
    }

    TaskManager::~TaskManager()
    {
        if (_runningTasks != nullptr)
        {
            delete _runningTasks;
        }
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
        if (_tasksPool != nullptr)
        {
            for (uint16_t i = 0; i < _tasksPool->count(); i++)
            {
                this->startTaskByPointer(this->fetch(i, false));
            }
        }
    }

    bool TaskManager::stopTask(uint16_t id)
    {
        Task *task = nullptr;

        for (uint16_t i = 0; i < (uint16_t)_runningTasks->size(); i++)
        {
            task = _runningTasks->get(i);

            if (task->canBeDeleted())
            {
                if (task->getId() == id)
                {
                    _runningTasks->remove(i);
                    delete task;
                    return true;
                }
            }
            else
            {
                return false;
            }
        }

        return false;
    }

    void TaskManager::stopAllTasks()
    {
        Task *task = nullptr;

        for (uint16_t i = 0; i < (uint16_t)_runningTasks->size(); i++)
        {
            task = _runningTasks->get(i);

            if (task->canBeDeleted())
            {
                _runningTasks->remove(i);
            }
        }
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
                    Serial.print("Task ");
                    Serial.print(task->getId());
                    Serial.println(" about to be deleted!");
                    this->stopTask(task->getId(), i);
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

    bool TaskManager::isTaskDone(uint16_t id)
    {
        Task *task = this->getTask(id);
        return (task == nullptr ? true : task->isDone());
    }

    bool TaskManager::isTaskRunning(uint16_t id)
    {
        Task *task = this->getTask(id);
        return (task == nullptr ? false : !task->isDone());
    }

    bool TaskManager::doesTaskExist(uint16_t id)
    {
        Task *task = this->getTask(id);
        return task != nullptr;
    }

    Task *TaskManager::getTask(uint16_t id)
    {
        Task *task = nullptr;

        for (uint16_t i = 0; i < (uint16_t)_runningTasks->size(); i++)
        {
            task = _runningTasks->get(i);

            if (task->getId() == id)
            {
                return task;
            }
        }

        return nullptr;
    }

    void TaskManager::removeTaskFromRunningTasks(uint16_t id)
    {
        Task *task = nullptr;

        for (uint16_t i = 0; i < (uint16_t)_runningTasks->size(); i++)
        {
            task = _runningTasks->get(i);

            if (task->getId() == id)
            {
                _runningTasks->remove(i);
                return;
            }
        }
    }

    bool TaskManager::stopTask(uint16_t id, uint16_t pos)
    {
        if (pos >= _runningTasks->size())
        {
            return false;
        }

        Task *task = _runningTasks->get(pos);

        if (task->getId() == id)
        {
            _runningTasks->remove(pos);
            delete task;
        }
    }

} // namespace ArduinoTasker
