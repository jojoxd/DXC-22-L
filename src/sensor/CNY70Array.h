#pragma once

#include <mbed.h>

#include "CNY70.h"

class CNY70Array
{
public:
    CNY70Array(PinName leftPin, PinName centerPin, PinName rightPin)
            : m_leftSensor(leftPin), m_centerSensor(centerPin), m_rightSensor(rightPin)
    {
    }

    ~CNY70Array() = default;

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
