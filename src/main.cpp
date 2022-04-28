#include <mbed.h>

#include "driver/MotorDriver.h"
#include "sensor/HCSR04.h"
#include "helper/macros.h"
#include "console.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

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

    HCSR04 sensor(D8, D9);
    sensor.setRanges(5.0f, 25.0f);

    InterruptIn btn(D13, PullDown);
    MotorDriver driver(D10, D12);

    while(true) {
        console.ISR_handle();
        ThisThread::sleep_for(250ms);
    }

    return 0;
}

#pragma clang diagnostic pop