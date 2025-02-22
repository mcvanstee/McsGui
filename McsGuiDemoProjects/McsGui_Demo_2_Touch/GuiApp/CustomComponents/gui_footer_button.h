#ifndef CUSTOMCOMPONENTS_GUI_FOOTER_BUTTON_H_
#define CUSTOMCOMPONENTS_GUI_FOOTER_BUTTON_H_

#include "gui_theme.h"

#define FOOTER_BTN_WIDTH 146
#define FOOTER_BTN_HEIGHT 38

typedef struct
{
	Button_s button;
	file_key_e content;
	Touch_s touch;
} FooterButton_s;

FooterButton_s *footer_btn_new(void);
FooterButton_s *footer_btn_newInit(void);

void footer_btn_delete(BaseComponent_s *p_footerButtonBase);
void footer_btn_init(FooterButton_s *p_footerButton);
void footer_btn_initIcon(
		FooterButton_s *p_footerButton,
		file_key_e content,
		void (*onPressed)(void));

#endif /* CUSTOMCOMPONENTS_GUI_FOOTER_BUTTON_H_ */
