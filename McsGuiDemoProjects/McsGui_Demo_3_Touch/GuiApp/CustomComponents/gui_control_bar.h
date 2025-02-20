#ifndef CUSTOMCOMPONENTS_GUI_CONTROL_BAR_H_
#define CUSTOMCOMPONENTS_GUI_CONTROL_BAR_H_

#include "mcsgui.h"
#include "style.h"
#include "fs_file_search.h"

#define CONTROL_BAR_BUTTON_COUNT 8
#define CONTROL_BAR_BUTTON_WIDTH STYLE_CONTROL_BAR_WIDTH
#define CONTROL_BAR_BUTTON_HEIGHT 40

typedef struct
{
	BaseComponent_s base;
	Touch_s touch;
	file_key_e iconList[CONTROL_BAR_BUTTON_COUNT];
	void (*onPressed[CONTROL_BAR_BUTTON_COUNT])(void);
	int8_t selectedButton;
} ControlBar_s;

void control_bar_init(ControlBar_s *p_controlBar);
void control_bar_delete(BaseComponent_s *p_controlBarBase);

void control_bar_setSelected(ControlBar_s *p_controlBar, uint8_t buttonIndex);
void control_bar_addButton(ControlBar_s *p_controlBar, uint8_t buttonIndex, file_key_e icon, void (*onPressed)(void));
void control_bar_setButtonIcon(ControlBar_s *p_controlBar, uint8_t buttonIndex, file_key_e icon);
void control_bar_drawButton(ControlBar_s *p_controlBar, uint8_t buttonIndex);

#endif /* CUSTOMCOMPONENTS_GUI_CONTROL_BAR_H_ */
