#include "PaperThrower.h"

PaperThrower::PaperThrower()
    : m_console(Console::getInstance())
{
}

int PaperThrower::execute(int currentTick)
{
    raise(currentTick + 1);

    throwPaper(currentTick + 2);

    lower(currentTick + 3);

    ThisThread::sleep_for(2s);

    return currentTick + 3;
}

inline void PaperThrower::raise(int tick)
{
    #if defined(DATA_LOGGING)
        m_console.writeln("paper-thrower/raise");
        m_console.writelnf("tick=%d", tick);
    #endif

    #if defined(PAPERTHROWER_TRANSLATE)
        #if defined(PAPERTHROWER_TRANSLATE_WATERMARKS)
            // Should be optimized away
            int checkCondition = PAPERTHROWER_TRANSLATE_WATERMARKS_HIGH_PINMODE == PinMode::PullDown ? 0 : 1;

            do {
                m_translateMotor.setSpeed(PAPERTHROWER_TRANSLATE_UP_SPEED);
                ThisThread::sleep_for(1ms);
            } while(m_translateHighWatermark.read() == checkCondition);

            m_translateMotor.setSpeed(0.0f);

            // @HACK: Limit Switch broken, using ticks to define how long to go for
            int ticks = 0;

//            do {
//                ticks++;
//
//                m_translateMotor.setSpeed(-1.0f);
//                ThisThread::sleep_for(1ms);
//            } while(ticks < 5000);

            m_translateMotor.setSpeed(0.0f);
        #else
            // @TODO: Somehow signal that we're at the end, maybe using a timer or something?
        #endif
    #endif

    // Give some time to settle
    ThisThread::sleep_for(500ms);
}

inline void PaperThrower::throwPaper(int tick)
{
    #if defined(DATA_LOGGING)
        m_console.writeln("paper-thrower/throw");
        m_console.writelnf("tick=%d", tick);
    #endif

    #if defined(PAPERTHROWER_THROW)
        uint16_t ticks = 0;

        do {
            ticks++;

            m_throwMotor.setSpeed(1.0f);
            ThisThread::sleep_for(100ms);
        } while(ticks < PAPERTHROWER_THROW_TICKS);

        m_throwMotor.setSpeed(0.0f);
    #endif
}

inline void PaperThrower::lower(int tick)
{
    #if defined(DATA_LOGGING)
        m_console.writeln("paper-thrower/lower");
        m_console.writelnf("tick=%d", tick);
    #endif

    #if defined(PAPERTHROWER_TRANSLATE)
        #if defined(PAPERTHROWER_TRANSLATE_WATERMARKS)
            // Should be optimized away
            int checkCondition = PAPERTHROWER_TRANSLATE_WATERMARKS_LOW_PINMODE == PinMode::PullDown ? 0 : 1;

            do {
                m_translateMotor.setSpeed(PAPERTHROWER_TRANSLATE_DOWN_SPEED);
                ThisThread::sleep_for(1ms);
            } while(m_translateLowWatermark.read() == checkCondition);

            m_translateMotor.setSpeed(0.0f);
        #else
            // @TODO: Somehow signal that we're at the end, maybe using a timer or something?
        #endif
    #endif

    // Give some time to settle
    ThisThread::sleep_for(500ms);
}
