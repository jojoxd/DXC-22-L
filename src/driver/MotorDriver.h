#pragma once

#include <mbed.h>

#include "util.hpp"

/**
 * @TODO: Kick-on / Kick-off sequence (Smooth fade-in/out)
 * @TODO: Reversal Sequence (tied in to Kick-on/Kick-off)
 */

class MotorDriver
{
public:
    MotorDriver() = delete;

    MotorDriver(PinName pwmPin, PinName directionPin);
    MotorDriver(PinName pwmPin, PinName directionPin, float speedMultiplier);

    ~MotorDriver() = default;

protected:
    PwmOut m_pwmSignal;

    DigitalOut m_direction;

    float m_speedMultiplier;

public:
    /**
     * Sets the speed of this motor
     *
     * Domain is [-1.0f .. 1.0f]
     */
    void setSpeed(float speed);
    float getSpeed(bool corrected = false);
};
