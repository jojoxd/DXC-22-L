#include <mbed.h>

#include "driver/MotorFunction.h"
#include "driver/MotorDriver.h"
#include "sensor/HCSR04.h"
#include "helper/macros.h"
#include "console.hpp"
#include "SteeringController.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"

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
    sensor.setRanges(5.0f, 25.0f);

    InterruptIn btn(D13, PullDown);
    MotorDriver driver(D10, D12);
    MotorDriver::Direction dir = MotorDriver::ClockWise;

    btn.rise([&]() {
        dir = dir == MotorDriver::ClockWise ? MotorDriver::CounterClockWise : MotorDriver::ClockWise;
    });

    MotorFunction rampUp(&driver, 1'000'000us, 32, callback([&](MotorDriver* drv, int currentRep) {
        auto percent = ((float)currentRep / 32.0f) * 100.0f;

        console.ISR_writelnf("Ramp UP", "%d => %d%%", currentRep, (int)percent);

        drv->setSpeed(percent);
    }));

    MotorFunction rampDown(&driver, 1'000'000us, 32, [&](MotorDriver* drv, int currentRep) {
        auto percent = ((32.0f - (float)currentRep) / 32.0f) * 100.0f;

        console.ISR_writelnf("Ramp DOWN", "%d = %d%%", currentRep, (int)percent);

        drv->setSpeed(percent);
    });

    while(true) {
        rampUp.start();
        while(rampUp.isRunning());

        rampDown.start();
        while(rampDown.isRunning());

        console.writeln("End while()");

        console.ISR_handle();
    }

//    while(true) {
//        // sc.getBias();
//
//        sensor.startMeasurement();
//        while(!sensor.isNewDataReady()) {}
//
//        // sensor => [5..25] => [0..20] => [0..100] => pwmSpeed
//        auto pwmSpeed = (sensor.getDistance() - 5.0f) * 5.0f;
//
//        // Stop when low
////        if((pwmSpeed + 0.05f) < 30.0f) {
////            pwmSpeed = 0.0f;
////        }
//
//        driver.setSpeed(pwmSpeed);
//        driver.setDirection(dir);
//
//        console.writelnf(
//            "Speed: %d%% (DutyCycle: %d%%), dir: %s, Distance: %d cm (elapsed time = %d us)",
//            (int)pwmSpeed,
//            (int) (driver.getSpeed() * 100.0f),
//            dir == MotorDriver::ClockWise ? "CW" : "CCW",
//            (int)sensor.getDistance(),
//            (int)sensor.getElapsedTime().count()
//        );
//
//        ThisThread::sleep_for(200ms);
//    }

    return 0;
}

#pragma clang diagnostic pop