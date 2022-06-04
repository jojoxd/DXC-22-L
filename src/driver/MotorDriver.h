#pragma once

#include <mbed.h>

#include "helper/config.h"
#include "util.hpp"

/**
 * A Motor Driver implementation
 * Controls the speed and direction of a motor using an L293D/L293N H-bridge
 *
 * Supports 2 modes:
 * - DRIVER_METHOD = 0: Instant Mode:
 *     Pushes the asked speed instantly to the motor
 *     This may cause a sudden spike in current
 *
 * - DRIVER_METHOD = 1: Average Mode:
 *     Uses a moving average to ramp up/down the motor
 *     When setting the speed to 0.0f, it will immediately set that speed.
 *
 * The mode can be set in helper/config.h
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

    float m_speed = 0.0f;
    float m_speedMultiplier;

    util::MovingAverage<float, 10, float> m_movingAverageSpeed;
    Ticker m_ticker;

public:
    /**
     * Sets the speed of this motor
     *
     * Domain is [-1.0f .. 1.0f]
     */
    void setSpeed(float speed);
    float getSpeed(bool corrected = false);

protected:
    void tick();
};
