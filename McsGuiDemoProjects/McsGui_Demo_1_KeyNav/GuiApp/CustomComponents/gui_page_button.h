#ifndef CUSTOMCOMPONENTS_GUI_PAGE_BUTTON_H_
#define CUSTOMCOMPONENTS_GUI_PAGE_BUTTON_H_

#include "gui_theme.h"

typedef struct
{
	Button_s button;
	file_key_e icon;
	file_key_e text;
	KeyNavigation_s keyNavigation;
} PageButton_s;

PageButton_s *page_btn_new(void);
PageButton_s *page_btn_newInit(void);

void page_btn_delete(BaseComponent_s *p_pageButtonBase);
void page_btn_init(PageButton_s *p_pageButton);
void page_btn_initIconText(
		PageButton_s *p_pageButton,
		const file_key_e icon, const file_key_e text,
		void (*onPressed)(void));

#endif /* CUSTOMCOMPONENTS_GUI_PAGE_BUTTON_H_ */
