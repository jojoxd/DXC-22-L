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

    struct SurfaceData
    {
        Surface surface;
        double voltage;
    };

public:
    explicit CNY70(PinName pin);
    CNY70(CNY70& copy) = delete;
    ~CNY70() = default;

    double getVoltage();
    CNY70::Surface getSurface();
    CNY70::SurfaceData getSurfaceData();

    explicit operator double();

protected:
    AnalogIn m_sensor;
};
