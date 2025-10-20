#include "gui_digit_input.h"

#include <stddef.h>
#include <stdio.h>

#include "gui_app.h"
#include "fs_font_search.h"
#include "Graphics/gui_graphics.h"
#include "Core/gui_memory.h"

#define GUI_DIGIT_INPUT_WIDTH 20
#define GUI_DIGIT_INPUT_HEIGHT 36

#define GUI_DIGIT_INPUT_BUFFER_SIZE 4

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticDigitInputMemInUse[GUI_DIGIT_INPUT_BUFFER_SIZE];
static DigitInput_s staticDigitInputMem[GUI_DIGIT_INPUT_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void digit_input_onDisplay(BaseComponent_s *p_base);
static void digit_input_displayFocusBorder(BaseComponent_s *p_base, bool focused);
static void digit_input_focusChanged(BaseComponent_s *p_base);
static bool digit_input_handleEvent(BaseComponent_s *p_digitInputBase, const GuiEvent_s *p_event);
static void digit_input_editModeChanged(DigitInput_s *p_digitInput);
static void digit_input_displayValue(DigitInput_s *p_digitInput);
static void digit_input_displayTopAndBottomValues(DigitInput_s *p_digitInput);
static void digit_input_increaseValue(DigitInput_s *p_digitInput);
static void digit_input_decreaseValue(DigitInput_s *p_digitInput);
static void digit_input_initArrowLabel(Label_s *p_label, const file_key_e bmpKey);
static void digit_input_setFont(TextBlock_s *p_textBlock);

DigitInput_s* digit_input_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(DigitInput_s));
#else
    for (uint32_t i = 0; i < GUI_DIGIT_INPUT_BUFFER_SIZE; i++)
    {
        if (!staticDigitInputMemInUse[i])
        {
            staticDigitInputMemInUse[i] = true;

            return &staticDigitInputMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No DigitInput_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

DigitInput_s* digit_input_newInit(void)
{
    DigitInput_s *p_digitInput = digit_input_new();
    if (p_digitInput != NULL)
    {
        digit_input_init(p_digitInput);
    }

    return p_digitInput;
}

void digit_input_delete(BaseComponent_s *p_digitInputBase)
{
    base_clear(p_digitInputBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_digitInputBase, sizeof(DigitInput_s));
#else
    for (uint32_t i = 0; i < GUI_DIGIT_INPUT_BUFFER_SIZE; i++)
    {
        if (&staticDigitInputMem[i].base == p_digitInputBase)
        {
            staticDigitInputMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void digit_input_init(DigitInput_s *p_digitInput)
{
    base_initParentComp(&p_digitInput->base, digit_input_delete);
    base_setOnDisplay(&p_digitInput->base, digit_input_onDisplay);
    base_setOnFocusChanged(&p_digitInput->base, digit_input_focusChanged);
    base_setOnHandleEvent(&p_digitInput->base, digit_input_handleEvent);
    base_setDimensions(&p_digitInput->base, GUI_DIGIT_INPUT_WIDTH, GUI_DIGIT_INPUT_HEIGHT);

    keynav_init(&p_digitInput->keyNavigation);
    base_addKeyNavigation(p_digitInput, &p_digitInput->keyNavigation);

    p_digitInput->value = 0;
    p_digitInput->minValue = 0;
    p_digitInput->maxValue = 9;
    p_digitInput->editMode = false;
}

void digit_input_setValue(DigitInput_s *p_digitInput, uint8_t value)
{
    p_digitInput->value = value;
}

uint8_t digit_input_getValue(DigitInput_s *p_digitInput)
{
    return p_digitInput->value;
}

void digit_input_setMinValue(DigitInput_s *p_digitInput, uint8_t minValue)
{
    p_digitInput->minValue = minValue;
}

void digit_input_setMaxValue(DigitInput_s *p_digitInput, uint8_t maxValue)
{
    p_digitInput->maxValue = maxValue;
}

static void digit_input_onDisplay(BaseComponent_s *p_base)
{
    DigitInput_s *p_digitInput = (DigitInput_s *)p_base;

#if GUI_CONFIG_USE_ANCHOR
    if (p_digitInput->base.p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_base);
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    Rectangle_s background;
    rectangle_initFillPosSize(
            &background, theme_getPaneColor(),
            p_base->x, p_base->y,
            p_base->width, p_base->height);
    rectangle_setRadius(&background, 3);
    base_display(&background);

    digit_input_focusChanged(p_base);
    digit_input_displayValue(p_digitInput);
}

static void digit_input_focusChanged(BaseComponent_s *p_base)
{
    digit_input_displayFocusBorder(p_base, p_base->focused);
}

static void digit_input_displayFocusBorder(BaseComponent_s *p_base, bool focused)
{
    const Color_t borderColor = focused ? theme_getCursorColor() : theme_getSeparatorColor();

    Rectangle_s border;
    rectangle_initBorderPosSize(
            &border,
            p_base->x, p_base->y,
            p_base->width, p_base->height,
            1, borderColor);
    rectangle_setRadius(&border, 3);
    base_display(&border);
}

static bool digit_input_handleEvent(BaseComponent_s *p_digitInputBase, const GuiEvent_s *p_event)
{
    bool eventHandled = false;
    DigitInput_s *p_digitInput = (DigitInput_s *)p_digitInputBase;

    if ((GUI_EVENT_KEY_ENTER_PRESS == p_event->event))
    {
        p_digitInput->editMode = !p_digitInput->editMode;
        digit_input_editModeChanged(p_digitInput);

        eventHandled = true;
    }

    if (!eventHandled && p_digitInput->editMode)
    {
        if (GUI_EVENT_KEY_UP_PRESS == p_event->event)
        {
            digit_input_increaseValue(p_digitInput);
        }
        else if (GUI_EVENT_KEY_DOWN_PRESS == p_event->event)
        {
            digit_input_decreaseValue(p_digitInput);
        }
        else
        {
        }

        eventHandled = true;
    }

    return eventHandled;
}

static void digit_input_editModeChanged(DigitInput_s *p_digitInput)
{
    if (p_digitInput->editMode)
    {
        Label_s arrowUp;
        digit_input_initArrowLabel(&arrowUp, FILE_KEY_ICON_ARROW_UP);

        GuiAnchor_s upAnchor;
        anchor_init(&upAnchor);
        base_addAnchor(&arrowUp, &upAnchor);
        anchor_setTopAnchor(&arrowUp, p_digitInput, Gui_Anchor_Top);
        anchor_setTopMargin(&arrowUp, 2);
        anchor_setHorizontalCenter(&arrowUp, p_digitInput);

        Label_s arrowDown;
        digit_input_initArrowLabel(&arrowDown, FILE_KEY_ICON_ARROW_DOWN);

        GuiAnchor_s downAnchor;
        anchor_init(&downAnchor);
        base_addAnchor(&arrowDown, &downAnchor);
        anchor_setBottomAnchor(&arrowDown, p_digitInput, Gui_Anchor_Bottom);
        anchor_setBottomMargin(&arrowDown, 2);
        anchor_setHorizontalCenter(&arrowDown, p_digitInput);

        digit_input_displayFocusBorder(&p_digitInput->base, false);

        base_display(&arrowUp);
        base_display(&arrowDown);
    }
    else
    {
        Rectangle_s eraseUp;
        rectangle_initFillSize(&eraseUp, theme_getPaneColor(), 12, 4);

        GuiAnchor_s anchor;
        anchor_init(&anchor);
        base_addAnchor(&eraseUp, &anchor);
        anchor_setTopAnchor(&eraseUp, p_digitInput, Gui_Anchor_Top);
        anchor_setTopMargin(&eraseUp, 2);
        anchor_setHorizontalCenter(&eraseUp, p_digitInput);

        Rectangle_s eraseDown;
        rectangle_initFillSize(&eraseDown, theme_getPaneColor(), 13, 4);

        GuiAnchor_s anchorDown;
        anchor_init(&anchorDown);
        base_addAnchor(&eraseDown, &anchorDown);
        anchor_setBottomAnchor(&eraseDown, p_digitInput, Gui_Anchor_Bottom);
        anchor_setBottomMargin(&eraseDown, 2);
        anchor_setHorizontalCenter(&eraseDown, p_digitInput);

        digit_input_displayFocusBorder(&p_digitInput->base, true);

        base_display(&eraseUp);
        base_display(&eraseDown);
    }

    digit_input_displayTopAndBottomValues(p_digitInput);
}

static void digit_input_displayValue(DigitInput_s *p_digitInput)
{
    BaseComponent_s *p_base = &p_digitInput->base;

    TextBlock_s textBlock;
    textblock_init(&textBlock);
    digit_input_setFont(&textBlock);
    base_setPosition(&textBlock, p_base->x, p_base->y);
    base_setDimensions(&textBlock, p_base->width, p_base->height);
    base_setTopPadding(&textBlock, 1);
    base_setLeftPadding(&textBlock, 1);
    snprintf(textBlock.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%u", p_digitInput->value);
    base_display(&textBlock);

    digit_input_displayTopAndBottomValues(p_digitInput);
}

static void digit_input_displayTopAndBottomValues(DigitInput_s *p_digitInput)
{
    TextBlock_s valueUpTb;
    textblock_init(&valueUpTb);
    digit_input_setFont(&valueUpTb);

    GuiAnchor_s upAnchor;
    anchor_init(&upAnchor);
    base_addAnchor(&valueUpTb, &upAnchor);
    anchor_setBottomAnchor(&valueUpTb, p_digitInput, Gui_Anchor_Top);
    anchor_setHorizontalCenter(&valueUpTb, p_digitInput);

    if (p_digitInput->editMode && (p_digitInput->value < p_digitInput->maxValue))
    {
        snprintf(valueUpTb.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%u", p_digitInput->value + 1);
    }
    else
    {
        textblock_setText(&valueUpTb, "  ");
    }

    TextBlock_s valueDownTb;
    textblock_init(&valueDownTb);
    digit_input_setFont(&valueDownTb);

    GuiAnchor_s downAnchor;
    anchor_init(&downAnchor);
    base_addAnchor(&valueDownTb, &downAnchor);
    anchor_setTopMargin(&valueDownTb, 1);
    anchor_setTopAnchor(&valueDownTb, p_digitInput, Gui_Anchor_Bottom);
    anchor_setHorizontalCenter(&valueDownTb, p_digitInput);

    if (p_digitInput->editMode && (p_digitInput->value > p_digitInput->minValue))
    {
        snprintf(valueDownTb.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%u", p_digitInput->value - 1);
    }
    else
    {
        textblock_setText(&valueDownTb, "  ");
    }

    base_display(&valueUpTb);
    base_display(&valueDownTb);
}

static void digit_input_increaseValue(DigitInput_s *p_digitInput)
{
    if (p_digitInput->value < p_digitInput->maxValue)
    {
        p_digitInput->value++;
        digit_input_displayValue(p_digitInput);
    }
}

static void digit_input_decreaseValue(DigitInput_s *p_digitInput)
{
    if (p_digitInput->value > p_digitInput->minValue)
    {
        p_digitInput->value--;
        digit_input_displayValue(p_digitInput);
    }
}

static void digit_input_initArrowLabel(Label_s *p_label, const file_key_e bmpKey)
{
    label_init(p_label);
    base_setBmpKey(p_label, bmpKey);
    base_setBackground(p_label, theme_getPaneColor());
    base_setForeColor(p_label, theme_getAccentColor());
    base_setTransparent(p_label, false);
}

static void digit_input_setFont(TextBlock_s *p_textBlock)
{
    textblock_setFont(p_textBlock, theme_getDefaultFont());
    textblock_setFontBackColor(p_textBlock, theme_getPaneColor());
    textblock_setFontForeColor(p_textBlock, theme_getPaneTextColor());
}
