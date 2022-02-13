#include "console.h"

Console::Console()
    : serial(USBTX, USBRX, CONSOLE_BAUDRATE)
{
    serial.set_blocking(false);
}

void Console::write(const string& str)
{
    serial.write(str.c_str(), str.length());
}

void Console::writeln(const string &string)
{
    write(string + "\r\n");
}

template<typename... Args>
void Console::writef(const string &string, Args... args)
{
    write(util::string_fmt(string, args...));
}

template<typename... Args>
void Console::writelnf(const string &string, Args... args)
{
    writeln(util::string_fmt(string, args...));
}
