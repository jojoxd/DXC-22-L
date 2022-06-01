#pragma once

#include <mbed.h>

#include "config.h"
#include "sensor/CNY70Array.h"
#include "driver/MotorFunction.h"

#ifndef DRCTL_TICKER_INTERVAL
    #define DRCTL_TICKER_INTERVAL 1'000us
#endif

#define SPEED_FAST 1.0f
#define SPEED_SLOW 0.8f

class DrivingController
{
public:
    DrivingController(MotorDriver* leftDriver, MotorDriver* rightDriver)
        : m_leftDriver(leftDriver), m_rightDriver(rightDriver),
          m_ticker(), m_ticks(0), m_interval(DRCTL_TICKER_INTERVAL)
    {
    }

    ~DrivingController()
    {
        m_ticker.detach();
    }

protected:
    MotorDriver* m_leftDriver;
    MotorDriver* m_rightDriver;

    Ticker m_ticker;
    int m_ticks;

    std::chrono::microseconds m_interval;

    bool m_isRunning = false;

    CNY70Array::Bias m_bias = CNY70Array::Bias::Center;
    float m_speedLeft = 1.0f;
    float m_speedRight = 1.0f;
public:
    void start()
    {
        m_ticker.attach(callback(this, &DrivingController::handleDriving), m_interval);
        m_isRunning = true;
    }

    void stop()
    {
        m_ticker.detach();
        m_isRunning = false;
    }

    bool isRunning() const
    {
        return m_isRunning;
    }

    void setBias(CNY70Array::Bias bias)
    {
        m_bias = bias;
    }

protected:
    /**
     * Handle Sensor Readout => MotorDriver conversion
     *
     * @NOTE: This function is in ISR context.
     */
    void handleDriving()
    {
        m_ticks++;

        if(m_bias == CNY70Array::Bias::Center) {
            m_speedLeft = SPEED_FAST;
            m_speedRight = SPEED_FAST;
        }

        if(m_bias == CNY70Array::Bias::Left) {
            m_speedLeft = SPEED_SLOW;
            m_speedRight = SPEED_FAST;
        }

        if(m_bias == CNY70Array::Bias::Right) {
            m_speedLeft = SPEED_FAST;
            m_speedRight = SPEED_SLOW;
        }

        m_leftDriver->setSpeed(m_speedLeft);
        m_rightDriver->setSpeed(m_speedRight);
    }
};
