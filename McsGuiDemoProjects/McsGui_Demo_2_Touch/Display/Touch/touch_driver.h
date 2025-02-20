#ifndef TOUCH_TOUCH_DRIVER_H_
#define TOUCH_TOUCH_DRIVER_H_

#include <stdint.h>
#include <math.h>

typedef struct
{
	float_t gainX;
	float_t gainY;
	float_t offsetX;
	float_t offsetY;
} TouchCalibrationValues_s;

typedef struct
{
	uint16_t x;
	uint16_t y;
	uint16_t z;
} TouchADCValues_s;

void touch_dr_init(void);
void touch_dr_scan(void);
void touch_dr_resetCalibration(void);
void touch_dr_setCalibrationValues(const TouchCalibrationValues_s *p_values);
TouchCalibrationValues_s touch_dr_getCalibrationValues(void);
TouchADCValues_s touch_dr_getAdcValues(void);

#endif /* TOUCH_TOUCH_DRIVER_H_ */
