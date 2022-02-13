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
