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

protected:
    CNY70 m_leftSensor;
    CNY70 m_centerSensor;
    CNY70 m_rightSensor;

public:
    float getBias()
    {
        return -1.0f;
    }

    bool isOnLine()
    {
        return false;
    }
};
