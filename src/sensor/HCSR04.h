#pragma once

#include <mbed.h>

#define HCSR04_MIN_RANGE 2.0f
#define HCSR04_MAX_RANGE 400.0f

#ifndef HCSR04_TIMEOUT
    #define HCSR04_TIMEOUT 25ms
#endif

/**
 * HC-SR04 Distance Sensor
 *
 * Adapted to work with our mbed-os version,
 * from https://os.mbed.com/teams/TVZ-Mechatronics-Team/code/HCSR04/
 *
 * @NOTE: If the measured object is more then 15 degrees rotated,
 *        the sensor will NOT give an accurate reading.
 *
 * @TODO: Cleanup variables / etc.
 */
class HCSR04
{
public:
    HCSR04(PinName echoPin, PinName triggerPin);

public:
    /**
     * Start the measurement
     */
    void startMeasurement();

    /**
     * Get the distance in centimeters
     */
    float getDistance();

    /**
     * Set the minimum and maximum range
     */
    void setRanges(float min, float max);

    /**
     * Is there new data available?
     *
     * can be used to wait for measurement:
     * while(!sensor.isNewDataReady());
     */
    bool isNewDataReady() const;

    /**
     * Get the last elapsed time in microseconds
     */
    std::chrono::microseconds getElapsedTime();

private:
    /**
     * Trigger Pin
     */
    DigitalOut m_trigger;

    /**
     * Echo Interrupt Pin
     */
    InterruptIn m_echo;

    /**
     * High-resolution (us) mbed timer
     */
    Timer m_timer;

    /**
     * Last measured distance in centimeters
     */
    float m_distance;

    /**
     * The last measured elapsed time
     */
    std::chrono::microseconds m_elapsedTime{};

    /**
     * Minimum distance measured
     */
    float m_minDistance;

    /**
     * Maximum distance measured
     */
    float m_maxDistance;

    /**
     * Timeout for resetting the trigger pin
     */
    Timeout m_triggerTimeout;

    /**
     * Timeout for echo response
     */
    Timeout m_echoTimeout;

    /**
     * Allows waiting for sensor readout
     */
    bool m_newDataReady;

    /**
     * Makes this class stateful
     */
    bool m_timerStarted;

private:
    /**
     * Starts the timer
     * Used to measure the time
     *
     * @internal
     */
    void startTimer();

    /**
     * Stops the timer
     * Used for timeout and interrupt handling in startTimer
     *
     * @internal
     */
    void stopTimer();

    /**
     * Clears the trigger pin
     * Used in startMeasurement() to automatically clear the trigger pin
     *
     * @internal
     */
    void turnOffTrigger();
};
