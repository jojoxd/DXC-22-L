#include <mbed.h>

#include "helper/macros.h"
#include "console.hpp"
#include "eventthread.h"

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
    EventThread commandBus(osPriorityNormal1, "Command Bus");

    Console& console = Console::getInstance();

    commandBus.start();

    console.setupSigio(commandBus);

    commandBus.add_trigger("console_input", callback(consoleInput));

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

        int queueId1 = commandBus.push(callback(test1, &console));
        console.writelnf("Queued Func with id %d", queueId1);
    }

    return 0;
}
