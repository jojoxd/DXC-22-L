#pragma once

#include <mbed.h>

/**
 * @TODO: Kick-on / Kick-off sequence (Smooth fade-in/out)
 * @TODO: Reversal Sequence (tied in to Kick-on/Kick-off)
 */

class MotorDriver
{
public:
    MotorDriver() = delete;

    MotorDriver(PinName pwmPin, PinName directionPin);

    ~MotorDriver() = default;

    enum Direction
    {
        ClockWise = 0,
        CounterClockWise = 1,
    };

protected:
    PwmOut m_pwm;
    DigitalOut m_direction;

public:
    void setSpeed(float percent);
    float getSpeed();

    void setDirection(Direction direction);
};
