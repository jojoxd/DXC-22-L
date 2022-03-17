#include "SteeringController.h"

SteeringController::SteeringController(PinName left, PinName center, PinName right)
    : m_left(left), m_center(center), m_right(right)
{
}

SteeringController::Bias SteeringController::getBias()
{
    CNY70::Surface left = m_left.getSurface();
    CNY70::Surface center = m_center.getSurface();
    CNY70::Surface right = m_right.getSurface();

    if(left == CNY70::Surface::Light) {
        if(center == CNY70::Surface::Light) {
            // Low Bias Left
            return LowLeft;
        }

        // High Bias Left
        return Left;
    }

    if(right == CNY70::Surface::Light) {
        if(center == CNY70::Surface::Light) {
            // Low Bias Right
            return LowRight;
        }

        // High Bias Right
        return Right;
    }

    if(center == CNY70::Surface::Light) {
        return Center;
    }

    return Unknown;
}
