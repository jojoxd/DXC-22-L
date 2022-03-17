#pragma once

#include <mbed.h>
#include "CNY70.h"

class SteeringController
{
public:
    enum Bias
    {
        Left,
        Center,
        Right,

        LowLeft,
        LowRight,

        Unknown,
    };

public:
    SteeringController(PinName left, PinName center, PinName right);

    SteeringController::Bias getBias();

protected:
    CNY70 m_left;
    CNY70 m_center;
    CNY70 m_right;
};