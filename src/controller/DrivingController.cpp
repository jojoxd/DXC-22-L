#include "DrivingController.h"

DrivingController::DrivingController(MotorDriver* leftDriver, MotorDriver* rightDriver, ConsoleInput* input)
    : m_leftDriver(leftDriver), m_rightDriver(rightDriver)
{
    input->attachPauseCallback(callback(this, &DrivingController::onPause));
    input->attachResumeCallback(callback(this, &DrivingController::onResume));
}

DrivingController::~DrivingController()
{
    m_ticker.detach();
}

void DrivingController::start()
{
    if(m_isRunning)
        return;

    m_ticker.attach(callback(this, &DrivingController::handleDriving), m_interval);
    m_isRunning = true;
}

void DrivingController::stop()
{
    m_ticker.detach();
    m_isRunning = false;

    m_leftDriver->setSpeed(0);
    m_rightDriver->setSpeed(0);
}

bool DrivingController::isRunning() const
{
    return m_isRunning;
}

void DrivingController::setBias(CNY70Array::Bias bias)
{
    m_bias = bias;
}

void DrivingController::handleDriving()
{
    m_ticks++;

    if(m_bias == CNY70Array::Bias::Center) {
        m_speedLeft = DRCTL_SPEED_FORWARD;
        m_speedRight = DRCTL_SPEED_FORWARD;
    }

    if(m_bias == CNY70Array::Bias::Left) {
        m_speedLeft = DRCTL_SPEED_SLOW;
        m_speedRight = DRCTL_SPEED_FAST;
    }

    if(m_bias == CNY70Array::Bias::Right) {
        m_speedLeft = DRCTL_SPEED_FAST;
        m_speedRight = DRCTL_SPEED_SLOW;
    }

    m_leftDriver->setSpeed(m_speedLeft);
    m_rightDriver->setSpeed(m_speedRight);
}

void DrivingController::onPause()
{
    stop();
}

void DrivingController::onResume()
{
    start();
}
