#ifndef GUIMODELS_GUI_MEASUREMENT_SETUP_H_
#define GUIMODELS_GUI_MEASUREMENT_SETUP_H_

#include <stdint.h>

typedef struct
{
    uint32_t sampleInterval_s;
    uint32_t upperLimit;
    uint32_t lowerLimit;
} GuiMeasurementSetup_s;


void measurement_setup_init(GuiMeasurementSetup_s *p_setup);
void measurement_setup_setToDefault(GuiMeasurementSetup_s *p_setup);

uint32_t measurement_setup_getSampleInterval(void);
uint32_t measurement_setup_getUpperLimit(void);
uint32_t measurement_setup_getLowerLimit(void);

void measurement_setup_setSampleInterval(const uint32_t interval_s);
void measurement_setup_setUpperLimit(const uint32_t upperLimit);
void measurement_setup_setLowerLimit(const uint32_t lowerLimit);

#endif /* GUIMODELS_GUI_MEASUREMENT_SETUP_H_ */
