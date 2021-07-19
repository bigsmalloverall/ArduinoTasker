# Arduino Tasker

Arduino Tasker is a simple framework for creating task based code. The goal is to never use delay() so many tasks can run "concurrently" and to be able to neatly segregate your code features. It is designed to run on devices with limited memory like Arduino Uno. It loosely bases operation workflow on RTOS (Real Time Operating System) in that you can time tasks in semi predictable intervals. 

[Consider giving me a buck!](https://www.paypal.com/donate?hosted_button_id=4U6UWETUNPX4C&source=url)

- [Arduino Tasker](#arduino-tasker)
- [How to use](#how-to-use)
  - [Task definition](#task-definition)
  - [TaskManager](#taskmanager)
  - [TasksPool](#taskspool)
    - [TasksPool alternate binding](#taskspool-alternate-binding)
  - [Manually adding tasks](#manually-adding-tasks)
  - [Stopping tasks](#stopping-tasks)
  - [Stopping newer ending tasks](#stopping-newer-ending-tasks)
  - [Preventing finished task from deletion](#preventing-finished-task-from-deletion)

# How to use

See *examples/* for in depth explanations

## Task definition
Every task needs to be defined by you as **child** class of **Task class** which lives inside **ArduinoTasker** namespace. It **requires update** function and to **task id** parameter. There is also cache function that is called before update, but it is optional (*examples/TaskCache*). Everything else is up to you.

**Make sure every instance of your tasks have unique ids!**

``` C++
// Pseudo code
// Task header

#ifndef SOME_TASK
#define SOME_TASK

#include <Arduino.h>
#include <Task.h>

class SomeTask : public ArduinoTasker::Task
{
private:
    bool _variable{false};

public:
    SomeTask(uint16_t id, bool variable);
    void update(uint32_t deltaT);
};

#endif
```

``` C++
// Pseudo code
// Task body

#include <Arduino.h>
#include "SomeTask.h"

// Task id passed to Task constructor
SomeTask::SomeTask(uint16_t id, uint8_t variable) : Task(id)
{
    _variable = variable;
}

void SomeTask::update(uint32_t deltaT)
{   
    _variable = !_variable;
}
```

The task definition looks very similar to main Arduino loop. Constructor is like ```void setup()``` and  ```void update(...)``` is like ``` void loop()```.

## TaskManager
This library allows you to create many tasks templates that are loaded in to memory only when they are running (or needed). It achieves that with TaskManager, which is imitates **simple** operating system. Manager fetches Tasks from user defined TasksPool, which is collection of templates for Tasks or accepts pointers to tasks. **Be careful wit that! See *examples/TaskEnding*)**.

``` C++
// Pseudo code
// Arduino main

#include <TasksManager.h>
#include "YourTasksPool.h"

ArduinoTasker::TaskManager *manager;

void setup()
{
    manager = new ArduinoTasker::TaskManager(new YourTasksPool());
    manager->startTask(0); // Loads task with id 0 to memory and runs it
    manager->startAllTasks(); // Loads all tasks from TasksPool to memory and runs them 
}

void loop() 
{
    manager->update(); // Updates states of running tasks
}
```

## TasksPool
As mentioned before. TasksPool is collection of class templates. It’s main purpose is to easily iterate through your task and load them to memory only when they are needed. In practice tasks pool is just child class of TasksPool class with two mandatory functions: tasks and count.

``` C++
// Pseudo code
// YourTasksPool.h

#ifndef YOUR_TASKS_POOL
#define YOUR_TASKS_POOL

#include <Arduino.h>
#include <TasksPool.h>
#include <Task.h>
#include "SomeTask.h"

class YourTasksPool : public ArduinoTasker::TasksPool
{
public:
    ArduinoTasker::Task *tasks(uint16_t id)
    {
        switch (id)
        {
            // Case index should be equal to task id
            case 0:
                // Task id as first parameter
                return new SomeTask(0, your params ...);

            default:
                // If id is invalid return nullptr
                // TaskManager function startTask() will return false
                // meaning the task failed to start.
                // It can also be a default task.
                return nullptr;
        }
    }

    uint16_t count()
    {
        // This value needs to be incremented manually and 
        // should be equal to the number of cases in switch
        return 1;
    }
};
#endif
```

### TasksPool alternate binding
Task pool can also be added after TaskManager instantiation, at any point during runtime. Running tasks will not be affected. TaskManager frees taskPool pointer when it's destructed. **Changing TasksPools multiple times during runtime is not advised. This feature is under development. There should bo not TasksPool or only one.**

``` C++
// Pseudo code
// Arduino main

#include <TasksManager.h>
#include "YourTasksPool.h"

ArduinoTasker::TaskManager manager;

void setup()
{
    manager.setTasksPool(new YourTasksPool());

    // (...)
}

void loop() 
{
    manager.update(); // Updates states of running tasks
}
```

## Manually adding tasks
Tasks can also be added manually. Make sure there are no external pointers to that task.

``` C++
// Pseudo code
// Arduino main

#include <TasksManager.h>
#include "SomeTask.h"

ArduinoTasker::TaskManager manager;

void setup()
{
    manager.startTaskByPointer(new SomeTask(0));

    // You can add many tasks of the same type, but with different id
    manager.startTaskByPointer(new SomeTask(1));
    manager.startTaskByPointer(new SomeTask(2));
    manager.startTaskByPointer(new SomeTask(3));
}

// (...)
```

## Stopping tasks
Tasks are automatically stopped by TaskManager in next update after isDone flag is set by ```finish()``` function.

``` C++
// Pseudo code
// Task body

#include <Arduino.h>
#include "SomeTask.h"

// Task id passed to Task constructor
SomeTask::SomeTask(uint16_t id) : Task(id)
{

}

void SomeTask::update(uint32_t deltaT)
{   
    // Some condition ...

    // Sets isDone flag to true
    // TaskManager will no longer cache or update this task
    // This task will be deleted on next global update
    this->finish();
}
```
## Stopping newer ending tasks
Some tasks run indefinitely and it is needed to stop them by some external trigger. It can be done with ```stopTask()``` function.

``` C++
// Pseudo code
// Arduino main

#include <TasksManager.h>
#include "SomeInfiniteTask.h"

ArduinoTasker::TaskManager manager;

void setup()
{
    manager.startTaskByPointer(new SomeInfiniteTask(0));
}

void loop() 
{
    manager.update(); // Updates states of running tasks

    if (// Some condition)
    {
        // Deletes task with ID 0 from memory
        // You can not do this if you have external pointer to this task, see example below!
        manager.stopTask(0);
    }
}
```

## Preventing finished task from deletion
Sometimes it is needed to operate on results from finished task. I can be done by setting flag ```doNotDelete``` to ```true```. It is safe now to use external pointer to the task, just make sure to do cleanup.See *examples/TaskEnding* for more details.

``` C++
// Pseudo code
// Task body

#include <Arduino.h>
#include "SomeTaskWithData.h"

// Task id passed to Task constructor
SomeTaskWithData::SomeTaskWithData(uint16_t id) : Task(id)
{
    // This marks task as "Do not delete"
    // TaskManager will not delete this task from memory
    this->doNotDelete();
}

void SomeTaskWithData::update(uint32_t deltaT)
{   
    // Some end condition ...

    // Sets isDone flag to true
    // TaskManager will no longer cache or update this task
    this->finish();
}

// Manually added function to retrieve data
uint32 SomeTaskWithData::getData()
{
    return some value ...;
}
```

``` C++
// Pseudo code
// Arduino main

#include <TasksManager.h>
#include "SomeTaskWithData.h"

ArduinoTasker::TaskManager manager;

SomeTaskWithData * pTaskWithData = nullptr;

void setup()
{
    pTaskWithData = new SomeTaskWithData(0);
    manager.startTaskByPointer(pTaskWithData);
}

void loop() 
{
    manager->update(); // Updates states of running tasks

    // SomeTaskWithData is done and has some data
    if (pTaskWithData != nullptr && pTaskWithData->isDone())
    {
        uint32_t data = pTaskWithData->getData();

        // Cleanup
        // This is important!
        manager.removeTaskFromRunningTasks(pTaskWithData->getId());
        delete pTaskWithData;
        pTaskWithData = nullptr;

        // Do something with data ...
    }
}
```


[Consider giving me a buck!](https://www.paypal.com/donate?hosted_button_id=4U6UWETUNPX4C&source=url)
