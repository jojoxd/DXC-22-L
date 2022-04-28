#pragma once

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
#define DRCTL_TICKER_INTERVAL 1'000us

// These depend on generalized PCB
#define CNY70_LEFT PinName::A0
#define CNY70_CENTER PinName::A2
#define CNY70_RIGHT PinName::A3
