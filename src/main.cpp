#include <mbed.h>

#include "helper/macros.h"
#include "console.hpp"

void test1(Console* console)
{
    console->writeln("TEST1 TEST1 TEST1 >>>>>>>>>>>>>>>>>>>>");
}

void consoleInput(void* buffer)
{
    Console::getInstance().writelnf("consoleInput() called (%s)", (char*)buffer);
}

int main()
{
    Console& console = Console::getInstance();

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

    while(true) {
        ThisThread::sleep_for(1000ms);
    }

    return 0;
}
