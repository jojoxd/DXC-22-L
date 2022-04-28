#include <mbed.h>

#include "console.hpp"
#include "sensor/HCSR04.h"

#define ECHO_PIN A0
#define TRIG_PIN A1

/**
 * Shows how to use the HCSR04 implementation
 */
[[noreturn]] void ex_HCSR04_Implementation()
{
    HCSR04 sensor(ECHO_PIN, TRIG_PIN);

    // Ensure sensor readout is always in this range (in cm)
    sensor.setRanges(2.0f, 30.0f);

    Console& console = Console::getInstance();

    while(true) {
        sensor.startMeasurement();
        while(!sensor.isNewDataReady()); // Wait for sensor data

        float distanceInCentimeters = sensor.getDistance();

        console.writelnf("Distance: %d cm", (int)distanceInCentimeters);

        ThisThread::sleep_for(500ms);
    }
}