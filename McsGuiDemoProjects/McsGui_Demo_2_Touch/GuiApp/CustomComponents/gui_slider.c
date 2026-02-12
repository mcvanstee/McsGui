#include "gui_slider.h"

#include <stdio.h>

#include "gui_app.h"
#include "Core/gui_memory.h"
#include "Graphics/gui_graphics.h"

#define GUI_SLIDER_BUFFER_SIZE 4

#define GUI_SLIDER_WIDTH 160
#define GUI_SLIDER_HEIGHT 31
#define GUI_SLIDER_BAR_HEIGHT 5
#define GUI_SLIDER_KNOB_WIDTH 20
#define GUI_SLIDER_KNOB_HEIGHT (GUI_SLIDER_HEIGHT)
#define GUI_SLIDER_TEXT_WIDTH 60

#define GUI_SLIDER_BUTTON_WIDTH 32
#define GUI_SLIDER_BUTTON_HEIGHT 32

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticSliderMemInUse[GUI_SLIDER_BUFFER_SIZE];
static Slider_s staticSliderMem[GUI_SLIDER_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void slider_onDisplay(BaseComponent_s *p_baseComponent);
static void slider_displayMinusBtn(Slider_s *p_slider);
static void slider_displayPlusBtn(Slider_s *p_slider);
static void slider_displayValue(Slider_s *p_slider);
static void slider_displayKnob(Slider_s *p_slider);
static void slider_decreaseValue(Button_s *p_button);
static void slider_increaseValue(Button_s *p_button);
static void slider_buttonDelete(BaseComponent_s *p_buttonBase);


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
    touch_init(&p_slider->minusTouch);
    touch_init(&p_slider->plusTouch);
    base_addTouch(&p_slider->minusButton, &p_slider->minusTouch);
    base_addTouch(&p_slider->plusButton, &p_slider->plusTouch);

    base_setBmpKey(&p_slider->minusButton, FILE_KEY_ICON_PANE_MINUS);
    base_setBmpKey(&p_slider->plusButton, FILE_KEY_ICON_PANE_PLUS);
    base_setDimensions(&p_slider->minusButton, GUI_SLIDER_BUTTON_WIDTH, GUI_SLIDER_BUTTON_HEIGHT);
    base_setDimensions(&p_slider->plusButton, GUI_SLIDER_BUTTON_WIDTH, GUI_SLIDER_BUTTON_HEIGHT);

    button_setOnReleased(&p_slider->minusButton, slider_decreaseValue);
    button_setOnReleased(&p_slider->plusButton, slider_increaseValue);
    theme_applyThemeProperty(&p_slider->minusButton);
    theme_applyThemeProperty(&p_slider->plusButton);

    base_setOnDelete(&p_slider->minusButton.base, slider_buttonDelete);
    base_setOnDelete(&p_slider->plusButton.base, slider_buttonDelete);
    base_addChild(&p_slider->base, &p_slider->minusButton.base);
    base_addChild(&p_slider->base, &p_slider->plusButton.base);

    p_slider->value = 0;
    p_slider->minValue = 0;
    p_slider->maxValue = 100;
    p_slider->step = 1;
    p_slider->active = false;
    p_slider->colorLeft = theme_getSliderColor();
    p_slider->colorRight = theme_getSliderColor();
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

static void slider_onDisplay(BaseComponent_s *p_base)
{
    Slider_s *p_slider = (Slider_s*)p_base;

#if GUI_CONFIG_USE_ANCHOR
    if (p_slider->base.p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_base);
    }
#endif /* GUI_CONFIG_USE_ANCHOR */

    const uint16_t knobXLeft = p_slider->base.x + ((p_slider->base.width - GUI_SLIDER_KNOB_WIDTH) * p_slider->value) / p_slider->maxValue;
    const uint16_t knobXRight = p_slider->base.x + GUI_SLIDER_KNOB_WIDTH + ((p_slider->base.width - GUI_SLIDER_KNOB_WIDTH) * p_slider->value) / p_slider->maxValue;
    const uint16_t yBar = p_base->y + (uint16_t)((GUI_SLIDER_HEIGHT - GUI_SLIDER_BAR_HEIGHT) / 2) + 1;

    Rectangle_s barLeft;
    rectangle_initFillPosSize(
            &barLeft, p_slider->colorLeft,
            p_base->x, yBar,
            knobXLeft - p_base->x + 3, GUI_SLIDER_BAR_HEIGHT);

    Rectangle_s barRight;
    rectangle_initFillPosSize(
            &barRight, p_slider->colorRight,
            knobXRight - 1, yBar,
            p_base->x + p_base->width - knobXRight + 2, GUI_SLIDER_BAR_HEIGHT);

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

    slider_displayKnob(p_slider);
    slider_displayMinusBtn(p_slider);
    slider_displayPlusBtn(p_slider);
    slider_displayValue(p_slider);
}

