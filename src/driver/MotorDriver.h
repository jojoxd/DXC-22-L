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

protected:
    PwmOut m_pwmSignal;
    DigitalOut m_direction;

public:
    /**
     * Sets the speed of this motor
     *
     * Domain is [-1.0f .. 1.0f]
     */
    void setSpeed(float speed);
    float getSpeed();
};
