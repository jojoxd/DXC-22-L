#pragma once

#define CONSOLE_BAUDRATE 9600

// Niet veranderen, doet build systeem automatisch
#ifndef VERSION_STR
    #define VERSION_STR 0.0.0
#endif

#ifndef VERSION_COMMIT_SHA
    #define VERSION_COMMIT_SHA dev
#endif
