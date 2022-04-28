#pragma once

#include <mbed.h>
#include <driver/MotorFunction.h>

#include "config.h"
#include "sensor/CNY70Array.h"

#ifndef DRCTL_TICKER_INTERVAL
    #define DRCTL_TICKER_INTERVAL 1'000us
#endif

class DrivingController
{
public:
    explicit DrivingController(MotorDriver* leftDriver, MotorDriver* rightDriver)
        : m_sensorArray(CNY70_LEFT, CNY70_CENTER, CNY70_RIGHT),
          m_leftDriver(leftDriver), m_rightDriver(rightDriver),
          m_ticker(), m_interval(DRCTL_TICKER_INTERVAL)
    {
    }

protected:
    CNY70Array m_sensorArray;

    MotorDriver* m_leftDriver;
    MotorDriver* m_rightDriver;

    Ticker m_ticker;

    std::chrono::microseconds m_interval;

public:
    void start()
    {
        m_ticker.attach(callback(this, &DrivingController::handleDriving), m_interval);
    }

    void stop()
    {
        m_ticker.detach();
    }

protected:
    /**
     * Handle Sensor Readout => MotorDriver conversion
     *
     * @NOTE: This function is in ISR context.
     */
    void handleDriving()
    {
        // @TODO: Readout of sensor array, execute speed changes on MotorDriver leftDriver & rightDriver.

        if(!m_sensorArray.isOnLine()) {
            float bias = m_sensorArray.getBias();

            // Ensure we are going towards the line
        }
    }
};
