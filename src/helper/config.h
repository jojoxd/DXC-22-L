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
//#define STARTUP_PAUSED

// Disable Console
// #define CONSOLE_DISABLED

/**
 * SECTION: Driving Controller
 */

// Driver Controller Ticker interval
#define DRCTL_TICKER_INTERVAL 100ms

// End Stop length in cm (float)
#define HCSR04_STOP_LENGTH 20.0f

// @TODO: Map DRV5053, most likely will use center CNY70 channel (A1)
#define DRV5053_SENSOR PinName::A2

#if DXC_TEAM == 1
    /**
     * Robot with weird steering and extra thrower motor
     */

    #define PAPERTHROWER_TRANSLATE
    #define PAPERTHROWER_TRANSLATE_MUL 1.0f

    #define PAPERTHROWER_THROW
    #define PAPERTHROWER_THROW_MUL 1.0f
    #define PAPERTHROWER_THROW_TICKS 50
#endif

#if DXC_TEAM == 2
    /**
     * Robot with auto-throw system
     */

    #define PAPERTHROWER_TRANSLATE

    #define PAPERTHROWER_TRANSLATE_WATERMARKS

    #define DRCTL_SPEED_FAST 0.8f
    #define DRCTL_SPEED_SLOW 0.0f

    #define DRCTL_LEFTMOTOR_MUL 1.0f

    #define DRCTL_RIGHTMOTOR_MUL -1.0f

    #define PAPERTHROWER_TRANSLATE_MUL 1.0f
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

#if DXC_TEAM == 1 || DXC_TEAM == 2
    /**
     * Generalized PCB Config
     *
     * LIM1 (PA_9/D1) is defaulted to Low Watermark for PaperThrower
     * LIM2 (PA_10/D0) is defaulted to High Watermark for PaperThrower
     *
     * HCSR-04 { TRIG = PB_5 (D11), ECHO = PB_4 (D12)}
     *
     * There are 4 Motor Driver "Slots" on 2 connectors:
     * - C1 : M1 = Motor 1, Direction is shared with C2:M1, defaults to "Translate Motor"
     * - C1 : M2 = Motor 2, defaults to "Left Motor"
     * - C2 : M1 = Motor 3, Direction is shared with C1:M1, defaults to "Throw Motor"
     * - C2 : M2 = Motor 4, defaults to "Right Motor"
     *
     * Optionally, you can override:
     *
     * (From DrivingController.h)
     * - DRCTL_SPEED_SLOW (Default: 0.0f)
     * - DRCTL_SPEED_FAST (Default: 1.0f)
     * - DRCTL_TICKER_INTERVAL (Default: 1'000us)
     *
     * (From PaperThrower.h)
     * - PAPERTHROWER_TRANSLATE_MUL (Default: 1.0f)
     * - PAPERTHROWER_THROW_MUL (Default: 1.0f)
     * - PAPERTHROWER_THROW_TICKS (Default: 50)
     * - Feature Flag: PAPERTHROWER_TRANSLATE: See PaperThrower.h
     * - Feature Flag: PAPERTHROWER_TRANSLATE_WATERMARKS: See PaperThrower.h
     * - Feature Flag: PAPERTHROWER_THROW: See PaperThrower.h
     */

    // CNY Sensors {CNY_LEFT = PA_0 (A0), CNY_CENTER = PA_1 (A1), CNY_RIGHT = PA_3 (A2)}
    #define CNY70_LEFT PinName::A2
    #define CNY70_CENTER PinName::A6
    #define CNY70_RIGHT PinName::A1

    // Left Motor Config (Slot: M2) {M2_ENABLE = PF_0 (D7), M4_DIR = PF_1 (D8)}
    #define DRCTL_LEFTMOTOR_PWM PinName::D3
    #define DRCTL_LEFTMOTOR_DIR PinName::D6

    // Right Motor Config (Slot: M4) {M4_ENABLE = PB_6 (D5), M4_DIR = PB_1 (D6)}
    #define DRCTL_RIGHTMOTOR_PWM PinName::D7
    #define DRCTL_RIGHTMOTOR_DIR PinName::D8


    #define HCSR04_TRIG PinName::D11
    #define HCSR04_ECHO PinName::D12

    // Translate Motor Config (Slot: M1, Shared w/ M3) {M1_ENABLE = PB_7 (D4), M1_DIR = PA_8 (D9)}
    // Optional, Enable with PAPERTHROWER_TRANSLATE
    #define PAPERTHROWER_TRANSLATE_PWM PinName::D5
    #define PAPERTHROWER_TRANSLATE_DIR PinName::D6

    // LIM1 {LIM1 = PA_9 (D1)}
    // Optional, Enable with PAPERTHROWER_TRANSLATE_WATERMARKS
    #define PAPERTHROWER_TRANSLATE_WATERMARKS_LOW PinName::D1

    // LIM2 {LIM2 = PA_10 (D0)}
    // Optional, Enable with PAPERTHROWER_TRANSLATE_WATERMARKS
    #define PAPERTHROWER_TRANSLATE_WATERMARKS_HIGH PinName::D0

    // Throw Motor Config (Slot: M3, Shared w/ M1) {M3_ENABLE = PB_0 (D3), M3_DIR = PA_8 (D9)}
    // Optional, Enable with PAPERTHROWER_THROW
    #define PAPERTHROWER_THROW_PWM PinName::D4
    #define PAPERTHROWER_THROW_DIR PinName::D9

    #define HV_ENABLE PinName::D2
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
