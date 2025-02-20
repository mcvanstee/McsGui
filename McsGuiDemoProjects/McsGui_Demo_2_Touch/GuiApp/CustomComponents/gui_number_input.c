#include "gui_number_input.h"

#include <stddef.h>
#include <stdio.h>

#include "gui_app.h"
#include "Graphics/gui_graphics.h"
#include "Utils/gui_log.h"
#include "Utils/gui_memory.h"

#define GUI_NUMBER_INPUT_BUTTON_WIDTH 30
#define GUI_NUMBER_INPUT_TEXT_WIDTH 50

#define GUI_NUMBER_INPUT_WIDTH (GUI_NUMBER_INPUT_BUTTON_WIDTH * 2) + GUI_NUMBER_INPUT_TEXT_WIDTH
#define GUI_NUMBER_INPUT_HEIGHT 30

#define GUI_NUMBER_INPUT_BUFFER_SIZE 4

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticNumberInputMemInUse[GUI_NUMBER_INPUT_BUFFER_SIZE];
static NumberInput_s staticNumberInputMem[GUI_NUMBER_INPUT_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void num_input_onDisplay(BaseComponent_s *p_base);
static void num_input_displayValue(NumberInput_s *p_numberInput);
static void num_input_increaseValue(Button_s *p_button);
static void num_input_decreaseValue(Button_s *p_button);
static void num_input_buttonDelete(BaseComponent_s *p_buttonBase);

NumberInput_s *num_input_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(NumberInput_s));
#else
    for (uint32_t i = 0; i < GUI_NUMBER_INPUT_BUFFER_SIZE; i++)
    {
        if (!staticNumberInputMemInUse[i])
        {
            staticNumberInputMemInUse[i] = true;

            return &staticNumberInputMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No NumberInput_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

NumberInput_s *num_input_newInit(void)
{
    NumberInput_s *p_numberInput = num_input_new();
    if (p_numberInput != NULL)
    {
        num_input_init(p_numberInput);
    }

    return p_numberInput;
}

void num_input_delete(BaseComponent_s *p_numberInputBase)
{
    base_clear(p_numberInputBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_numberInputBase, sizeof(NumberInput_s));
#else
    for (uint32_t i = 0; i < GUI_NUMBER_INPUT_BUFFER_SIZE; i++)
    {
        if (&staticNumberInputMem[i].base == p_numberInputBase)
        {
            staticNumberInputMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void num_input_init(NumberInput_s *p_numberInput)
{
    base_initParentComp(&p_numberInput->base, num_input_delete);
    base_setSize(&p_numberInput->base, GUI_NUMBER_INPUT_WIDTH, GUI_NUMBER_INPUT_HEIGHT);

    button_init(&p_numberInput->decreaseButton);
    button_init(&p_numberInput->increaseButton);
    touch_init(&p_numberInput->decreaseTouch);
    touch_init(&p_numberInput->increaseTouch);
    base_addTouch(&p_numberInput->decreaseButton.base, &p_numberInput->decreaseTouch);
    base_addTouch(&p_numberInput->increaseButton.base, &p_numberInput->increaseTouch);

    base_setBmpKey(&p_numberInput->decreaseButton, FILE_KEY_BUTTON_NUMINPUT_MINUS);
    base_setBmpKey(&p_numberInput->increaseButton, FILE_KEY_BUTTON_NUMINPUT_PLUS);
    base_setSize(&p_numberInput->decreaseButton, GUI_NUMBER_INPUT_BUTTON_WIDTH, GUI_NUMBER_INPUT_HEIGHT);
    base_setSize(&p_numberInput->increaseButton, GUI_NUMBER_INPUT_BUTTON_WIDTH, GUI_NUMBER_INPUT_HEIGHT);
    button_setOnReleased(&p_numberInput->decreaseButton, num_input_decreaseValue);
    button_setOnReleased(&p_numberInput->increaseButton, num_input_increaseValue);
    theme_setTheme(&p_numberInput->decreaseButton);
    theme_setTheme(&p_numberInput->increaseButton);
    base_setOnDelete(&p_numberInput->decreaseButton, num_input_buttonDelete);
    base_setOnDelete(&p_numberInput->increaseButton, num_input_buttonDelete);

    base_setOnDisplay(&p_numberInput->base, num_input_onDisplay);
    base_addChild(&p_numberInput->base, &p_numberInput->decreaseButton.base);
    base_addChild(&p_numberInput->base, &p_numberInput->increaseButton.base);

    p_numberInput->orientation = NumberInput_Orientation_Horizontal;
    p_numberInput->minValue = 0;
    p_numberInput->maxValue = 9;
    p_numberInput->value = 0;
    p_numberInput->valueChanged = NULL;
}

void num_input_setValue(NumberInput_s *p_numberInput, int32_t value)
{
    p_numberInput->value = value;
}

int32_t num_input_getValue(NumberInput_s *p_numberInput)
{
    return p_numberInput->value;
}

void num_input_setOnValueChanged(NumberInput_s *p_numberInput, void (*valueChanged)(NumberInput_s *p_numberInput))
{
    p_numberInput->valueChanged = valueChanged;
}

void num_input_setOrientation(NumberInput_s *p_numberInput, NumberInputOrientation_e orientation)
{
	p_numberInput->orientation = orientation;

	if (NumberInput_Orientation_Horizontal == orientation)
	{
		base_setSize(&p_numberInput->base, GUI_NUMBER_INPUT_WIDTH, GUI_NUMBER_INPUT_HEIGHT);
	}
	else
	{
		base_setSize(&p_numberInput->base, GUI_NUMBER_INPUT_HEIGHT, GUI_NUMBER_INPUT_WIDTH);
	}
}

void num_input_setMinimumValue(NumberInput_s *p_numberInput, int32_t minValue)
{
    p_numberInput->minValue = minValue;
}

void num_input_setMaximumValue(NumberInput_s *p_numberInput, int32_t maxValue)
{
    p_numberInput->maxValue = maxValue;
}

void num_input_setMinMaxValue(NumberInput_s *p_numberInput, int32_t minValue, int32_t maxValue)
{
    p_numberInput->minValue = minValue;
    p_numberInput->maxValue = maxValue;
}

static void num_input_increaseValue(Button_s *p_button)
{
    NumberInput_s *p_numberInput = (NumberInput_s*)p_button->base.p_parent;

    if (p_numberInput->value < p_numberInput->maxValue)
    {
        p_numberInput->value++;
        num_input_displayValue(p_numberInput);
    }
}

static void num_input_decreaseValue(Button_s *p_button)
{
    NumberInput_s *p_numberInput = (NumberInput_s*) p_button->base.p_parent;

    if (p_numberInput->value > p_numberInput->minValue)
    {
        p_numberInput->value--;
        num_input_displayValue(p_numberInput);
    }
}

static void num_input_displayValue(NumberInput_s *p_numberInput)
{
    TextBlock_s textBlock;
    textblock_init(&textBlock);
    textblock_setFont(&textBlock, theme_getDefaultFont());

    if (p_numberInput->orientation == NumberInput_Orientation_Horizontal)
    {
    	base_setPosition(&textBlock, p_numberInput->base.x + GUI_NUMBER_INPUT_BUTTON_WIDTH, p_numberInput->base.y);
		base_setSize(&textBlock, GUI_NUMBER_INPUT_TEXT_WIDTH, GUI_NUMBER_INPUT_HEIGHT);
	}
    else
	{
    	base_setPosition(&textBlock, p_numberInput->base.x, p_numberInput->base.y + GUI_NUMBER_INPUT_BUTTON_WIDTH);
		base_setSize(&textBlock, GUI_NUMBER_INPUT_HEIGHT, GUI_NUMBER_INPUT_TEXT_WIDTH);
	}

    base_setBackground(&textBlock, theme_getPaneColor());
    snprintf(textBlock.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%ld", p_numberInput->value);
    base_display(&textBlock);
}

static void num_input_onDisplay(BaseComponent_s *p_base)
{
    NumberInput_s *p_numberInput = (NumberInput_s*)p_base;

#if GUI_CONFIG_USE_ANCHOR
    if (p_numberInput->base.p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_base);
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

	if (p_numberInput->orientation == NumberInput_Orientation_Horizontal)
	{
		base_setPosition(&p_numberInput->decreaseButton, p_base->x, p_base->y);
		base_setPosition(&p_numberInput->increaseButton, p_base->x + p_base->width - GUI_NUMBER_INPUT_BUTTON_WIDTH, p_base->y);
	}
	else
	{
	    base_setPosition(&p_numberInput->increaseButton, p_base->x, p_base->y);
	    base_setPosition(&p_numberInput->decreaseButton, p_base->x, p_base->y + p_base->height - GUI_NUMBER_INPUT_BUTTON_WIDTH);
	}

    base_display(&p_numberInput->decreaseButton.base);
    base_display(&p_numberInput->increaseButton.base);
    num_input_displayValue(p_numberInput);
}

static void num_input_buttonDelete(BaseComponent_s *p_buttonBase)
{
    // Dummy delete function. The buttons are deleted when the parent is deleted.
}
