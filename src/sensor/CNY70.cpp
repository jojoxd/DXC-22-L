#include "CNY70.h"
#include "console.hpp"

int ticks = 0;

CNY70::CNY70(PinName pin, int id)
    : m_sensor(pin), m_id(id)
{
}

double CNY70::getVoltage()
{
    return (double) m_sensor.read() * 3.3;
}

CNY70::Surface CNY70::getSurface()
{
    if(ticks++ % 8 == 0) {
        Console::getInstance().ISR_writelnf("CNY70", "SenseV:0x%d=%dmV", m_id, (int) (m_sensor.read() * 1000.0f));
    }

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
