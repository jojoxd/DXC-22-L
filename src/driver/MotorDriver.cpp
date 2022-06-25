#include "MotorDriver.h"

MotorDriver::MotorDriver(PinName pwmPin, PinName directionPin, float speedMultiplier = 1.0f)
    : m_pwmSignal(pwmPin), m_direction(directionPin, PinMode::PullDown),
    m_speedMultiplier(speedMultiplier), m_movingAverageSpeed(), m_ticker()
{
    m_pwmSignal.period_us(10);

    m_ticker.attach(callback(this, &MotorDriver::tick), 10ms);
}

MotorDriver::MotorDriver(PinName pwmPin, PinName directionPin)
    : MotorDriver(pwmPin, directionPin, 1.0f)
{
    m_pwmSignal.period_us(40);
}

void MotorDriver::setSpeed(float speed)
{
    speed = speed * m_speedMultiplier;

    if(speed < 0.0f) {
        m_direction = 0;
    } else {
        m_direction = 1;
    }

    m_speed = speed;
}

float MotorDriver::getSpeed(bool corrected)
{
    float speedMultiplier = corrected ? m_speedMultiplier : 1.0f;

    if(m_direction.read() == 0)
        return 0.0f - (m_pwmSignal.read() / speedMultiplier);

    return (m_pwmSignal.read() / speedMultiplier);
}

void MotorDriver::tick()
{
    #if defined(DRIVER_METHOD_INSTANT)
        float speed = m_speed;
    #elif defined(DRIVER_METHOD_AVERAGE)
        float speed = m_movingAverageSpeed.next(m_speed);

        // Quick off, but keep moving average moving
        if(m_speed == 0.0f) {
            speed = 0.0f;
        }
    #endif

    m_pwmSignal = fabs(speed);
}
