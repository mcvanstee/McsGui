#ifndef CUSTOMCOMPONENTS_GUI_NUMBER_INPUT_H_
#define CUSTOMCOMPONENTS_GUI_NUMBER_INPUT_H_

#include "gui_theme.h"

typedef enum
{
	NumberInput_Orientation_Horizontal,
	NumberInput_Orientation_Vertical
} NumberInputOrientation_e;

typedef struct number_input_t
{
    BaseComponent_s base;
    Button_s increaseButton;
    Button_s decreaseButton;
    Touch_s increaseTouch;
    Touch_s decreaseTouch;
    NumberInputOrientation_e orientation;
    int32_t value;
    int32_t minValue;
    int32_t maxValue;
    void (*valueChanged)(struct number_input_t *p_numberInput);
} NumberInput_s;

NumberInput_s *num_input_new(void);
NumberInput_s *num_input_newInit(void);

void num_input_delete(BaseComponent_s *p_numberInputBase);
void num_input_init(NumberInput_s *p_numberInput);

void num_input_setValue(NumberInput_s *p_numberInput, int32_t value);
int32_t num_input_getValue(NumberInput_s *p_numberInput);
void num_input_setOnValueChanged(NumberInput_s *p_numberInput, void (*valueChanged)(NumberInput_s *p_numberInput));
void num_input_setOrientation(NumberInput_s *p_numberInput, NumberInputOrientation_e orientation);
void num_input_setMinimumValue(NumberInput_s *p_numberInput, int32_t minValue);
void num_input_setMaximumValue(NumberInput_s *p_numberInput, int32_t maxValue);
void num_input_setMinMaxValue(NumberInput_s *p_numberInput, int32_t minValue, int32_t maxValue);

#endif /* CUSTOMCOMPONENTS_GUI_NUMBER_INPUT_H_ */
