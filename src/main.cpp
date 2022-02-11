#include <mbed.h>
#include "helper/macros.h"

#include "console/console.h"

int main()
{
    Console& console = Console::getInstance();

    console.writeln(CONSOLE_TITLE);

    #ifdef DXC_TEAM_1
        // Team 1 Custom Code
        console.writeln("Team 1");
    #endif

    #ifdef DXC_TEAM_2
        // Team 2 Custom Code
        console.writeln("Team 2");
    #endif

    #ifdef DXC_TEAM_3
        // Team 3 Custom Code
        console.writeln("Team 3");
    #endif

    return 0;
}
