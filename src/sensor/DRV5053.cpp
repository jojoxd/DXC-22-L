#include "DRV5053.h"

DRV5053::DRV5053(PinName input)
    : m_sensor(input)
{
}

DRV5053::SensorResponse DRV5053::getData()
{
    float voltage = m_sensor.read() * 3.3f;
    float mT = (voltage - DRV5053_VQ) * DRV5053_SENSITIVITY_mT_per_mV;

    return {
        .pole = mT > 0 ? North : South,
        .mT = fabs(mT),
        .voltage = voltage,
    };
}
