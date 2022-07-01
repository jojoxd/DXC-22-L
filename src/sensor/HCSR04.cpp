#include "HCSR04.h"

#include <util.hpp>

HCSR04::HCSR04(PinName echoPin, PinName triggerPin)
    : m_trigger(triggerPin), m_echo(echoPin)
{
    m_distance = -1;
    m_elapsedTime = 0ms;

    m_minDistance = HCSR04_MIN_RANGE;
    m_maxDistance = HCSR04_MAX_RANGE;

    m_newDataReady = false;
    m_timerStarted = false;
}

void HCSR04::startTimer()
{
    if(!m_timerStarted) {
        m_timer.start();
        m_timerStarted = true;

        m_echoTimeout.attach(callback(this, &HCSR04::stopTimer), HCSR04_TIMEOUT);
        m_echo.fall(callback(this, &HCSR04::stopTimer));
        m_echo.rise(nullptr);
    }
}

void HCSR04::stopTimer()
{
    m_timer.stop();

    if(m_timerStarted) {

        m_elapsedTime = m_timer.elapsed_time();

        m_distance = util::math::clamp(
            (m_elapsedTime.count() / 2.0f) * HCSR04_SPEED_OF_SOUND_CM_US,
            m_minDistance, 
            m_maxDistance
        );

        m_newDataReady = true;
    }

    m_timer.reset();
    m_timerStarted = false;
    m_echoTimeout.detach();
    m_echo.fall(nullptr);
}

void HCSR04::turnOffTrigger()
{
    m_trigger = 0;
}

void HCSR04::startMeasurement()
{
    m_trigger = 1;

    m_triggerTimeout.attach(callback(this, &HCSR04::turnOffTrigger), 10ms);
    m_echo.rise(callback(this, &HCSR04::startTimer));

    m_newDataReady = false;
}

float HCSR04::getDistance()
{
    m_newDataReady = false;

    return m_distance;
}

bool HCSR04::isNewDataReady() const
{
    return m_newDataReady;
}

bool HCSR04::isRunning() const
{
    return m_timerStarted;
}

void HCSR04::setRanges(float min, float max)
{
    if(min < max) {
        m_minDistance = util::math::clamp(min, HCSR04_MIN_RANGE, HCSR04_MAX_RANGE);
        m_maxDistance = util::math::clamp(max, HCSR04_MIN_RANGE, HCSR04_MAX_RANGE);
    }
}

std::chrono::microseconds HCSR04::getElapsedTime()
{
    return m_elapsedTime;
}
