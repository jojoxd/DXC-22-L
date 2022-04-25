#pragma once

#include <mbed.h>
#include <string>

#include "helper/config.h"
#include "util.hpp"

#ifndef CONSOLE_ISR_QUEUE_SZ
    #define CONSOLE_ISR_QUEUE_SZ 8
#endif

#ifndef CONSOLE_ISR_EVENT_SZ
    #define CONSOLE_ISR_EVENT_SZ (sizeof(mbed::Callback<void(const char*, const char*)>) + 4 * sizeof(float))
#endif

class Console
{
public:
    Console()
        : m_serial(CONSOLE_TX, CONSOLE_RX, CONSOLE_BAUDRATE), m_queue(CONSOLE_ISR_QUEUE_SZ * CONSOLE_ISR_EVENT_SZ)
    {
        m_serial.set_blocking(true);
    }

    ~Console() = default;

    inline static Console& getInstance()
    {
        static Console s_instance;

        return s_instance;
    }

protected:
    BufferedSerial m_serial;

    EventQueue m_queue;

public:
    void write(const string& ctx, const string& str)
    {
        int millisFromEpoch = (int)Kernel::Clock::now().time_since_epoch().count();
        string context = ctx;

        const string formatted = util::string_fmt(
            "[% 4d.%03d] %s: %s",
            millisFromEpoch / 1000,
            millisFromEpoch % 1000,
            context.append(std::max(0, 16 - (int)context.length()), ' ').c_str(),
            str.c_str()
        );

        m_serial.write(formatted.c_str(), formatted.length());
    }

    void writeln(const string& str)
    {
        write(ThisThread::get_name(), str + "\r\n");
    }

    template<typename... Args>
    void writef(const string& str, Args... args)
    {
        write(ThisThread::get_name(), util::string_fmt(str, args...));
    }

    template<typename... Args>
    void writelnf(const string& str, Args... args)
    {
        writeln(util::string_fmt(str, args...));
    }

    /**
     * Allows writing to console from ISR context.
     *
     * Use *very* sparingly!
     * silently fails if queue is full.
     */
    template<typename ...Args>
    inline void ISR_writelnf(const char* ctx, const char* str, Args... args)
    {
        m_queue.call(callback([](const char* in_ctx, const char* in_str, Args... args) {
            Console& console = Console::getInstance();

            const string ctx = util::string_fmt("ISR:%s", in_ctx);
            const string msg = util::string_fmt("%s\r\n", util::string_fmt(in_str, args...).c_str());

            console.write(ctx, msg);
        }), ctx, str, args...);
    }

    /**
     * Handle the ISR_writelnf() queue
     */
    inline void ISR_handle()
    {
        for(int i = 0; i < CONSOLE_ISR_QUEUE_SZ; i++) {
            m_queue.dispatch_once();
        }
    }
};
