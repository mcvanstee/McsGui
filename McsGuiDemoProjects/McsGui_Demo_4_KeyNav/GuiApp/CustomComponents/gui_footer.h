#ifndef CUSTOMCOMPONENTS_GUI_FOOTER_H_
#define CUSTOMCOMPONENTS_GUI_FOOTER_H_

#include "gui_theme.h"

typedef struct
{
    Button_s button;
    KeyNavigation_s keyNavigation;
} Footer_s;


void footer_init(Footer_s *p_footer);

void footer_display(void);
void footer_showLogo(void);
void footer_drawBackground(void);
void footer_resetButton(Footer_s *p_footer);
void footer_setOnReleased(Footer_s *p_footer, void (*onReleased)(void));

#endif /* CUSTOMCOMPONENTS_GUI_FOOTER_H_ */
