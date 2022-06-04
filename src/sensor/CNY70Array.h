#pragma once

#include <mbed.h>

#include "sensor/CNY70.h"
#include "console/Console.hpp"


#ifndef CNY70_RELATIVE_DELTA
    #define CNY70_RELATIVE_DELTA 0.3f
#endif

/**
 * Sensor Array
 *
 * Contains logic to define which way we want to drive
 *
 * The sensor array supports 2 modes:
 * - CNY70_TYPE = 0: Absolute mode:
 *     Uses an absolute cutoff (CNY70_CUTOFF) to define a direction
 *     > This mode will always try to pull left
 *     > This mode uses the CNY70::Surface returned straight from the CNY70 class
 *
 * - CNY70_TYPE = 1: Relative mode:
 *     Uses a delta to check if we need to go straight
 *     Otherwise, we check both left and right sensors to define our direction.
 *     This mode is a little slower, but _should_ work better with sudden light level changes
 *     when both sensors detect it at the same time.
 *     > This mode uses the voltage from the CNY70 class
 */
class CNY70Array
{
public:
    enum Bias
    {
        Left = 0,
        Center = 1,
        Right = 2,
    };

public:
    CNY70Array(PinName leftPin, PinName centerPin, PinName rightPin);
    ~CNY70Array() = default;

protected:
    CNY70 m_leftSensor;
    CNY70 m_centerSensor;
    CNY70 m_rightSensor;

public:
    CNY70Array::Bias getBias();
};
