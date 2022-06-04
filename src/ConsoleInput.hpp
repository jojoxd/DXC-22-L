#pragma once

#include <mbed.h>

#include "helper/config.h"
#include "console.hpp"

/**
 * Handles Console Commands
 *
 * Currently supported:
 * - r<enter> - reset after 10 seconds (pause handlers are called before countdown)
 * - p<enter> - pauses/unpauses running state
 *
 * Note: Seld EOL = LF, and we want to send the whole message in 1 go instead of per letter
 */
class ConsoleInput
{
public:
    explicit ConsoleInput(Console& console)
        : m_console(console)
    {
    }

protected:
    bool m_paused = false;
    bool m_resetting = false;
    bool m_firstRun = true;

    Console& m_console;

    Callback<void()> m_pauseCallbacks[4] = {nullptr};
    Callback<void()> m_resumeCallbacks[4] = {nullptr};

public:
    void attachPauseCallback(Callback<void()> cb)
    {
        for(auto &onPauseCallback : m_pauseCallbacks) {
            if(onPauseCallback == nullptr) {
                onPauseCallback = cb;
            }
        }
    }

    void attachResumeCallback(Callback<void()> cb)
    {
        for(auto &onResumeCallback : m_resumeCallbacks) {
            if(onResumeCallback == nullptr) {
                onResumeCallback = cb;
            }
        }
    }

    void handleInput()
    {
        char str[8] = {0};

        if(m_resetting)
            return;

        if(m_console.read(str, 8) != -EAGAIN) {
            if(strcmp(str, "r\n") == 0) {
                runPauseCallbacks();
                m_resetting = true;

                for (int i = 10; i > 0; i--) {
                    m_console.writelnf("reset=%d", i);
                    ThisThread::sleep_for(1s);
                }

                system_reset();
            }

            if(strcmp(str, "p\n") == 0) {
                togglePause();
            }
        }
    }

    void togglePause()
    {
        if(m_paused) {
            m_paused = false;

            runResumeCallbacks();

            m_console.writelnf("pause=0");
        } else {
            m_paused = true;

            runPauseCallbacks();

            m_console.writelnf("pause=1");

            while(m_paused) {
                m_console.writelnf("pause=1");
                ThisThread::sleep_for(1000ms);

                handleInput();
            }
        }
    }

protected:
    void runPauseCallbacks()
    {
        for(auto &onPauseCallback : m_pauseCallbacks) {
            if(onPauseCallback != nullptr) {
                onPauseCallback();
            }
        }
    }

    void runResumeCallbacks()
    {
        for(auto &onResumeCallback : m_resumeCallbacks) {
            if(onResumeCallback != nullptr) {
                onResumeCallback();
            }
        }
    }
};
