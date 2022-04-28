#include "MotorDriver.h"

MotorDriver::MotorDriver(PinName pwmPin, PinName directionPin)
    : m_pwmSignal(pwmPin), m_direction(directionPin)
{
    m_pwmSignal.period_us(500);
}

void MotorDriver::setSpeed(float speed)
{
    if(speed < 0.0f) {
        m_direction = 0;
    } else {
        m_direction = 1;
    }

     m_pwmSignal = fabs(speed);
}

float MotorDriver::getSpeed()
{
    if(m_direction.read() == 0)
        return 0.0f - m_pwmSignal.read();

    return m_pwmSignal.read();
}
