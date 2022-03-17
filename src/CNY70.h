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
        Light,
        Dark,
    };

public:
    explicit CNY70(PinName pin);
    CNY70(CNY70& copy) = delete;
    ~CNY70() = default;

    double getVoltage();

    CNY70::Surface getSurface();

    explicit operator double();

protected:
    AnalogIn m_sensor;
};
