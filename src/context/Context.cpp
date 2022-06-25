#include "Context.h"

Context::Context()
{
    m_distanceSensor.setRanges(10.0f, 40.0f);

    m_consoleInput.setThrowCallback(callback(this, &Context::throwPaper));
}

void Context::tick()
{
    m_ticks++;

    #if defined(DATA_LOGGING)
        m_console.writelnf("tick=%d", m_ticks);
    #endif

    handleMagnet();

    m_consoleInput.handleInput();

    // @TODO: Read DRV5053 Sensor and run throwPaper() when it senses a magnetic field

    updateDrivingController();

    handleDistance();

    #if defined(DATA_LOGGING)
        m_console.ISR_handle();
    #endif
}

void Context::startup()
{
    #if defined(HV_ENABLE)
        m_hvEnable = 1;
    #endif

    #if defined(STARTUP_PAUSED)
        m_consoleInput.togglePause();
    #endif

    m_consoleInput.attachPauseCallback([&](){
        m_hvEnable = 0;
    });

    m_consoleInput.attachResumeCallback([&](){
        m_hvEnable = 1;
    });

    m_drivingController.start();
}

inline void Context::updateDrivingController()
{
    CNY70Array::Bias bias = m_sensorArray.getBias();
    m_drivingController.setBias(bias);

    #if defined(DATA_LOGGING)
        float leftSpeedPct = m_leftMotor.getSpeed(false) * 100.0f;
        float rightSpeedPct = m_rightMotor.getSpeed(false) * 100.0f;

        m_console.writelnf(
            "cny70/bias=%d, drctl/leftSpeed=%d%%, drctl/rightSpeed=%d%%",
            bias,
            (int) leftSpeedPct,
            (int) rightSpeedPct
        );
    #endif
}

inline void Context::handleDistance()
{
    if(m_distanceSensor.isNewDataReady()) {
        float distance = m_distanceSensor.getDistance();

        #if defined(DATA_LOGGING)
            m_console.writelnf("hc-sr04/distance=%dcm", (int) distance);
        #endif

        if(distance < HCSR04_STOP_LENGTH) {
            m_drivingController.stop();
        } else {
            m_drivingController.start();
        }
    }

    if(!m_distanceSensor.isRunning()) {
        #if defined(DATA_LOGGING)
            m_console.writeln("hc-sr04/start");
        #endif

        m_distanceSensor.startMeasurement();
    }
}

inline void Context::throwPaper()
{
    m_drivingController.stop();

    m_paperThrower.execute();

    m_drivingController.start();
}

inline void Context::handleMagnet()
{
    DRV5053::SensorResponse data = m_hallEffectSensor.getData();

    // If we have a magnetic field of 5 mT or more, throw
    if(data.mT > 5.0f) {
        throwPaper();
    }
}
