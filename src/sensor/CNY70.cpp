#include "CNY70.h"

CNY70::CNY70(PinName pin)
    : m_sensor(pin)
{
}

double CNY70::getVoltage()
{
    return (double) m_sensor.read() * 3.3;
}

CNY70::Surface CNY70::getSurface()
{
    return m_sensor.read() > 0.5f ? Dark : Light;
}

CNY70::operator double()
{
    return getVoltage();
}

CNY70::SurfaceData CNY70::getSurfaceData()
{
    return {
        .surface = getSurface(),
        .voltage = getVoltage(),
    };
}
