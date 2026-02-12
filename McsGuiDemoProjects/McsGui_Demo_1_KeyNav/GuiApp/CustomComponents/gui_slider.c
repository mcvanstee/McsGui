#include "gui_slider.h"

#include "gui_app.h"
#include "Core/gui_memory.h"
#include "Graphics/gui_graphics.h"

#define GUI_SLIDER_BUFFER_SIZE 4

#define GUI_SLIDER_WIDTH 160
#define GUI_SLIDER_HEIGHT 31
#define GUI_SLIDER_BAR_HEIGHT 5
#define GUI_SLIDER_KNOB_WIDTH 20
#define GUI_SLIDER_KNOB_HEIGHT (GUI_SLIDER_HEIGHT)

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticSliderMemInUse[GUI_SLIDER_BUFFER_SIZE];
static Slider_s staticSliderMem[GUI_SLIDER_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void slider_onDisplay(BaseComponent_s *p_baseComponent);
static void slider_focusChanged(BaseComponent_s *p_base);
static void slider_displayKnob(Slider_s *p_slider);
static bool slider_handleEvent(BaseComponent_s *p_sliderBase, const GuiEvent_s *p_event);

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
    slider_init(p_slider);

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
    base_setOnFocusChanged(&p_slider->base, slider_focusChanged);
    base_setOnHandleEvent(&p_slider->base, slider_handleEvent);
    base_setDimensions(&p_slider->base, GUI_SLIDER_WIDTH, GUI_SLIDER_HEIGHT);

    keynav_init(&p_slider->keyNavigation);
    base_addKeyNavigation(&p_slider->base, &p_slider->keyNavigation);

    p_slider->value = 0;
    p_slider->minValue = 0;
    p_slider->maxValue = 100;
    p_slider->step = 1;
    p_slider->active = false;
    p_slider->colorLeft = theme_getSliderColor();
    p_slider->colorRight = theme_getSliderColor();
    p_slider->onValueChanged = NULL;
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
    const Color_t borderColor = p_base->focused ? theme_getCursorColor() : theme_getButtonBorderColor();

    Rectangle_s barLeft;
    rectangle_initFillBorderPosSize(
            &barLeft, p_slider->colorLeft,
            p_base->x, yBar,
            knobXLeft - p_base->x + 3, GUI_SLIDER_BAR_HEIGHT,
            1, borderColor);

    Rectangle_s barRight;
    rectangle_initFillBorderPosSize(
            &barRight, p_slider->colorRight,
            knobXRight - 1, yBar,
            p_base->x + p_base->width - knobXRight + 2, GUI_SLIDER_BAR_HEIGHT,
            1, borderColor);

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

static void slider_focusChanged(BaseComponent_s *p_base)
{
    slider_onDisplay(p_base);
}

static bool slider_handleEvent(BaseComponent_s *p_sliderBase, const GuiEvent_s *p_event)
{
    bool eventHandled = true;

    Slider_s *p_slider = (Slider_s*)p_sliderBase;

    if (p_event->event == GUI_EVENT_KEY_LEFT_PRESS)
    {
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
            base_display(p_sliderBase);

            if (p_slider->onValueChanged)
            {
                p_slider->onValueChanged(p_slider);
            }
        }
    }
    else if (p_event->event == GUI_EVENT_KEY_RIGHT_PRESS)
    {
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
            base_display(p_sliderBase);

            if (p_slider->onValueChanged)
            {
                p_slider->onValueChanged(p_slider);
            }
        }
    }
    else
    {
        eventHandled = false;
    }

    return eventHandled;
}

