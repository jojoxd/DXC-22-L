#pragma once

#include <mbed.h>

#include "console/Console.hpp"
#include "console/ConsoleInput.h"
#include "controller/DrivingController.h"
#include "controller/PaperThrower.h"
#include "driver/MotorDriver.h"
#include "helper/config.h"
#include "sensor/DRV5053.h"
#include "sensor/HCSR04.h"

/**
 * Main Application Context
 *
 * Contains startup and main loop routines
 */
class Context
{
public:
    explicit Context();

    ~Context() = default;

public:
    void tick();
    void startup();

protected:
    MotorDriver m_leftMotor = {
        DRCTL_LEFTMOTOR_PWM,
        DRCTL_LEFTMOTOR_DIR,
        DRCTL_LEFTMOTOR_MUL
    };

    MotorDriver m_rightMotor = {
        DRCTL_RIGHTMOTOR_PWM,
        DRCTL_RIGHTMOTOR_DIR,
        DRCTL_RIGHTMOTOR_MUL
    };

    PaperThrower m_paperThrower;

    Console& m_console = Console::getInstance();

    ConsoleInput m_consoleInput;

    HCSR04 m_distanceSensor = {
        HCSR04_ECHO,
        HCSR04_TRIG
    };

    DrivingController m_drivingController = {
        &m_leftMotor,
        &m_rightMotor,
        &m_consoleInput,
    };

    CNY70Array m_sensorArray = {
        CNY70_LEFT,
        CNY70_CENTER,
        CNY70_RIGHT
    };

    DRV5053 m_hallEffectSensor = {
            DRV5053_SENSOR
    };

    uint32_t m_ticks = 0;

protected:
    inline void updateDrivingController();
    inline void handleDistance();

    inline void throwPaper();

    inline void handleMagnet();
};
