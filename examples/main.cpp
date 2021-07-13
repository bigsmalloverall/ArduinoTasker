#include <Arduino.h>
#include <pins_arduino.h>

#include "TaskManager.h"
#include "TasksPool.h"
#include "Task.h"
#include <Servo.h>

Servo myservo;

namespace ArduinoTasker
{
    class LedBlinkTask : public Task
    {
    private:
        bool _ledState{false};
        uint8_t _ledPin{0};
        uint32_t _frameTime{0};
        uint32_t _sumDeltaT{0};

    public:
        /**
         * @param  id: Task id
         * @param  pin: LED pin
         * @param  delay: Delay in us between state changes
         * @retval 
         */
        LedBlinkTask(uint16_t id, uint8_t pin, uint32_t frameTime = 1000000) : Task(id)
        {
            _ledPin = pin;
            _frameTime = frameTime;
            pinMode(pin, OUTPUT);
        }

        ~LedBlinkTask()
        {
            digitalWrite(_ledPin, LOW);
        }

        void update(uint32_t deltaT)
        {
            if (_sumDeltaT > _frameTime)
            {
                digitalWrite(_ledPin, _ledState);
                _ledState = !_ledState;
                _sumDeltaT = 0;
            }

            _sumDeltaT += deltaT;
        }

        void cache() {}
    };

    class PotLedTask : public Task
    {
    private:
        bool _ledState{false};
        uint8_t _ledPin{0};
        uint8_t _potPin{0};
        uint8_t _dispersion{0};
        uint8_t _totalStateChanges{0};
        uint16_t _analogReadCache{0};
        uint16_t _treshold{0};
        uint16_t _taskToStop{0};
        uint32_t _sumDeltaT{0};
        TaskManager *_managerRef{nullptr};

    public:
        /**
         * @param  id: Task id
         * @param  pin: LED pin
         * @retval 
         */
        PotLedTask(uint16_t id, uint8_t ledPin, uint8_t potPin, uint16_t treshold, uint16_t taskToStop, TaskManager *managerRef, uint8_t dispersion = 100) : Task(id)
        {
            _ledPin = ledPin;
            _potPin = potPin;
            _treshold = treshold;
            _taskToStop = taskToStop;
            _managerRef = managerRef;

            pinMode(ledPin, OUTPUT);
        }

        void update(uint32_t deltaT)
        {
            if ((_analogReadCache >= _treshold - _dispersion || _analogReadCache >= _treshold + _dispersion))
            {
                if (_sumDeltaT >= 250000 && !_ledState) // 0.25s
                {
                    digitalWrite(_ledPin, HIGH);
                    _ledState = true;
                    _totalStateChanges++;

                    if (_totalStateChanges >= 3 && _managerRef != nullptr)
                    {
                        _managerRef->stopTask(_taskToStop);
                    }

                    _sumDeltaT = 0;
                }

                _sumDeltaT += deltaT;
            }
            else
            {
                _sumDeltaT = 0;
                _ledState = false;
                digitalWrite(_ledPin, LOW);
            }
        }

        void cache()
        {
            _analogReadCache = analogRead(_potPin);
        }
    };

    class ServoSweepTask : public Task
    {
    private:
        bool _servoState{false};
        int _servoPosition{0};
        Servo *_servo{nullptr};

        uint32_t _frameTime{0};
        uint32_t _sumDeltaT{0};

    public:
        ServoSweepTask(uint16_t id, Servo *servo) : Task(id)
        {
            _servo = servo;
        }

        ~ServoSweepTask()
        {
            delete _servo;
        }

        void update(uint32_t deltaT)
        {
            if (_sumDeltaT >= 15000)
            {
                if (_servoState)
                {
                    _servoPosition -=10;
                }
                else
                {
                    _servoPosition +=10;
                }

                if (_servoPosition >= 180)
                {
                    _servoState = true;
                    _servoPosition = 180;
                }
                else if (_servoPosition <= 0)
                {
                    _servoPosition = 0;
                    _servoState = false;
                }

                _servo->write(_servoPosition);
                _sumDeltaT = 0;
            }

            _sumDeltaT += deltaT;
        }

        void cache()
        {
        }
    };

    class Tasks : public TasksPool
    {
    public:
        TaskManager *_taskManagerRef{nullptr};

        Tasks(TaskManager *taskManagerRef)
        {
            _taskManagerRef = taskManagerRef;
        }

        Task *tasks(uint16_t id)
        {
            switch (id)
            {
            case 0:
                return new LedBlinkTask(0, 12, 500000);

            case 1:
                return new PotLedTask(1, 11, A0, 512, 0, _taskManagerRef);

            case 2:
                return new ServoSweepTask(2, &myservo);

            default:
                return nullptr;
            }
        }

        uint16_t count()
        {
            return 3;
        }
    };
}

using namespace ArduinoTasker;

TaskManager *manager;

void setup()
{
    // Serial.begin(115200);
    // while (!Serial)
    //     ;
    // Serial.println("init");

    myservo.attach(9);
    manager = new TaskManager();

    TasksPool *pool = new Tasks(manager);

    manager->setTasksPool(pool);
    manager->startAllTasks();
    // manager->startTask(2);
}

void loop()
{
    manager->update();
}