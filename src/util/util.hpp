#pragma once

#include <string>
#include <mbed.h>

namespace util
{
    template<typename... Args>
    std::string string_fmt(const std::string &format, Args... args)
    {
        std::size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
        auto buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, format.c_str(), args...);

        return std::string(buf.get(), buf.get() + size - 1);
    }
}
