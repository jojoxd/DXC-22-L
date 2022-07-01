#include "CNY70.h"

CNY70::CNY70(PinName pin)
    : m_sensor(pin)
{
}

float CNY70::getVoltage()
{
    return m_sensor.read() * 3.3f;
}

CNY70::Surface CNY70::getSurface()
{
    return m_sensor.read() > CNY70_CUTOFF ? Dark : Light;
}

CNY70::operator float()
{
    return getVoltage();
}
