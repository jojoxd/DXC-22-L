#include <mbed.h>

#include "sensor/HCSR04.h"
#include "helper/macros.h"
#include "console.hpp"
#include "SteeringController.h"

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

    SteeringController sc(CNY70_LEFT, CNY70_CENTER, CNY70_RIGHT);

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

    HCSR04 sensor(D8, D9);

    while(true) {
        // sc.getBias();

        sensor.startMeasurement();
        while(!sensor.isNewDataReady()) {}
        console.writelnf("Distance: %d cm (elapsed time = %d us)", (int)sensor.getDistance(), (int)sensor.getElapsedTime().count());

        ThisThread::sleep_for(200ms);
    }

    return 0;
}
