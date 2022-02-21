#include "eventthread.h"
#include "console.hpp"

Mutex eventThreadStartMutex;

EventThread::EventThread(osPriority_t prio, const char* threadName)
    : queue(512, nullptr), thread(prio, 1024, nullptr, threadName)
{
}

void EventThread::start()
{
    eventThreadStartMutex.lock();
    osStatus status = thread.start(callback(&queue, &EventQueue::dispatch_forever));
    ThisThread::sleep_for(1s); // TEST
    eventThreadStartMutex.unlock();

    Thread::State state = thread.get_state();

    Console::getInstance().writelnf("EventThread Status: %02X, State: %d", &status, state);
}

void EventThread::join()
{
    thread.join();
}
