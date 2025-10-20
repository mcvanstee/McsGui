#ifndef CUSTOMCOMPONENTS_GUI_SPINNER_INPUT_H_
#define CUSTOMCOMPONENTS_GUI_SPINNER_INPUT_H_

#include "gui_theme.h"

typedef struct spinner_input_t
{
    TextBlock_s valueTextBlock;
    KeyNavigation_s keyNavigation;
    int32_t value;
    int32_t minValue;
    int32_t maxValue;
    bool editMode;
    GuiSize_s upTbSize;
    GuiSize_s downTbSize;
    uint8_t leadingZeros;
} SpinnerInput_s;

SpinnerInput_s *spinner_input_new(void);
SpinnerInput_s *spinner_input_newInit(void);

void spinner_input_delete(BaseComponent_s *p_spinnerInputBase);
void spinner_input_init(SpinnerInput_s *p_spinnerInput);
void spinner_input_initValues(SpinnerInput_s *p_spinnerInput, int32_t value, int32_t minValue, int32_t maxValue);

void spinner_input_setValue(SpinnerInput_s *p_spinnerInput, int32_t value);
int32_t spinner_input_getValue(SpinnerInput_s *p_spinnerInput);

void spinner_input_setMinValue(SpinnerInput_s *p_spinnerInput, int32_t minValue);
void spinner_input_setMaxValue(SpinnerInput_s *p_spinnerInput, int32_t maxValue);

void spinner_input_setLeadingZeros(SpinnerInput_s *p_spinnerInput, uint8_t leadingZeros);

#endif /* CUSTOMCOMPONENTS_GUI_SPINNER_INPUT_H_ */