static void slider_displayMinusBtn(Slider_s *p_slider)
{
	const uint16_t x = p_slider->base.x - GUI_SLIDER_BUTTON_WIDTH - 8;
	const uint16_t y = p_slider->base.y + (p_slider->base.height - GUI_SLIDER_BUTTON_HEIGHT) / 2;

	base_setPosition(&p_slider->minusButton.base, x, y);
	base_display(&p_slider->minusButton.base);
}

static void slider_displayPlusBtn(Slider_s *p_slider)
{
	const uint16_t x = p_slider->base.x + p_slider->base.width + 8;
	const uint16_t y = p_slider->base.y + (p_slider->base.height - GUI_SLIDER_BUTTON_HEIGHT) / 2;

	base_setPosition(&p_slider->plusButton.base, x, y);
	base_display(&p_slider->plusButton.base);
}

static void slider_displayValue(Slider_s *p_slider)
{
	const uint16_t x = p_slider->base.x + (p_slider->base.width - GUI_SLIDER_TEXT_WIDTH) / 2;

	TextBlock_s textBlock;
	textblock_init(&textBlock);
	textblock_setFont(&textBlock, theme_getDefaultFont());
	textblock_setFontBackColor(&textBlock, theme_getPaneColor());
	base_setTransparent(&textBlock, false);
	base_setPosition(&textBlock, x, (p_slider->base.y + GUI_SLIDER_BUTTON_HEIGHT + 8));
	base_setWidth(&textBlock, GUI_SLIDER_TEXT_WIDTH);
	snprintf(textBlock.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%d %s", p_slider->value, "%");
	base_display(&textBlock);
}

static void slider_displayKnob(Slider_s *p_slider)
{
    const uint16_t knobX = p_slider->base.x + ((p_slider->base.width - GUI_SLIDER_KNOB_WIDTH) * p_slider->value) / p_slider->maxValue;
    const uint16_t knobY = p_slider->base.y;

    Label_s label;
    label_init(&label);
    label_initBmpPos(&label, FILE_KEY_BUTTON_SLIDER, knobX, knobY);
    theme_applyThemeProperty(&label);
    base_display(&label);
}

static void slider_decreaseValue(Button_s *p_button)
{
	Slider_s *p_slider = (Slider_s*)p_button->base.p_parent;

    if (p_slider->value > p_slider->minValue)
    {
        const uint16_t knobX = p_slider->base.x + GUI_SLIDER_KNOB_WIDTH + (((p_slider->base.width - GUI_SLIDER_KNOB_WIDTH) * (p_slider->value -  p_slider->step)) / p_slider->maxValue);
        const uint16_t knobX1 = p_slider->base.x + GUI_SLIDER_KNOB_WIDTH + (((p_slider->base.width - GUI_SLIDER_KNOB_WIDTH) * p_slider->value) / p_slider->maxValue);
        const uint16_t knobY = p_slider->base.y;

        Rectangle_s rect;
        rectangle_initFillPosSize(
                &rect, theme_getPaneColor(),
                knobX + 2, knobY,
                knobX1 - knobX, GUI_SLIDER_KNOB_HEIGHT);
        base_display(&rect);

        p_slider->value -= p_slider->step;
        base_display(&p_slider->base);

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
        const uint16_t knobX = p_slider->base.x + (((p_slider->base.width - GUI_SLIDER_KNOB_WIDTH) * p_slider->value) / p_slider->maxValue);
        const uint16_t knobX1 = p_slider->base.x + (((p_slider->base.width - GUI_SLIDER_KNOB_WIDTH) * (p_slider->value + p_slider->step)) / p_slider->maxValue);
        const uint16_t knobY = p_slider->base.y;

        Rectangle_s rect;
        rectangle_initFillPosSize(
                &rect, theme_getPaneColor(),
                knobX, knobY,
                knobX1 - knobX, GUI_SLIDER_KNOB_HEIGHT);
        base_display(&rect);

        p_slider->value += p_slider->step;
        base_display(&p_slider->base);

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
