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
    MotorDriver rightMotor(D9, D10, 0.7f);
    HCSR04 distanceSensor(D7, D8);
    distanceSensor.setRanges(10.0f, 40.0f);

    DrivingController drivingController(&leftMotor, &rightMotor);
    drivingController.start();
    CNY70Array sensorArray(CNY70_LEFT, CNY70_CENTER, CNY70_RIGHT);

    uint32_t ticks = 0;

    while(true) {
        ticks++;

        CNY70Array::Bias bias = sensorArray.getBias();
        drivingController.setBias(bias);

        if(distanceSensor.isNewDataReady()) {
            float distance = distanceSensor.getDistance();

            if(ticks % 10 == 0) {
                console.writelnf("T:%d Distance: %dcm", ticks, (int) distance);
            }

            if(distance < 20.0f) {
                drivingController.stop();
            } else {
                drivingController.start();
            }
        }

        if(!distanceSensor.isRunning()) {
            distanceSensor.startMeasurement();
        }

        if(ticks % 10 == 0) {
            float leftSpeedPct = leftMotor.getSpeed() * 100.0f;
            float rightSpeedPct = rightMotor.getSpeed() * 100.0f;

            console.writelnf(
                    "T:%d bias:%d, leftSpeed:%d%%, rightSpeed:%d%%",
                    ticks, bias, (int) leftSpeedPct, (int) rightSpeedPct);
        }

        console.ISR_handle();

        ThisThread::sleep_for(50ms);
    }

    return 0;
}

#pragma clang diagnostic pop