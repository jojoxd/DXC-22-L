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

/**
 * Console is the main way to talk to a computer using USB
 */
class Console
{
public:
    Console()
    {
        m_serial.set_blocking(false);
    }

    ~Console() = default;

    inline static Console& getInstance()
    {
        static Console s_instance;

        return s_instance;
    }

protected:
    BufferedSerial m_serial = { CONSOLE_TX, CONSOLE_RX, CONSOLE_BAUDRATE };

    EventQueue m_isrQueue = { CONSOLE_ISR_QUEUE_SZ * CONSOLE_ISR_EVENT_SZ };

public:
    /**
     * Write an unformatted string under context
     */
    void write(const std::string& ctx, const std::string& str)
    {
        int millisFromEpoch = (int)Kernel::Clock::now().time_since_epoch().count();
        string context = ctx;

        const std::string formatted = util::string_fmt(
            "[% 4d.%03d] %s: %s",
            millisFromEpoch / 1000,
            millisFromEpoch % 1000,
            context.append(std::max(0, 16 - (int)context.length()), ' ').c_str(),
            str.c_str()
        );

        m_serial.write(formatted.c_str(), formatted.length());

        // We need to sync, or lines will be cut off
        m_serial.sync();
    }

    /**
     * Write an unformatted string under the {ThreadName} context
     */
    void write(const std::string& str)
    {
        write(ThisThread::get_name(), str);
    }

    /**
     * Write un-formatted line
     */
    void writeln(const std::string& str)
    {
        write(str + "\r\n");
    }

    /**
     * Write formatted string
     */
    template<typename... Args>
    void writef(const std::string& str, Args... args)
    {
        write(util::string_fmt(str, args...));
    }

    /**
     * Write formatted line
     */
    template<typename... Args>
    void writelnf(const std::string& str, Args... args)
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
        m_isrQueue.call(callback([](const char* in_ctx, const char* in_str, Args... args) {
            Console& console = Console::getInstance();

            const std::string out_ctx = util::string_fmt("ISR:%s", in_ctx);
            const std::string out_msg = util::string_fmt("%s\r\n", util::string_fmt(in_str, args...).c_str());

            console.write(out_ctx, out_msg);
        }), ctx, str, args...);
    }

    /**
     * Handle the ISR_writelnf() queue
     */
    inline void ISR_handle()
    {
        for(int i = 0; i < CONSOLE_ISR_QUEUE_SZ; i++) {
            m_isrQueue.dispatch_once();
        }
    }

    ssize_t read(void* ptr, size_t sz)
    {
        return m_serial.read(ptr, sz);
    }
};
