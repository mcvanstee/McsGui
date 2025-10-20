#include "gui_spinner_input.h"

#include <stdio.h>

#include "gui_app.h"
#include "Graphics/gui_graphics.h"
#include "Core/gui_memory.h"

#define GUI_SPINNER_INPUT_BUFFER_SIZE 4

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticSpinnerInputMemInUse[GUI_SPINNER_INPUT_BUFFER_SIZE];
static SpinnerInput_s staticSpinnerInputMem[GUI_SPINNER_INPUT_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void spinner_input_onDisplay(BaseComponent_s *p_base);
static void spinner_input_focusChanged(BaseComponent_s *p_base);
static bool spinner_input_handleEvent(BaseComponent_s *p_spinnerInputBase, const GuiEvent_s *p_event);
static void spinner_input_editModeChanged(SpinnerInput_s *p_spinnerInput);
static void spinner_input_displayValue(SpinnerInput_s *p_spinnerInput);
static void spinner_input_displayUpValue(SpinnerInput_s *p_spinnerInput);
static void spinner_input_displayDownValue(SpinnerInput_s *p_spinnerInput);
static void spinner_input_initUpDownTextblock(TextBlock_s *p_textBlock, const GuiSize_s size);
static void spinner_input_decreaseValue(SpinnerInput_s *p_spinnerInput);
static void spinner_input_increaseValue(SpinnerInput_s *p_spinnerInput);
static void spinner_input_setText(SpinnerInput_s *p_spinnerInput);


SpinnerInput_s* spinner_input_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(SpinnerInput_s));
#else
    for (uint32_t i = 0; i < GUI_SPINNER_INPUT_BUFFER_SIZE; i++)
    {
        if (!staticSpinnerInputMemInUse[i])
        {
            staticSpinnerInputMemInUse[i] = true;

            return &staticSpinnerInputMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No SpinnerInput_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

SpinnerInput_s* spinner_input_newInit(void)
{
    SpinnerInput_s *p_spinnerInput = spinner_input_new();
    if (p_spinnerInput != NULL)
    {
        spinner_input_init(p_spinnerInput);
    }

    return p_spinnerInput;
}

void spinner_input_delete(BaseComponent_s *p_spinnerInputBase)
{
    base_clear(p_spinnerInputBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_spinnerInputBase, sizeof(SpinnerInput_s));
#else
    for (uint32_t i = 0; i < GUI_SPINNER_INPUT_BUFFER_SIZE; i++)
    {
        if (&staticSpinnerInputMem[i].valueTextBlock.base == p_spinnerInputBase)
        {
            staticSpinnerInputMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void spinner_input_init(SpinnerInput_s *p_spinnerInput)
{
    textblock_init(&p_spinnerInput->valueTextBlock);
    textblock_setFont(&p_spinnerInput->valueTextBlock, FONT_KEY_ROBOTO_36_B);
    textblock_setFontBackColor(&p_spinnerInput->valueTextBlock, theme_getPaneColor());
    base_setTransparent(&p_spinnerInput->valueTextBlock, false);
    base_setOnDelete(p_spinnerInput, spinner_input_delete);
    base_setOnDisplay(p_spinnerInput, spinner_input_onDisplay);
    base_setOnFocusChanged(p_spinnerInput, spinner_input_focusChanged);
    base_setOnHandleEvent(p_spinnerInput, spinner_input_handleEvent);

    keynav_init(&p_spinnerInput->keyNavigation);
    base_addKeyNavigation(p_spinnerInput, &p_spinnerInput->keyNavigation);

    p_spinnerInput->value = 0;
    p_spinnerInput->minValue = 0;
    p_spinnerInput->maxValue = 100;
    p_spinnerInput->editMode = false;
    p_spinnerInput->upTbSize.width = 0;
    p_spinnerInput->upTbSize.height = 0;
    p_spinnerInput->downTbSize.width = 0;
    p_spinnerInput->downTbSize.height = 0;
    p_spinnerInput->leadingZeros = 0;
}

void spinner_input_initValues(SpinnerInput_s *p_spinnerInput, int32_t value, int32_t minValue, int32_t maxValue)
{
    spinner_input_init(p_spinnerInput);
    p_spinnerInput->minValue = minValue;
    p_spinnerInput->maxValue = maxValue;
    spinner_input_setValue(p_spinnerInput, value);
}

void spinner_input_setValue(SpinnerInput_s *p_spinnerInput, int32_t value)
{
    if (value < p_spinnerInput->minValue)
    {
        p_spinnerInput->value = p_spinnerInput->minValue;
    }
    else if (value > p_spinnerInput->maxValue)
    {
        p_spinnerInput->value = p_spinnerInput->maxValue;
    }
    else
    {
        p_spinnerInput->value = value;
    }

    spinner_input_setText(p_spinnerInput);
}

int32_t spinner_input_getValue(SpinnerInput_s *p_spinnerInput)
{
    return p_spinnerInput->value;
}

void spinner_input_setMinValue(SpinnerInput_s *p_spinnerInput, int32_t minValue)
{
    p_spinnerInput->minValue = minValue;
}

void spinner_input_setMaxValue(SpinnerInput_s *p_spinnerInput, int32_t maxValue)
{
    p_spinnerInput->maxValue = maxValue;
}

void spinner_input_setLeadingZeros(SpinnerInput_s *p_spinnerInput, uint8_t leadingZeros)
{
    p_spinnerInput->leadingZeros = leadingZeros;
    spinner_input_setText(p_spinnerInput);
}

static void spinner_input_onDisplay(BaseComponent_s *p_base)
{
    spinner_input_displayValue((SpinnerInput_s *)p_base);
}

static void spinner_input_focusChanged(BaseComponent_s *p_base)
{
    spinner_input_displayValue((SpinnerInput_s *)p_base);
}

static bool spinner_input_handleEvent(BaseComponent_s *p_spinnerInputBase, const GuiEvent_s *p_event)
{
    bool eventHandled = false;
    SpinnerInput_s *p_spinnerInput = (SpinnerInput_s *)p_spinnerInputBase;

    if ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event))
    {
        p_spinnerInput->editMode = !p_spinnerInput->editMode;
        spinner_input_editModeChanged(p_spinnerInput);

        eventHandled = true;
    }

    if (!eventHandled && p_spinnerInput->editMode)
    {
        if (GUI_EVENT_KEY_UP_PRESS == p_event->event)
        {
            spinner_input_increaseValue(p_spinnerInput);
        }
        else if (GUI_EVENT_KEY_DOWN_PRESS == p_event->event)
        {
            spinner_input_decreaseValue(p_spinnerInput);
        }
        else
        {
        }

        eventHandled = true;
    }

    return eventHandled;
}

static void spinner_input_editModeChanged(SpinnerInput_s *p_spinnerInput)
{
    spinner_input_displayValue(p_spinnerInput);
}

static void spinner_input_displayValue(SpinnerInput_s *p_spinnerInput)
{
    const Color_t fontColor = p_spinnerInput->valueTextBlock.base.focused ? theme_getCursorColor() : theme_getPaneTextColor();

    textblock_setFontForeColor(&p_spinnerInput->valueTextBlock, fontColor);
    spinner_input_setText(p_spinnerInput);

    // Call graphics display directly to avoid recursive call to spinner_input_onDisplay
    //
    graphics_displayComponent(&p_spinnerInput->valueTextBlock.base);

    spinner_input_displayUpValue(p_spinnerInput);
    spinner_input_displayDownValue(p_spinnerInput);
}

static void spinner_input_displayUpValue(SpinnerInput_s *p_spinnerInput)
{
    TextBlock_s upValueTb;
    spinner_input_initUpDownTextblock(&upValueTb, p_spinnerInput->upTbSize);

    if (p_spinnerInput->editMode && (p_spinnerInput->value < p_spinnerInput->maxValue))
    {
        snprintf(upValueTb.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%ld", p_spinnerInput->value + 1);
    }

    GuiAnchor_s anchor;
    anchor_init(&anchor);
    base_addAnchor(&upValueTb, &anchor);
    anchor_setBottomAnchor(&upValueTb, p_spinnerInput, Gui_Anchor_Top);
    anchor_setHorizontalCenter(&upValueTb, p_spinnerInput);

    base_display(&upValueTb);
    p_spinnerInput->upTbSize = base_getSize(&upValueTb);
}

static void spinner_input_displayDownValue(SpinnerInput_s *p_spinnerInput)
{
    TextBlock_s downValueTb;
    spinner_input_initUpDownTextblock(&downValueTb, p_spinnerInput->downTbSize);

    if (p_spinnerInput->editMode && (p_spinnerInput->value > p_spinnerInput->minValue))
    {
        snprintf(downValueTb.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%ld", p_spinnerInput->value - 1);
    }

    GuiAnchor_s anchor;
    anchor_init(&anchor);
    base_addAnchor(&downValueTb, &anchor);
    anchor_setTopAnchor(&downValueTb, p_spinnerInput, Gui_Anchor_Bottom);
    anchor_setHorizontalCenter(&downValueTb, p_spinnerInput);

    base_display(&downValueTb);
    p_spinnerInput->downTbSize = base_getSize(&downValueTb);
}

static void spinner_input_initUpDownTextblock(TextBlock_s *p_textBlock, const GuiSize_s size)
{
    textblock_initTextSize(p_textBlock, "", size.width, size.height);
    textblock_setFontAndColor(p_textBlock, FONT_KEY_ROBOTO_22_R, theme_getPaneTextColor(), theme_getPaneColor());
    base_setTransparent(p_textBlock, false);
}

static void spinner_input_increaseValue(SpinnerInput_s *p_spinnerInput)
{
    if (p_spinnerInput->value < p_spinnerInput->maxValue)
    {
        spinner_input_setValue(p_spinnerInput, p_spinnerInput->value + 1);
        spinner_input_displayValue(p_spinnerInput);
    }
}

static void spinner_input_decreaseValue(SpinnerInput_s *p_spinnerInput)
{
    if (p_spinnerInput->value > p_spinnerInput->minValue)
    {
        spinner_input_setValue(p_spinnerInput, p_spinnerInput->value - 1);
        spinner_input_displayValue(p_spinnerInput);
    }
}

static void spinner_input_setText(SpinnerInput_s *p_spinnerInput)
{
    snprintf(p_spinnerInput->valueTextBlock.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%0*ld",
            p_spinnerInput->leadingZeros, p_spinnerInput->value);
}
