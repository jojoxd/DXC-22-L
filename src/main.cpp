#include <mbed.h>

#include "helper/macros.h"
#include "console/console.hpp"

struct LedThreadData
{
    Console* console;
    DigitalOut* led;
};

THREAD led_thread(LedThreadData* data)
{
    while(true) {
        *(data->led) = !*(data->led);
        data->console->writeln("LED Toggle");

        ThisThread::sleep_for(1000ms);
    }
}

int main()
{
    Console& console = Console::getInstance();

    console.writeln(CONSOLE_TITLE);

    DigitalOut led(LED1);

    auto t = new Thread(osPriorityNormal1, 1024, nullptr, "TestThread");

    LedThreadData data;
    data.led = &led;
    data.console = &console;
    osStatus ret = t->start(callback(led_thread, &data));
    console.writelnf("Thread Started %02X", &ret);

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

    int count = 0;
    while(true) {
        console.writelnf("Led Status: %d %d", (int)led, count++);
        ThisThread::sleep_for(500ms);

        Thread::State state = t->get_state();
        console.writelnf("Thread State: %d", state);
    }

    return 0;
}
