#include "ConsoleInput.h"

void ConsoleInput::handleInput()
{
    char str[8] = {0};

    if(m_isResetting)
        return;

    if(m_console.read(str, 8) != -EAGAIN) {
        if(strcmp(str, "r\n") == 0) {
            runPauseCallbacks();
            m_isResetting = true;

            for (int i = 10; i > 0; i--) {
                m_console.writelnf("reset=%d", i);
                ThisThread::sleep_for(1s);
            }

            system_reset();
        }

        if(strcmp(str, "p\n") == 0) {
            togglePause();
        }

        if(strcmp(str, "t\n") == 0) {
            runThrowCallback();
        }
    }
}

void ConsoleInput::togglePause()
{
    if(m_isPaused) {
        m_isPaused = false;

        runResumeCallbacks();

        m_console.writelnf("pause=0");
    } else {
        m_isPaused = true;

        runPauseCallbacks();

        m_console.writelnf("pause=1");

        while(m_isPaused) {
            m_console.writelnf("pause=1");
            ThisThread::sleep_for(1000ms);

            handleInput();
        }
    }
}

void ConsoleInput::attachPauseCallback(Callback<void()> cb)
{
    for(auto &onPauseCallback : m_pauseCallbacks) {
        if(onPauseCallback == nullptr) {
            onPauseCallback = cb;
        }
    }
}

void ConsoleInput::runPauseCallbacks()
{
    for(auto &onPauseCallback : m_pauseCallbacks) {
        if(onPauseCallback != nullptr) {
            onPauseCallback();
        }
    }
}

void ConsoleInput::attachResumeCallback(Callback<void()> cb)
{
    for(auto &onResumeCallback : m_resumeCallbacks) {
        if(onResumeCallback == nullptr) {
            onResumeCallback = cb;
        }
    }
}

void ConsoleInput::runResumeCallbacks()
{
    for(auto &onResumeCallback : m_resumeCallbacks) {
        if(onResumeCallback != nullptr) {
            onResumeCallback();
        }
    }
}

void ConsoleInput::setThrowCallback(Callback<void()> cb)
{
    m_throwCallback = cb;
}

void ConsoleInput::runThrowCallback()
{
    if(m_throwCallback != nullptr) {
        m_throwCallback();
    }
}
