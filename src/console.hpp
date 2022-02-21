#pragma once

#include <mbed.h>
#include <string>

#include "helper/config.h"
#include "util.hpp"
#include "eventthread.h"

class Console
{
public:
    Console()
        : serial(USBTX, USBRX, CONSOLE_BAUDRATE)
    {
        serial.set_blocking(false);
    }

    ~Console() = default;

    static Console& getInstance()
    {
        static Console instance;

        return instance;
    }

protected:
    BufferedSerial serial;

public:
    void write(const string& str)
    {
        int millisFromEpoch = (int)Kernel::Clock::now().time_since_epoch().count();
        string threadName = ThisThread::get_name();

        const string formatted = util::string_fmt(
            "[% 4d.%03d] %s: %s",
            millisFromEpoch / 1000,
            millisFromEpoch % 1000,
            threadName.append(std::max(0, 16 - (int)threadName.length()), ' ').c_str(),
            str.c_str()
        );

        serial.write(formatted.c_str(), formatted.length());
    }

    void writeln(const string& str)
    {
        write(str + "\r\n");
    }

    template<typename... Args>
    void writef(const string& str, Args... args)
    {
        write(util::string_fmt(str, args...));
    }

    template<typename... Args>
    void writelnf(const string& str, Args... args)
    {
        writeln(util::string_fmt(str, args...));
    }

    EventThread* p_commandBus;
    void setupSigio(EventThread& commandBus)
    {
        p_commandBus = &commandBus;

        serial.sigio(callback(this, &Console::__sigio));
    }

    void __sigio()
    {
        p_commandBus->push(callback(this, &Console::tryRead));
    }

    char buffer[32] = {0};
    char* p_buf = buffer;

    void tryRead()
    {
        if(!serial.readable())
            return;

        while(serial.readable()) {
            p_buf += serial.read(p_buf, sizeof(buffer) - (p_buf - buffer));

            // Ensure no overflow can happen
            if(sizeof(buffer) - (p_buf - buffer) <= 0) {
                memset(buffer, 0, sizeof(buffer));
                p_buf = buffer;

                writeln("RESET INPUT");

                return;
            }
        }

        if(buffer[strlen(buffer) - 1] == '\n') {
            writelnf("Read String: '%s'", buffer);

            // trigger commands
            p_commandBus->dispatch("console_input", (void*)buffer);

            memset(buffer, 0, sizeof(buffer));

            // reset
            p_buf = buffer;
        }
    }
};
