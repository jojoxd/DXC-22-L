#pragma once

#include <mbed.h>

#include "helper/macros.h"
#include "console.hpp"
#include "driver/MotorDriver.h"

class PaperThrower
{
public:
    explicit PaperThrower()
        : m_console(Console::getInstance())
    {
    }

    ~PaperThrower() = default;

public:
    void execute()
    {
        raise();

        throwPaper();

        lower();

        ThisThread::sleep_for(2s);
    }

protected:
    Console& m_console;

    #if defined(PAPERTHROWER_TRANSLATE)
        MotorDriver m_translateMotor = {
            PAPERTHROWER_TRANSLATE_PWM,
            PAPERTHROWER_TRANSLATE_DIR,
            PAPERTHROWER_TRANSLATE_MUL
        };

        #if defined(PAPERTHROWER_TRANSLATE_WATERMARKS)
            DigitalIn m_translateHighWater = {
                PAPERTHROWER_TRANSLATE_WATERMARKS_HIGH,
                PinMode::PullDown
            };

            DigitalIn m_translateLowWater = {
                PAPERTHROWER_TRANSLATE_WATERMARKS_LOW,
                PinMode::PullDown
            };
        #endif
    #endif

    #if defined(PAPERTHROWER_THROW)
        MotorDriver m_throwMotor = {
            PAPERTHROWER_THROW_PWM,
            PAPERTHROWER_THROW_DIR,
            PAPERTHROWER_THROW_MUL
        };
    #endif

protected:
    inline void raise()
    {
        m_console.writeln("paper-thrower/raise");

        #if defined(PAPERTHROWER_TRANSLATE)
            #if defined(PAPERTHROWER_TRANSLATE_WATERMARKS)
                do {
                    m_translateMotor.setSpeed(1.0f);
                    ThisThread::sleep_for(1ms);
                } while(m_translateHighWater.read() == 0);

                m_translateMotor.setSpeed(0.0f);
            #else
                // @TODO: Somehow signal that we're at the end, maybe using a timer or something?
            #endif
        #endif

        // Give some time to settle
        ThisThread::sleep_for(500ms);
    }

    inline void throwPaper()
    {
        #if defined(PAPERTHROWER_THROW)
            m_console.writeln("paper-thrower/throw");

            uint16_t ticks = 0;

            do {
                ticks++;

                m_throwMotor.setSpeed(1.0f);
                ThisThread::sleep_for(100ms);
            } while(ticks < PAPERTHROWER_THROW_TICKS);

            m_throwMotor.setSpeed(0.0f);
        #endif
    }

    inline void lower()
    {
        m_console.writeln("paper-thrower/lower");

        #if defined(PAPERTHROWER_TRANSLATE)
            #if defined(PAPERTHROWER_TRANSLATE_WATERMARKS)
                do {
                    m_translateMotor.setSpeed(-1.0f);
                    ThisThread::sleep_for(1ms);
                } while(m_translateLowWater.read() == 0);

                m_translateMotor.setSpeed(0.0f);
            #else
                // @TODO: Somehow signal that we're at the end, maybe using a timer or something?
            #endif
        #endif

        // Give some time to settle
        ThisThread::sleep_for(500ms);
    }
};
