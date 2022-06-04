#include <mbed.h>

#include "helper/config.h"
#include "console/Console.hpp"
#include "context/Context.h"

[[noreturn]] int main()
{
    Console& console = Console::getInstance();

    Context context;

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

    context.startup();

    while(true) {
        context.tick();

        ThisThread::sleep_for(DRCTL_TICKER_INTERVAL / 2);
    }
}
