#pragma once

#include <mbed.h>

#include "CNY70.h"
#include "console.hpp"


#ifndef CNY70_RELATIVE_DELTA
    #define CNY70_RELATIVE_DELTA 0.3f
#endif

/**
 * Sensor Array
 *
 * Contains logic to define which way we want to drive
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
    CNY70Array(PinName leftPin, PinName centerPin, PinName rightPin)
            : m_leftSensor(leftPin), m_centerSensor(centerPin), m_rightSensor(rightPin)
    {
    }

    ~CNY70Array() = default;

protected:
    CNY70 m_leftSensor;
    CNY70 m_centerSensor;
    CNY70 m_rightSensor;

public:
    Bias getBias()
    {
        Console& console = Console::getInstance();

        console.writelnf(
            "cny70/left=%dmV, cny70/center=%dmV, cny70/right=%dmV",
            (int)(m_leftSensor.getVoltage() * 1000.0f),
            (int)(m_centerSensor.getVoltage() * 1000.0f),
            (int)(m_rightSensor.getVoltage() * 1000.0f)
        );

    #if defined(CNY70_TYPE_RELATIVE)
        float leftV = m_leftSensor.getVoltage();
        float rightV = m_rightSensor.getVoltage();

        if((leftV - CNY70_RELATIVE_DELTA) <= rightV && (leftV + CNY70_RELATIVE_DELTA) >= rightV) {
            return Center;
        }

        if(leftV > rightV) {
            return Right;
        }

        return Left;
    #elif defined(CNY70_TYPE_ABSOLUTE)
        if(m_leftSensor.getSurface() == CNY70::Surface::Light)
            return Left;

        if(m_rightSensor.getSurface() == CNY70::Surface::Light)
            return Right;

        return Center;
    #endif
    }

    bool isOnLine()
    {
        return false;
    }
};
