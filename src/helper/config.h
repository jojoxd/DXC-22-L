#pragma once

// Niet veranderen, doet build systeem automatisch (-D VERSION_STR=...)
#ifndef VERSION_STR
    #define VERSION_STR 0.0.0
#endif

// Niet veranderen, doet build systeem automatisch (-D VERSION_COMMIT_SHA=...)
#ifndef VERSION_COMMIT_SHA
    #define VERSION_COMMIT_SHA dev
#endif


// These depend on generalized PCB
#define CNY70_LEFT PinName::A0
#define CNY70_CENTER PinName::A2
#define CNY70_RIGHT PinName::A3

// ISR Message Queue for console

#define CONSOLE_TX USBTX
#define CONSOLE_RX USBRX
#define CONSOLE_BAUDRATE 115200

#define CONSOLE_ISR_QUEUE_SZ 32
