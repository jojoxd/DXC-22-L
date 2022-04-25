#include "MotorDriver.h"

MotorDriver::MotorDriver(PinName pwmPin, PinName directionPin)
    : m_pwm(pwmPin), m_direction(directionPin)
{
    m_pwm.period_us(500);
}

float bezier(float x, float u0, float u1, float u2, float u3)
{
    return (u0 * powf(1-x, 3)) + (3 * u1 * powf(1 - x, 2)) + (2 * u2 * (1 - x) * powf(x, 2)) + (u3 * powf(x, 3));
}

void MotorDriver::setSpeed(float percent)
{
//    auto between = 25.0f + (bezier(percent / 100.0f, 0.0f, 0.0f, 1.0f, 1.0f) * 75.0f);
//
//    m_pwm = between / 100.0f;

     m_pwm = percent / 100.0f;
}

float MotorDriver::getSpeed()
{
    return m_pwm;
}

void MotorDriver::setDirection(MotorDriver::Direction direction)
{
    m_direction = direction;
}
