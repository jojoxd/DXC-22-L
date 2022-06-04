#pragma once

#include <mbed.h>

#include "helper/macros.h"
#include "console.hpp"
#include "driver/MotorDriver.h"
#include "ConsoleInput.hpp"
#include "sensor/HCSR04.h"
#include "sensor/CNY70Array.h"
#include "controller/DrivingController.h"


/**
 * Main Application Context
 */
class MainContext
{
public:
    MainContext()
            : leftMotor(DRCTL_LEFTMOTOR_PWM, DRCTL_LEFTMOTOR_DIR, DRCTL_LEFTMOTOR_MUL),
              rightMotor(DRCTL_RIGHTMOTOR_PWM, DRCTL_RIGHTMOTOR_DIR, DRCTL_RIGHTMOTOR_MUL),
              console(Console::getInstance()),
              input(console),
              distanceSensor(HCSR04_ECHO, HCSR04_TRIG),
              drivingController(&leftMotor, &rightMotor, &input),
              sensorArray(CNY70_LEFT, CNY70_CENTER, CNY70_RIGHT)
    {
        distanceSensor.setRanges(10.0f, 40.0f);
    }

public:
    MotorDriver leftMotor;
    MotorDriver rightMotor;

    Console& console;

    ConsoleInput input;

    HCSR04 distanceSensor;

    DrivingController drivingController;
    CNY70Array sensorArray;

    uint32_t ticks = 0;

public:
    inline void tick()
    {
        ticks++;

        console.writelnf("tick=%d", ticks);

        input.handleInput();

        updateDrivingController();

        handleDistance();

        console.ISR_handle();
    }

protected:
    inline void updateDrivingController()
    {
        CNY70Array::Bias bias = sensorArray.getBias();
        drivingController.setBias(bias);

        float leftSpeedPct = leftMotor.getSpeed(false) * 100.0f;
        float rightSpeedPct = rightMotor.getSpeed(false) * 100.0f;

        console.writelnf(
                "cny70/bias=%d, drctl/leftSpeed=%d%%, drctl/rightSpeed=%d%%",
                bias,
                (int) leftSpeedPct,
                (int) rightSpeedPct
        );
    }

    inline void handleDistance()
    {
        if(distanceSensor.isNewDataReady()) {
            float distance = distanceSensor.getDistance();

            if(ticks % 1 == 0) {
                console.writelnf("hc-sr04/distance=%dcm", (int) distance);
            }

            if(distance < HCSR04_STOP_LENGTH) {
                drivingController.stop();
            } else {
                drivingController.start();
            }
        }

        if(!distanceSensor.isRunning()) {
            console.writeln("hc-sr04/start");
            distanceSensor.startMeasurement();
        }
    }
};
