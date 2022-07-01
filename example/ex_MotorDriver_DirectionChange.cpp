#include <mbed.h>

#include "console/Console.hpp"
#include "driver/MotorDriver.h"

#define PWM_PIN A0
#define DIRECTION_PIN A1

#define PI_F 3.1415f

/**
 * Example of MotorDriver Direction Changing
 *
 * Desmos Graph of MotorFunction: https://www.desmos.com/calculator/255nieta1f
 *
 * The graph on the X axis represents time (in this case, 1:1 mapping of seconds)
 * The Y axis is the motor speed and direction
 *
 * The function of the graph modulates the output of the driver one way, keeps it that way at 100% for 1*x,
 * then reverses the direction over a span of a second, and keeps it spinning that way for 1*x at 100% speed.
 *
 * Domain of Driver Speed is [-1.0f .. 1.0f],
 * which maps to the following domain [-100% Clockwise .. 100% CounterClockWise]
 *
 * NOTE: The Clockwise/CounterClockwise may be inverted if the motor's wires are reversed!
 */
[[noreturn]] void ex_MotorDriver_DirectionChange()
{
    MotorDriver driver(PWM_PIN, DIRECTION_PIN);
    Console& console = Console::getInstance();

    int currentRep = 0;
    while(true) {
        currentRep++;

        float x = (float)currentRep / 1000.0f;

        float a = 2.0f; // Amplitude
        float p = 4.0f; // Period

        float speed = max(-1.0f, min(1.0f, 2.0f * a / PI_F * asin(sin(2.0f * PI_F / p * x))));

        driver.setSpeed(speed);

        if(currentRep % 40 == 0)
            console.writelnf("func", "Speed@%d = %d%%", currentRep, (int)(driver.getSpeed() * 100.0f));

        ThisThread::sleep_for(250ms);
    }
}
