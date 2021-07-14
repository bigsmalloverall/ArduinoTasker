# Arduino Tasker

Arduino Tasker is a simple framework for creating task based code. The goal is to never use delay() so many tasks can run <concurrently" and to be able to neatly segregate your code features. It is designed to run on devices with limited memory like Arduino Uno. It loosely bases operation workflow on RTOS (Real Time Operating System) in that you can time tasks updates in  semi predictable intervals. 

[Consider giving me a buck!](https://www.paypal.com/donate?hosted_button_id=4U6UWETUNPX4C&source=url)

## How to use

Less detailed version in *examples/Blink*.

Below example turns led building of Arduino Uno on and off every second.

### Task definition
Every task needs to be defined by you as **child** class of **Task class** which lives inside **ArduinoTasker** namespace. It **requires update** function to be defined and to **task id** parameter. There is also cache function that is called before update, but it is optional. The purpose of cache will be explained in another examples (look: examples folder) Everything else is up to you. In this example we need led pin and time interval. You can put everything in one file, but for code clarity I’ll split class declaration and definition. 

``` C++
// LedBlinkTask.h

#include <Task.h>

class LedBlinkTask : public ArduinoTasker::Task
{
private:
    // Internal state cholders:
    bool _ledState{false};  // Current state of LED
    uint8_t _ledPin{0};     // Pin of LED
    uint32_t _frameTime{0}; // Delay duration
    uint32_t _sumDeltaT{0}; // Delay interval

public:

    // id: Task id
    // pin: LED pin
    // delay: Delay in us between state changes
    LedBlinkTask(uint16_t id, uint8_t ledPin, uint32_t frameTime = 1000000);
    ~LedBlinkTask();

    // Update is called every loop from main.cpp
    // deltaT is time in us from last time update() was called
    void update(uint32_t deltaT);
};
```

``` C++
// LedBlinkTask.cpp

#include "LedBlinkTask.h"

LedBlinkTask::LedBlinkTask(uint16_t id, uint8_t ledPin, uint32_t frameTime) : Task(id) // Task id passed to Task constructor
{
    _ledPin = ledPin;
    _frameTime = frameTime; // Default time is 1 000 000 us = 1s
    pinMode(ledPin, OUTPUT); // Set ledPin as output;
}

LedBlinkTask::~LedBlinkTask()
{
    // Turn off LED when task is destroyed
    digitalWrite(_ledPin, LOW);
}

void LedBlinkTask::update(uint32_t deltaT)
{   
    // Delay without delay() function
    // If time passed is greater than the delay change LED state
    // It might be helpful to think of this as changing frame in animation
    if (_sumDeltaT > _frameTime)
    {
        digitalWrite(_ledPin, _ledState); // Write LED state
        _ledState = !_ledState; // Change state to opposite
        _sumDeltaT = 0; // Reset time passed
    }

    _sumDeltaT += deltaT; // Accumulate how much time has passed
}
```

The task definition looks very similar to main Arduino loop. Constructor is like ```void setup()``` and  ```void update(...)``` is like ``` void loop()```. The code for such a simple task is quite substantial, but this is just an example. You can use this to make as complicated stuff as you want!

### TaskManager
This library allows you to create many tasks templates that are loaded in to memory only when they are running. It achieves that with TaskManager, which is imitates **simple** operating system. Manager fetches Tasks from user defined TasksPool, which is collection defined by You of templates for Tasks.

``` C++
// Arbitrary example

#include <TasksManager.h>
#include <YourTasksPool.h>

ArduinoTasker::TaskManager *manager;

void setup()
{
    manager = new ArduinoTasker::TaskManager(new TasksPoolChildClass());
    manager->startTask(0); // Loads task with id 0 to memory and runs it
}

void loop() 
{
    manager->update(); // Updates states of running tasks
}
```

Tasks can also be added manually. But you need to make that it is created with **new** keyword as when the task is finished it will be automatically deleted from memory. Make sure to free all allocated memory in you task in destructor to avoid leaks! 

``` C++
// Arbitrary example

#include <TasksManager.h>
#include "TestTask.h"

ArduinoTasker::TaskManager manager;

void setup()
{
    manager.startTaskByPointer(new TestTask());
}
```

### TasksPool
As mentioned before. TasksPool is collection of class templates. It’s main function is to easily iterate through your task and load them to memory only when they are needed. That moment is also defined by you. In practice tasks pool is just child class of TasksPool class with two mandatory functions: tasks and count.This time it’s the code is small enough to just cram everything into one header file. But in larger project it would be advised to split.

``` C++
//  CustomTaskPool.h

#include <TasksPool.h>

class CustomTaskPool : public ArduinoTasker::TasksPool
{
public:
    Task *tasks(uint16_t id)
    {
        switch (id)
        {
            // Case index should be equal to task id
        case 0:
            // Task id as first parameter
            // LED_PIN is constant from global scope, can be any uint
            return new LedBlinkTask(0, LED_PIN);

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
```

## Final code
Now that everything is defined we can put it together

``` C++
// LedBlinkTask.h

#include <Task.h>

class LedBlinkTask : public ArduinoTasker::Task
{
private:
    bool _ledState{false};  
    uint8_t _ledPin{0};     
    uint32_t _frameTime{0}; 
    uint32_t _sumDeltaT{0}; 

public:
    LedBlinkTask(uint16_t id, uint8_t ledPin, uint32_t frameTime = 1000000);
    ~LedBlinkTask();
    void update(uint32_t deltaT);
};
```

``` C++
// LedBlinkTask.cpp

#include "LedBlinkTask.h"

LedBlinkTask::LedBlinkTask(uint16_t id, uint8_t ledPin, uint32_t frameTime) : Task(id) 
{
    _ledPin = ledPin;
    _frameTime = frameTime;
    pinMode(ledPin, OUTPUT);
}

LedBlinkTask::~LedBlinkTask()
{
    digitalWrite(_ledPin, LOW);
}

void LedBlinkTask::update(uint32_t deltaT)
{   
    if (_sumDeltaT > _frameTime)
    {
        digitalWrite(_ledPin, _ledState); 
        _ledState = !_ledState; 
        _sumDeltaT = 0; 
    }

    _sumDeltaT += deltaT; 
}
```

``` C++
// CustomTaskPool.h

#include <TasksPool.h>

class CustomTaskPool : public ArduinoTasker::TasksPool
{
public:
    Task *tasks(uint16_t id)
    {
        switch (id)
        {
        case 0:
            return new LedBlinkTask(0, LED_PIN);

        default:
            return nullptr;
        }
    }

    uint16_t count()
    {
        return 1; 
    }
};
```

``` C++
// main.cpp
#include <TaskManager.h>
#include "CustomTaskPool.h"
#include "LedBlinkTask.h"

#define LED_PIN 13

using namespace ArduinoTasker;

TaskManager *manager;

void setup()
{
    manager = new TaskManager(new CustomTaskPool());
    manager->startTask(0);
}

void loop()
{
    manager->update();
}
```

# Other functions
## Tasks
## TaskManager


[Consider giving me a buck!](https://www.paypal.com/donate?hosted_button_id=4U6UWETUNPX4C&source=url)