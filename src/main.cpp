#include <mbed.h>

//#include "driver/MotorDriver.h"
//#include "sensor/HCSR04.h"
#include "helper/macros.h"
//#include "console.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main()
{
    //Console& console = Console::getInstance();

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
//        console.writeln("Team 3");
    #endif

//    HCSR04 sensor(D6, D7);
//    sensor.setRanges(5.0f, 25.0f);
//
//    InterruptIn btn(D13, PullDown);
//    MotorDriver driver(D10, D12);

//    util::MovingAverage<float, 5, int> avg;

    int test[256] = {0};

//    while(true) {
//        sensor.startMeasurement();
//        while(!sensor.isNewDataReady()); // Wait for sensor data
//
//        float distanceInCentimeters = sensor.getDistance();
//        int average = avg.next(distanceInCentimeters);
//
//        console.writelnf("Distance: %d cm (avg = %d cm) use test: %d", (int)distanceInCentimeters, average, test[0]);
//
//        ThisThread::sleep_for(1000ms);
//    }

    while(true) {
//        console.ISR_handle();
        ThisThread::sleep_for(250ms);
    }

    return 0;
}

#pragma clang diagnostic pop