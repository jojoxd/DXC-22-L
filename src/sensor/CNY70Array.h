#pragma once

#include <mbed.h>

#include "CNY70.h"
#include "console.hpp"


/**
 * Sensor Array
 *
 * Contains logic to define which way we want to drive
 */
class CNY70Array
{
public:
    CNY70Array(PinName leftPin, PinName centerPin, PinName rightPin)
            : m_leftSensor(leftPin), m_centerSensor(centerPin), m_rightSensor(rightPin)
    {
    }

    ~CNY70Array() = default;

public:
    enum Bias
    {
        Left = 0,
        Center = 1,
        Right = 2,
    };

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

        float leftV = m_leftSensor.getVoltage();
        float rightV = m_rightSensor.getVoltage();

        if(leftV - 0.1f <= rightV && leftV + 0.1f >= rightV) {
            return Center;
        }

        if(leftV > rightV) {
            return Right;
        } else {
            return Left;
        }

        if(m_leftSensor.getSurface() == CNY70::Surface::Light)
            return Left;

        if(m_rightSensor.getSurface() == CNY70::Surface::Light)
            return Right;

        return Center;
    }

    bool isOnLine()
    {
        return false;
    }
};
