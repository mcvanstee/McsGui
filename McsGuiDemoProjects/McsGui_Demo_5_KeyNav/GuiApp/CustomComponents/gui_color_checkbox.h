#ifndef CUSTOMCOMPONENTS_GUI_COLOR_CHECKBOX_H_
#define CUSTOMCOMPONENTS_GUI_COLOR_CHECKBOX_H_

#include "gui_theme.h"

typedef struct
{
    Checkbox_s checkbox;
    Color_t color;
    KeyNavigation_s keyNavigation;
} ColorCheckbox_s;

ColorCheckbox_s *color_checkbox_new(void);
ColorCheckbox_s *color_checkbox_newInit(void);

void color_checkbox_delete(BaseComponent_s *p_colorCheckboxBase);
void color_checkbox_init(ColorCheckbox_s *p_colorCheckbox);
void color_checkbox_setColor(ColorCheckbox_s *p_colorCheckbox, Color_t color);

#endif /* CUSTOMCOMPONENTS_GUI_COLOR_CHECKBOX_H_ */
