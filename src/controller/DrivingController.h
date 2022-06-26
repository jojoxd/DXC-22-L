#pragma once

#include <mbed.h>

#include "helper/config.h"
#include "sensor/CNY70Array.h"
#include "console/ConsoleInput.h"
#include "driver/MotorDriver.h"

#ifndef DRCTL_TICKER_INTERVAL
    #define DRCTL_TICKER_INTERVAL 1'000us
#endif

#ifndef DRCTL_SPEED_SLOW
    #define DRCTL_SPEED_SLOW 0.0f
#endif

#ifndef DRCTL_SPEED_FAST
    #define DRCTL_SPEED_FAST 1.0f
#endif

/**
 * DrivingController controls the way we drive
 *
 * It converts sensor data (CNY70Array::Bias) into actual movement
 *
 * Macros:
 * - DRCTL_TICKER_INTERVAL (default: 1000us):
 *     Interval at which to update the motor speeds
 *
 * - DRCTL_SPEED_SLOW (default: 0.0f):
 *     "slow" motor speed when it should move in a certain direction
 *
 * - DRCTL_SPEED_FAST (default: 1.0f):
 *     "fast" motor speed when it should move in a certain direction, or forward
 */
class DrivingController
{
public:
    DrivingController(MotorDriver* leftDriver, MotorDriver* rightDriver, ConsoleInput* input);

    ~DrivingController();

public:
    void start();

    void stop();

    bool isRunning() const;

    void setBias(CNY70Array::Bias bias);

protected:
    MotorDriver* m_leftDriver;
    MotorDriver* m_rightDriver;

    Ticker m_ticker;
    int m_ticks = 0;

    std::chrono::microseconds m_interval = { DRCTL_TICKER_INTERVAL };

    bool m_isRunning = false;

    CNY70Array::Bias m_bias = CNY70Array::Bias::Center;
    float m_speedLeft = 1.0f;
    float m_speedRight = 1.0f;

protected:
    /**
     * Handle Sensor Readout => MotorDriver conversion
     *
     * @NOTE: This function is in ISR context.
     */
    void handleDriving();

    void onPause();

    void onResume();

    friend class PaperThrower;
};
