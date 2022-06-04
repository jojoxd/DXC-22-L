#pragma once

#include <mbed.h>

#include "helper/config.h"
#include "console/Console.hpp"
#include "driver/MotorDriver.h"

/**
 * PaperThrower contains all logic pertaining throwing paper from the robot
 *
 * This is a dynamic class, as all teams have different ways of throwing the paper.
 * This class is split up in 2 features:
 *
 * - PAPERTHROWER_TRANSLATE:
 *     This feature flag is used to enable translation of a thrower arm.
 *     > Sub-feature: PAPERTHROWER_TRANSLATE_WATERMARKS
 *         This enables the use of endstops (watermarks) to define when to stop.
 *         Both the Low and High watermark should be set for this to work.
 *         These inputs are pull-down, and should be high when we should stop the translate motor.
 *
 * - PAPERTHROWER_THROW:
 *     This feature flag is used to enable a motor for throwing the paper away
 *
 *     > Sub-configuration: PAPERTHROWER_THROW_TICKS
 *         This sets the amount of ticks (100ms / tick) that we should throw the paper for.
 *
 * These feature flags (and configuration) can be set in config.h
 */
class PaperThrower
{
public:
    explicit PaperThrower();
    ~PaperThrower() = default;

public:
    void execute();

protected:
    Console& m_console;

    #if defined(PAPERTHROWER_TRANSLATE)
        MotorDriver m_translateMotor = {
            PAPERTHROWER_TRANSLATE_PWM,
            PAPERTHROWER_TRANSLATE_DIR,
            PAPERTHROWER_TRANSLATE_MUL
        };

        #if defined(PAPERTHROWER_TRANSLATE_WATERMARKS)
            DigitalIn m_translateHighWatermark = {
                PAPERTHROWER_TRANSLATE_WATERMARKS_HIGH,
                PinMode::PullDown
            };

            DigitalIn m_translateLowWatermark = {
                PAPERTHROWER_TRANSLATE_WATERMARKS_LOW,
                PinMode::PullDown
            };
        #endif
    #endif

    #if defined(PAPERTHROWER_THROW)
        MotorDriver m_throwMotor = {
            PAPERTHROWER_THROW_PWM,
            PAPERTHROWER_THROW_DIR,
            PAPERTHROWER_THROW_MUL
        };
    #endif

protected:
    inline void raise();

    inline void throwPaper();

    inline void lower();
};