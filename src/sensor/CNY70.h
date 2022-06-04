#pragma once

#include <mbed.h>

/**
 * Vishay CNY70 Optical Reflective Sensor
 */
class CNY70
{
public:
    enum Surface
    {
        Light = 0,
        Dark  = 1,
    };

public:
    explicit CNY70(PinName pin);

    ~CNY70() = default;

protected:
    AnalogIn m_sensor;

public:
    float getVoltage();
    CNY70::Surface getSurface();

    explicit operator float();
};
