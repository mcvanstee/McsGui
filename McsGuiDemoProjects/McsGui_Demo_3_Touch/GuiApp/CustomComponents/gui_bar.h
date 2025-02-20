#ifndef CUSTOMCOMPONENTS_GUI_BAR_H_
#define CUSTOMCOMPONENTS_GUI_BAR_H_

#include "mcsgui.h"

#define BAR_LEVEL_MAX 100
#define BAR_LEVEL_MIN 0

#define BAR_WIDTH 24
#define BAR_HEIGHT 80


typedef struct
{
	BaseComponent_s base;
	uint8_t level;
	Color_t fillColor;
	Color_t emptyColor;
	Color_t borderColor;
} Bar_s;

Bar_s *bar_new(void);
Bar_s *bar_newInit(void);
void bar_init(Bar_s *p_bar);

void bar_setLevel(Bar_s *p_bar, uint8_t level);
void bar_updateLevel(Bar_s *p_bar, uint8_t level);
void bar_setColors(Bar_s *p_bar, Color_t fillColor, Color_t emptyColor, Color_t borderColor);

#endif /* CUSTOMCOMPONENTS_GUI_BAR_H_ */
