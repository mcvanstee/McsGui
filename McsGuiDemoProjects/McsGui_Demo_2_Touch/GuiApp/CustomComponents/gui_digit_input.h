#ifndef CUSTOMCOMPONENTS_GUI_DIGIT_INPUT_H_
#define CUSTOMCOMPONENTS_GUI_DIGIT_INPUT_H_

#include "gui_theme.h"

typedef struct digit_input_t
{
    BaseComponent_s base;
    Touch_s touch;
    uint8_t value;
    uint8_t minValue;
    uint8_t maxValue;
    bool editMode;
} DigitInput_s;

DigitInput_s *digit_input_new(void);
DigitInput_s *digit_input_newInit(void);

void digit_input_delete(BaseComponent_s *p_digitInputBase);
void digit_input_init(DigitInput_s *p_digitInput);

void digit_input_setValue(DigitInput_s *p_digitInput, uint8_t value);
uint8_t digit_input_getValue(DigitInput_s *p_digitInput);

void digit_input_setMinValue(DigitInput_s *p_digitInput, uint8_t minValue);
void digit_input_setMaxValue(DigitInput_s *p_digitInput, uint8_t maxValue);

#endif /* CUSTOMCOMPONENTS_GUI_DIGIT_INPUT_H_ */
