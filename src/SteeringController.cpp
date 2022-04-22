#include "SteeringController.h"

SteeringController::SteeringController(PinName left, PinName center, PinName right)
    : m_left(left), m_center(center), m_right(right)
{
}

float SteeringController::getBias()
{
    CNY70::SurfaceData left = m_left.getSurfaceData();
    CNY70::SurfaceData center = m_center.getSurfaceData();
    CNY70::SurfaceData right = m_right.getSurfaceData();

    // Domain: [-1.0f .. 1.0f] == [Max Left .. Max Right]
    return -1.0f;
}

void SteeringController::doSteering()
{
    float bias = getBias();

    // @TODO
}
