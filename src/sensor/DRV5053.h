#pragma once

#include <mbed.h>

#define DRV5053_VQ 1.02f
#define DRV5053_SENSITIVITY_mT_per_mV -45.0f

/**
 * Our project uses the DRV5053 RA Q LPG (M) Q 1
 */
class DRV5053
{
public:
    DRV5053(PinName input);
    ~DRV5053() = default;

    enum Pole
    {
        North = 0,
        South = 1
    };

    struct SensorResponse
    {
        Pole pole;
        float mT;
        float voltage;
    };

public:
    DRV5053::SensorResponse getData();

protected:
    AnalogIn m_sensor;
};
