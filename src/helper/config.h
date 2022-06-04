#pragma once

#include "macros.h"

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
 * SECTION: Console
 */

// Console Configuration
#define CONSOLE_TX USBTX
#define CONSOLE_RX USBRX
#define CONSOLE_BAUDRATE 115200

// ISR Message Queue size
#define CONSOLE_ISR_QUEUE_SZ 32


/**
 * SECTION: Driving Controller
 */

// Driver Controller Ticker interval
#define DRCTL_TICKER_INTERVAL 100ms

#if DXC_TEAM == 3
    /**
     * DXC_TEAM 3 is the small test robot
     */

    #define CNY70_ANALOG

    #define CNY70_LEFT PinName::A0
    #define CNY70_CENTER PinName::A1
    #define CNY70_RIGHT PinName::A2

    #define DRCTL_SPEED_FAST 1.0f
    #define DRCTL_SPEED_SLOW 0.0f

    #define STARTUP_PAUSED true
#else
    // These depend on generalized PCB
    #define CNY70_LEFT PinName::A0
    #define CNY70_CENTER PinName::A2
    #define CNY70_RIGHT PinName::A3
#endif

#ifdef DXC_TEAM_3

#endif
