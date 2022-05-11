#pragma once

#include <mbed.h>
#include <string>

namespace util
{
    template<typename... Args>
    std::string string_fmt(const std::string& format, Args... args)
    {
        std::size_t size = std::snprintf(nullptr, 0, format.c_str(), args...) + 1;
        auto buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, format.c_str(), args...);

        return std::string(buf.get(), buf.get() + size - 1);
    }

    template<typename T, size_t t_size = 5, typename V = T>
    struct MovingAverage
    {
    public:
        V next(T sample)
        {
            //Subtract the oldest number from the prev sum, add the new number
            m_sum = m_sum - m_items[m_pos] + sample;
            //Assign the nextNum to the position in the array
            m_items[m_pos] = sample;

            // Update next pos
            m_pos = (m_pos + 1) % t_size;

            //return the average
            return (V) (m_sum / t_size);
        }

    protected:
        T m_items[t_size];
        T m_sum = 0;
        int m_pos = 0;
    };

    namespace math
    {
        template <typename T>
        T clamp(T val, T low , T high)
        {
            return std::min(std::max(val, low), high);
        }
    }
}
