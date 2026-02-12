#include "gui_measurement_setup.h"

static GuiMeasurementSetup_s *m_p_measurementSetup;


void measurement_setup_init(GuiMeasurementSetup_s *p_setup)
{
    m_p_measurementSetup = p_setup;
}

void measurement_setup_setToDefault(GuiMeasurementSetup_s *p_setup)
{
    p_setup->sampleInterval_s = 1;
    p_setup->upperLimit = 23;
    p_setup->lowerLimit = 17;
}

uint32_t measurement_setup_getSampleInterval(void)
{
    return m_p_measurementSetup->sampleInterval_s;
}

uint32_t measurement_setup_getUpperLimit(void)
{
    return m_p_measurementSetup->upperLimit;
}

uint32_t measurement_setup_getLowerLimit(void)
{
    return m_p_measurementSetup->lowerLimit;
}

void measurement_setup_setSampleInterval(const uint32_t interval_s)
{
    m_p_measurementSetup->sampleInterval_s = interval_s;
}

void measurement_setup_setUpperLimit(const uint32_t upperLimit)
{
    m_p_measurementSetup->upperLimit = upperLimit;
}

void measurement_setup_setLowerLimit(const uint32_t lowerLimit)
{
    m_p_measurementSetup->lowerLimit = lowerLimit;
}
