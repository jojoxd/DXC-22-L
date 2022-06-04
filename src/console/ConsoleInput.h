#pragma once

#include <mbed.h>

#include "helper/config.h"
#include "console/Console.hpp"

/**
 * Handles Console Commands
 *
 * Currently supported:
 * - r<enter> - reset after 10 seconds (pause handlers are called before countdown)
 * - p<enter> - pauses/unpauses running state
 * - t<enter> - runs the PaperThrower
 *
 * Note: Seld EOL = LF, and we want to send the whole message in 1 go instead of per letter
 */
class ConsoleInput
{
public:
    explicit ConsoleInput() = default;
    ~ConsoleInput() = default;

public:
    void attachPauseCallback(Callback<void()> cb);

    void attachResumeCallback(Callback<void()> cb);

    void setThrowCallback(Callback<void()> cb);

    void handleInput();

    void togglePause();

protected:
    Console& m_console = Console::getInstance();

    bool m_isPaused = false;
    bool m_isResetting = false;

    Callback<void()> m_pauseCallbacks[4] = {nullptr};
    Callback<void()> m_resumeCallbacks[4] = {nullptr};
    Callback<void()> m_throwCallback = nullptr;

protected:
    void runPauseCallbacks();

    void runResumeCallbacks();

    void runThrowCallback();
};
