#include "gui_slider.h"

#include <stdio.h>

#include "gui_app.h"
#include "Core/gui_memory.h"
#include "Graphics/gui_graphics.h"

#define GUI_SLIDER_BUFFER_SIZE 4

#define GUI_SLIDER_WIDTH 160
#define GUI_SLIDER_HEIGHT 31
#define GUI_SLIDER_BAR_HEIGHT 8
#define GUI_SLIDER_BORDER_WIDTH 2
#define GUI_SLIDER_BORDER_TOTAL_WIDTH (GUI_SLIDER_BORDER_WIDTH * 2)
#define GUI_SLIDER_TEXT_WIDTH 60

#define GUI_SLIDER_BUTTON_WIDTH 32
#define GUI_SLIDER_BUTTON_HEIGHT 32

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticSliderMemInUse[GUI_SLIDER_BUFFER_SIZE];
static Slider_s staticSliderMem[GUI_SLIDER_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void slider_onDisplay(BaseComponent_s *p_baseComponent);
static void slider_displayBtn(Button_s *p_button);
static void slider_displayValue(Slider_s *p_slider);
static void slider_decreaseValue(Button_s *p_button);
static void slider_increaseValue(Button_s *p_button);
static void slider_displayBar(Slider_s *p_slider);
static void slider_buttonDelete(BaseComponent_s *p_buttonBase);
static void slider_buttonFocusChanged(BaseComponent_s *p_buttonBase);
static void slider_setMinusBtnPosition(Slider_s *p_slider);
static void slider_setPlusBtnPosition(Slider_s *p_slider);


Slider_s *slider_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(Slider_s));
#else
    for (uint32_t i = 0; i < GUI_SLIDER_BUFFER_SIZE; i++)
    {
        if (!staticSliderMemInUse[i])
        {
            staticSliderMemInUse[i] = true;

            return &staticSliderMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No Slider_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

Slider_s *slider_newInit(void)
{
    Slider_s *p_slider = slider_new();
    if (p_slider != NULL)
    {
        slider_init(p_slider);
    }

    return p_slider;
}

void slider_delete(BaseComponent_s *p_sliderBase)
{
    base_clear(p_sliderBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_sliderBase, sizeof(Slider_s));
#else
    for (uint32_t i = 0; i < GUI_SLIDER_BUFFER_SIZE; i++)
    {
        if (&staticSliderMem[i].base == p_sliderBase)
        {
            staticSliderMemInUse[i] = false;

            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void slider_init(Slider_s *p_slider)
{
    base_initParentComp(&p_slider->base, slider_delete);
    base_setOnDisplay(&p_slider->base, slider_onDisplay);
    base_setDimensions(&p_slider->base, GUI_SLIDER_WIDTH, GUI_SLIDER_HEIGHT);

    button_init(&p_slider->minusButton);
    button_init(&p_slider->plusButton);
    keynav_init(&p_slider->minusKeyNavigation);
    keynav_init(&p_slider->plusKeyNavigation);
    base_addKeyNavigation(&p_slider->minusButton.base, &p_slider->minusKeyNavigation);
    base_addKeyNavigation(&p_slider->plusButton.base, &p_slider->plusKeyNavigation);

    base_setBmpKey(&p_slider->minusButton, FILE_KEY_ICON_MINUS);
    base_setBmpKey(&p_slider->plusButton, FILE_KEY_ICON_PLUS);
    base_setDimensions(&p_slider->minusButton, GUI_SLIDER_BUTTON_WIDTH, GUI_SLIDER_BUTTON_HEIGHT);
    base_setDimensions(&p_slider->plusButton, GUI_SLIDER_BUTTON_WIDTH, GUI_SLIDER_BUTTON_HEIGHT);
    slider_setMinusBtnPosition(p_slider);
    slider_setPlusBtnPosition(p_slider);
    button_setOnFocusChanged(&p_slider->minusButton, slider_buttonFocusChanged);
    button_setOnFocusChanged(&p_slider->plusButton, slider_buttonFocusChanged);

    button_setOnReleased(&p_slider->minusButton, slider_decreaseValue);
    button_setOnReleased(&p_slider->plusButton, slider_increaseValue);
    theme_applyThemeProperty(&p_slider->minusButton);
    theme_applyThemeProperty(&p_slider->plusButton);

    base_setOnDelete(&p_slider->minusButton.base, slider_buttonDelete);
    base_setOnDelete(&p_slider->plusButton.base, slider_buttonDelete);
    base_addChild(&p_slider->base, &p_slider->minusButton.base);
    base_addChild(&p_slider->base, &p_slider->plusButton.base);

    keynav_connectLeftRight(&p_slider->minusButton, &p_slider->plusButton);

    p_slider->value = 0;
    p_slider->minValue = 0;
    p_slider->maxValue = 100;
    p_slider->step = 1;
    p_slider->active = false;
    p_slider->colorLeft = theme_getSliderColor();
    p_slider->colorRight = theme_getBackgroundColor();
}

void slider_setValue(Slider_s *p_slider, int16_t value)
{
    if (value < p_slider->minValue)
    {
        p_slider->value = p_slider->minValue;
    }
    else if (value > p_slider->maxValue)
    {
        p_slider->value = p_slider->maxValue;
    }
    else
    {
        p_slider->value = value;
    }
}

int16_t slider_getValue(Slider_s *slider)
{
    return slider->value;
}

void slider_setStep(Slider_s *slider, int8_t step)
{
    slider->step = step;
}

void slider_setLeftColor(Slider_s *slider, Color_t color)
{
    slider->colorLeft = color;
}

void slider_setRightColor(Slider_s *slider, Color_t color)
{
    slider->colorRight = color;
}

void slider_setOnValueChanged(Slider_s *slider, void (*onValueChanged)(Slider_s *slider))
{
    slider->onValueChanged = onValueChanged;
}

static void slider_buttonFocusChanged(BaseComponent_s *p_buttonBase)
{
    Button_s *p_button = (Button_s*)p_buttonBase;
    slider_displayBtn(p_button);
}

static void slider_onDisplay(BaseComponent_s *p_base)
{
    Slider_s *p_slider = (Slider_s*)p_base;

#if GUI_CONFIG_USE_ANCHOR
    if (p_slider->base.p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_base);
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    slider_displayBar(p_slider);
    slider_setMinusBtnPosition(p_slider);
    slider_setPlusBtnPosition(p_slider);

    slider_displayBtn(&p_slider->minusButton);
    slider_displayBtn(&p_slider->plusButton);
    slider_displayValue(p_slider);
}

static void slider_displayBar(Slider_s *p_slider)
{
    BaseComponent_s *p_base = &p_slider->base;
    const uint16_t yBar = p_base->y + (uint16_t)((GUI_SLIDER_HEIGHT - GUI_SLIDER_BAR_HEIGHT) / 2) + 1;
    const uint16_t fillWidth = p_slider->value * (p_base->width - 2) / p_slider->maxValue;

    Rectangle_s border;
    rectangle_initBorderPosSize(
        &border, p_base->x, yBar, p_base->width, GUI_SLIDER_BAR_HEIGHT, GUI_SLIDER_BORDER_WIDTH, theme_getSeparatorColor());
    base_display(&border);

    Rectangle_s barLeft;
    rectangle_initFillPosSize(
            &barLeft, p_slider->colorLeft,
            p_base->x + GUI_SLIDER_BORDER_WIDTH, yBar + GUI_SLIDER_BORDER_WIDTH,
            fillWidth, GUI_SLIDER_BAR_HEIGHT - GUI_SLIDER_BORDER_TOTAL_WIDTH);

    Rectangle_s barRight;
    rectangle_initFillPosSize(
            &barRight, p_slider->colorRight,
            p_base->x + GUI_SLIDER_BORDER_WIDTH + fillWidth, yBar + GUI_SLIDER_BORDER_WIDTH,
            p_base->width - GUI_SLIDER_BORDER_TOTAL_WIDTH - fillWidth, GUI_SLIDER_BAR_HEIGHT - GUI_SLIDER_BORDER_TOTAL_WIDTH);

    if (p_slider->value == p_slider->minValue)
    {
        base_display(&barRight);
    }
    else if (p_slider->value == p_slider->maxValue)
    {
        base_display(&barLeft);
    }
    else
    {
        base_display(&barLeft);
        base_display(&barRight);
    }
}

static void slider_setMinusBtnPosition(Slider_s *p_slider)
{
    const uint16_t x = p_slider->base.x - GUI_SLIDER_BUTTON_WIDTH - 8;
    const uint16_t y = p_slider->base.y + (p_slider->base.height - GUI_SLIDER_BUTTON_HEIGHT) / 2;

    base_setPosition(&p_slider->minusButton.base, x, y);
}

static void slider_setPlusBtnPosition(Slider_s *p_slider)
{
    const uint16_t x = p_slider->base.x + p_slider->base.width + 8;
    const uint16_t y = p_slider->base.y + (p_slider->base.height - GUI_SLIDER_BUTTON_HEIGHT) / 2;
    base_setPosition(&p_slider->plusButton.base, x, y);
}

static void slider_displayBtn(Button_s *p_button)
{
    const Color_t color = theme_getFocusItemColor(p_button->base.focused);
    base_setBackground(&p_button->base, color);

    const property_value_focus_e propertyValueFocus =
            (p_button->base.focused) ? PROPERTY_FOCUS_VALUE_TRUE : PROPERTY_FOCUS_VALUE_FALSE;
    base_setProperty(p_button, FILE_PROPERTY_FOCUS, propertyValueFocus);
    base_display(p_button);

    const Color_t borderColor = p_button->base.focused ? COLOR_ACCENT_RED : theme_getSeparatorColor();

    Rectangle_s border;
    rectangle_initBorderPosSize(
        &border, p_button->base.x, p_button->base.y, p_button->base.width,
        p_button->base.height, GUI_SLIDER_BORDER_WIDTH, borderColor);
    base_display(&border);
}

static void slider_displayValue(Slider_s *p_slider)
{
    const uint16_t x = p_slider->base.x + (p_slider->base.width - GUI_SLIDER_TEXT_WIDTH) / 2;

    TextBlock_s textBlock;
    textblock_init(&textBlock);
    textblock_setFont(&textBlock, theme_getDefaultFont());
    base_setPosition(&textBlock, x, (p_slider->base.y + GUI_SLIDER_BUTTON_HEIGHT));
    base_setWidth(&textBlock, GUI_SLIDER_TEXT_WIDTH);
    base_setBackground(&textBlock, theme_getBackgroundColor());
    base_setTransparent(&textBlock, false);
    snprintf(textBlock.text, TEXTBLOCK_MAX_STRING_LENGTH, "%d", p_slider->value);
    base_display(&textBlock);
}

static void slider_decreaseValue(Button_s *p_button)
{
    Slider_s *p_slider = (Slider_s*)p_button->base.p_parent;

    if (p_slider->value > p_slider->minValue)
    {
        p_slider->value -= p_slider->step;
        slider_displayBar(p_slider);
        slider_displayValue(p_slider);

        if (p_slider->onValueChanged)
        {
            p_slider->onValueChanged(p_slider);
        }
    }
}

static void slider_increaseValue(Button_s *p_button)
{
    Slider_s *p_slider = (Slider_s*)p_button->base.p_parent;

    if (p_slider->value < p_slider->maxValue)
    {
        p_slider->value += p_slider->step;
        slider_displayBar(p_slider);
        slider_displayValue(p_slider);

        if (p_slider->onValueChanged)
        {
            p_slider->onValueChanged(p_slider);
        }
    }
}

static void slider_buttonDelete(BaseComponent_s *p_buttonBase)
{
    // Dummy delete function. The buttons are deleted when the parent is deleted.
}
