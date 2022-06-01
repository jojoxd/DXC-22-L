#include <mbed.h>

#include "sensor/HCSR04.h"
#include "controller/DrivingController.h"
#include "driver/MotorDriver.h"
#include "helper/macros.h"
#include "console.hpp"
#include "sensor/CNY70Array.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

int main()
{
    Console& console = Console::getInstance();

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

    MotorDriver leftMotor(D11, D12);
    MotorDriver rightMotor(D9, D10);
    HCSR04 distanceSensor(D7, D8);

    DrivingController drivingController(&leftMotor, &rightMotor);
    drivingController.start();
    CNY70Array sensorArray(CNY70_LEFT, CNY70_CENTER, CNY70_RIGHT);

    while(true) {
        drivingController.setBias(sensorArray.getBias());

        float leftSpeedPct = leftMotor.getSpeed() * 100.0f;
        float rightSpeedPct = rightMotor.getSpeed() * 100.0f;
        console.writelnf("Left Speed: %d%%, Right Speed: %d%%", (int)leftSpeedPct, (int)rightSpeedPct);

        ThisThread::sleep_for(10ms);
    }

    return 0;
}

#pragma clang diagnostic pop