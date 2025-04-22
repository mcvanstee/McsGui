#ifndef CUSTOMCOMPONENTS_GUI_SLIDER_H_
#define CUSTOMCOMPONENTS_GUI_SLIDER_H_

#include "mcsgui.h"

typedef struct slider_t
{
    BaseComponent_s base;
    Button_s minusButton;
    Button_s plusButton;
    KeyNavigation_s minusKeyNavigation;
    KeyNavigation_s plusKeyNavigation;
    int16_t value;
    int16_t minValue;
    int16_t maxValue;
    int8_t step;
    bool active;
    Color_t colorLeft;
    Color_t colorRight;
    void (*onValueChanged)(struct slider_t *slider);
} Slider_s;

Slider_s *slider_new(void);
Slider_s *slider_newInit(void);

void slider_delete(BaseComponent_s *p_sliderBase);
void slider_init(Slider_s *slider);

void slider_setValue(Slider_s *slider, int16_t value);
int16_t slider_getValue(Slider_s *slider);
void slider_setStep(Slider_s *slider, int8_t step);
void slider_setLeftColor(Slider_s *slider, Color_t color);
void slider_setRightColor(Slider_s *slider, Color_t color);
void slider_setOnValueChanged(Slider_s *slider, void (*onValueChanged)(Slider_s *slider));

#endif /* CUSTOMCOMPONENTS_GUI_SLIDER_H_ */
