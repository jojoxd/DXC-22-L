#pragma once

#include "helper/macros.h"

/**
 * SECTION: Build System
 */

// Niet veranderen, doet build systeem automatisch (-D VERSION_STR=...)
#ifndef VERSION_STR
    #define VERSION_STR 0.0.0
#endif

// Niet veranderen, doet build systeem automatisch (-D VERSION_COMMIT_SHA=...)
#ifndef VERSION_COMMIT_SHA
    #define VERSION_COMMIT_SHA dev
#endif

/**
 * Team Selection:
 *
 * - Team 1 = Robot with weird steering and extra thrower motor
 * - Team 2 = Robot with auto-throw system
 * - Team 3 = Mini Test Robot
 */

/**
 * SECTION: Console
 */

// Console Configuration
#define CONSOLE_TX USBTX
#define CONSOLE_RX USBRX
#define CONSOLE_BAUDRATE 115200

// ISR Message Queue size
#define CONSOLE_ISR_QUEUE_SZ 32

// 0=absolute or 1=relative
#define CNY70_TYPE 0

// 0=instant or 1=average
#define DRIVER_METHOD 1

// Enable data logging
#define DATA_LOGGING

// Require Computer Serial p<enter> signal to start
#define STARTUP_PAUSED

/**
 * SECTION: Driving Controller
 */

// Driver Controller Ticker interval
#define DRCTL_TICKER_INTERVAL 100ms

// End Stop length in cm (float)
#define HCSR04_STOP_LENGTH 20.0f

#if DXC_TEAM == 1
    /**
     * Robot with weird steering and extra thrower motor
     */

    #define PAPERTHROWER_TRANSLATE
    #define PAPERTHROWER_TRANSLATE_PWM PinName::D6
    #define PAPERTHROWER_TRANSLATE_DIR PinName::D5
    #define PAPERTHROWER_TRANSLATE_MUL 1.0f

    #define PAPERTHROWER_THROW
    #define PAPERTHROWER_THROW_PWM PinName::D6
    #define PAPERTHROWER_THROW_DIR PinName::D5
    #define PAPERTHROWER_THROW_MUL 1.0f
    #define PAPERTHROWER_THROW_TICKS 50
#endif

#if DXC_TEAM == 2
    /**
     * Robot with auto-throw system
     */

    #define PAPERTHROWER_TRANSLATE
    #define PAPERTHROWER_TRANSLATE_PWM PinName::D6
    #define PAPERTHROWER_TRANSLATE_DIR PinName::D5
    #define PAPERTHROWER_TRANSLATE_MUL 1.0f

    #define PAPERTHROWER_TRANSLATE_WATERMARKS
    #define PAPERTHROWER_TRANSLATE_WATERMARKS_LOW PinName::D4
    #define PAPERTHROWER_TRANSLATE_WATERMARKS_HIGH PinName::D3
#endif

#if DXC_TEAM == 1 || DXC_TEAM == 2
    // Generalized PCB Config

    #define CNY70_LEFT PinName::A0
    #define CNY70_CENTER PinName::A1
    #define CNY70_RIGHT PinName::A2

    #define DRCTL_SPEED_FAST 1.0f
    #define DRCTL_SPEED_SLOW 0.0f

    // Left Motor Config
    #define DRCTL_LEFTMOTOR_PWM PinName::D11
    #define DRCTL_LEFTMOTOR_DIR PinName::D12
    #define DRCTL_LEFTMOTOR_MUL 1.0f

    // Right Motor Config
    #define DRCTL_RIGHTMOTOR_PWM PinName::D9
    #define DRCTL_RIGHTMOTOR_DIR PinName::D10
    #define DRCTL_RIGHTMOTOR_MUL 0.7f

    #define HCSR04_ECHO PinName::D7
    #define HCSR04_TRIG PinName::D8
#endif

#if DXC_TEAM == 3
    /**
     * DXC_TEAM 3 is the small test robot
     */

    #define CNY70_LEFT PinName::A0
    #define CNY70_CENTER PinName::A1
    #define CNY70_RIGHT PinName::A2

    #define DRCTL_SPEED_FAST 1.0f
    #define DRCTL_SPEED_SLOW 0.0f

    #define DRV5053_SENSOR PinName::A3

    // Left Motor Config
    #define DRCTL_LEFTMOTOR_PWM PinName::D11
    #define DRCTL_LEFTMOTOR_DIR PinName::D12
    #define DRCTL_LEFTMOTOR_MUL 1.0f

    // Right Motor Config
    #define DRCTL_RIGHTMOTOR_PWM PinName::D9
    #define DRCTL_RIGHTMOTOR_DIR PinName::D10
    #define DRCTL_RIGHTMOTOR_MUL 0.7f

    #define HCSR04_ECHO PinName::D7
    #define HCSR04_TRIG PinName::D8
#endif


// macros - DO NOT EDIT
#if DRIVER_METHOD == 0
    #define DRIVER_METHOD_INSTANT
#elif DRIVER_METHOD == 1
    #define DRIVER_METHOD_AVERAGE
#else
    #error "Exhausted Driver Method: " DRIVER_METHOD " not available"
#endif

#if CNY70_TYPE == 0
    #define CNY70_TYPE_ABSOLUTE
#elif CNY70_TYPE == 1
    #define CNY70_TYPE_RELATIVE
#else
    #error "Exhausted CNY70 Type: " CNY70_TYPE " not available"
#endif
