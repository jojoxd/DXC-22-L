#include "MotorDriver.h"

MotorDriver::MotorDriver(PinName pwmPin, PinName directionPin, float speedMultiplier = 1.0f)
    : m_pwmSignal(pwmPin), m_direction(directionPin), m_speedMultiplier(speedMultiplier)
{
    m_pwmSignal.period_us(10);
}

MotorDriver::MotorDriver(PinName pwmPin, PinName directionPin)
    : MotorDriver(pwmPin, directionPin, 1.0f)
{
    m_pwmSignal.period_us(10);
}

void MotorDriver::setSpeed(float speed)
{
    if(speed < 0.0f) {
        m_direction = 0;
    } else {
        m_direction = 1;
    }

     m_pwmSignal = fabs(speed) * m_speedMultiplier;
}

float MotorDriver::getSpeed()
{
    if(m_direction.read() == 0)
        return 0.0f - (m_pwmSignal.read() / m_speedMultiplier);

    return (m_pwmSignal.read() / m_speedMultiplier);
}
