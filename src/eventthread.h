#pragma once

#include <mbed.h>
#include <list>

template<typename T>
struct EventTrigger
{
    const char* eventName;
    Callback<void(T)> callback;
};

class EventThread
{
public:
    explicit EventThread(osPriority_t prio, const char* threadName);
    EventThread(EventThread&) = default;
    ~EventThread() = default;

protected:
    EventQueue queue;
    Thread thread;

    std::list<EventTrigger<void*>> triggers = {};

public:
    void start();
    void join();

    inline EventQueue* getQueue()
    {
        return &queue;
    }

    template <typename T, typename... Args>
    int push(Callback<T> callback, Args... args)
    {
        return queue.call(callback, args...);
    }

    template<typename T>
    void add_trigger(const char* str, Callback<T> callback)
    {
        triggers.push_back({ str, callback });
    }

    template<typename... Args>
    void dispatch(const char* str, Args... args)
    {
        for(auto trigger : triggers) {
            if(trigger.eventName == str) {
                push(trigger.callback, args...);
            }
        }
    }
};
