#include <mbed.h>

#include "helper/macros.h"
#include "console.hpp"
#include "MainContext.hpp"

#ifndef STARTUP_PAUSED
    #define STARTUP_PAUSED false
#endif

[[noreturn]] int main()
{
    Console& console = Console::getInstance();

    MainContext context;

    console.writeln(CONSOLE_TITLE);

    #ifdef DXC_TEAM_1
        // Team 1 Custom Code
//        console.writeln("Team 1");
    #endif

    #ifdef DXC_TEAM_2
        // Team 2 Custom Code
//        console.writeln("Team 2");
    #endif

    #ifdef DXC_TEAM_3
        // Team 3 Custom Code
        console.writeln("Small Test Robot");
    #endif

    #if STARTUP_PAUSED
        context.input.togglePause();
    #endif

    context.drivingController.start();

    while(true) {
        context.tick();

        ThisThread::sleep_for(DRCTL_TICKER_INTERVAL / 2);
    }
}
