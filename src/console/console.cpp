#include "console.h"

Console::Console()
    : serial(USBTX, USBRX, CONSOLE_BAUDRATE)
{
}

void Console::write(const string& str)
{
    serial.write(str.c_str(), str.length());
}

void Console::writeln(const string &string)
{
    write(string + "\r\n");
}
