#pragma once

#include <mbed.h>

#ifndef CNY70_CUTOFF
    #define CNY70_CUTOFF 0.5f
#endif

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
