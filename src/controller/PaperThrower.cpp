#include "PaperThrower.h"

PaperThrower::PaperThrower()
    : m_console(Console::getInstance())
{
}

void PaperThrower::execute()
{
    raise();

    throwPaper();

    lower();

    ThisThread::sleep_for(2s);
}

inline void PaperThrower::raise()
{
    m_console.writeln("paper-thrower/raise");

    #if defined(PAPERTHROWER_TRANSLATE)
        #if defined(PAPERTHROWER_TRANSLATE_WATERMARKS)
            do {
                m_translateMotor.setSpeed(1.0f);
                ThisThread::sleep_for(1ms);
            } while(m_translateHighWatermark.read() == 0);

            m_translateMotor.setSpeed(0.0f);
        #else
            // @TODO: Somehow signal that we're at the end, maybe using a timer or something?
        #endif
    #endif

    // Give some time to settle
    ThisThread::sleep_for(500ms);
}

inline void PaperThrower::throwPaper()
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

inline void PaperThrower::lower()
{
    m_console.writeln("paper-thrower/lower");

    #if defined(PAPERTHROWER_TRANSLATE)
        #if defined(PAPERTHROWER_TRANSLATE_WATERMARKS)
            do {
                m_translateMotor.setSpeed(-1.0f);
                ThisThread::sleep_for(1ms);
            } while(m_translateLowWatermark.read() == 0);

            m_translateMotor.setSpeed(0.0f);
        #else
            // @TODO: Somehow signal that we're at the end, maybe using a timer or something?
        #endif
    #endif

    // Give some time to settle
    ThisThread::sleep_for(500ms);
}
