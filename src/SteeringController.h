#pragma once

#include <mbed.h>
#include "CNY70.h"

class SteeringController
{
public:
    SteeringController(PinName left, PinName center, PinName right);

    float getBias();

    void doSteering();

protected:
    CNY70 m_left;
    CNY70 m_center;
    CNY70 m_right;
};
