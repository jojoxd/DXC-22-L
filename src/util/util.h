#pragma once

#include <string>
#include <mbed.h>

namespace util
{
    template<typename... Args>
    std::string string_fmt(const std::string& format, Args... args);
}
