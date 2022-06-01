#pragma once

// Teams Macros (-D DXC_TEAM={1-3})
#ifndef DXC_TEAM
    #error Specify -D DXC_TEAM=(1-3) while compiling
#endif

#if (DXC_TEAM == 1)
    #define DXC_TEAM_1
#endif

#if (DXC_TEAM == 2)
    #define DXC_TEAM_2
#endif

// DXC Team 3 is the test robot
#if (DXC_TEAM == 3)
    #define DXC_TEAM_3
    #define TEST_ROBOT
#endif

// String helpers for macro string concatenation
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// Console Title
#define CONSOLE_TITLE "DXC-22-L Team " STR(DXC_TEAM) " (version: " STR(VERSION_STR) " / " STR(VERSION_COMMIT_SHA) ")"


#define THREAD [[noreturn]] void