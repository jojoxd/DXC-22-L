#pragma once

#include <mbed.h>
#include "MotorDriver.h"

class MotorFunction
{
public:
    /**
     * Creates a MotorFunction
     *
     * @NOTE: the callback will be executed in an ISR Context (From Ticker)
     */
    explicit MotorFunction(MotorDriver* driver, std::chrono::microseconds duration, int reps, Callback<void(MotorDriver*, int)> cb)
        : m_driver(driver), m_callback(cb), m_interval(duration / reps), m_ticker(), m_reps(reps)
    {
    }

protected:
    MotorDriver* m_driver;

    Callback<void(MotorDriver*, int)> m_callback;

    std::chrono::microseconds m_interval;

    Ticker m_ticker;

    int m_reps;

    int m_ticks = 0;

    bool m_isRunning = false;

protected:
    void onTick()
    {
        m_ticks += 1;

        if(m_ticks > m_reps) {
            stop();
            return;
        }

        m_callback.call(m_driver, m_ticks);
    }

public:
    /**
     * Start this MotorFunction
     */
    void start()
    {
        m_ticker.attach(callback(this, &MotorFunction::onTick), m_interval);

        m_isRunning = true;
    }

    /**
     * Stop/cancel this MotorFunction
     */
    void stop()
    {
        m_ticker.detach();
        m_ticks = 0;

        m_isRunning = false;
    }

    /**
     * Check if this MotorFunction is Running
     */
    bool isRunning() const
    {
        return m_isRunning;
    }
};
