#pragma once

#include "config.h"

// Teams Macros
#ifndef DXC_TEAM
    #define DXC_TEAM 0
#endif

#if (DXC_TEAM == 0)
    #warning Compiling all teams into singular binary

    #define DXC_TEAM_1
    #define DXC_TEAM_2
    #define DXC_TEAM_3
#endif

#if (DXC_TEAM == 1)
    #define DXC_TEAM_1
#endif

#if (DXC_TEAM == 2)
    #define DXC_TEAM_2
#endif

#if (DXC_TEAM == 3)
    #define DXC_TEAM_3
#endif

// String helpers for macro string concatenation
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// Console Title
#define CONSOLE_TITLE "DXC-22-L Team " STR(DXC_TEAM) " (version: " VERSION_STR ")"
