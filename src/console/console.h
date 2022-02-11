#pragma once

#include <mbed.h>
#include <string>

#include "helper/config.h"

class Console
{
public:
    Console();
    ~Console() = default;

    static Console& getInstance()
    {
        static Console instance;

        return instance;
    }

protected:
    BufferedSerial serial;

public:
    void write(const string& string);

    void writeln(const string& string);
};
