#ifndef CUSTOMCOMPONENTS_GUI_BUTTON_CUSTOM_H_
#define CUSTOMCOMPONENTS_GUI_BUTTON_CUSTOM_H_

#include "mcsgui.h"
#include "gui_config.h"
#include "Core/gui_basecomponent.h"
#include "fs_file_search.h"


typedef struct button_custom_s
{
	Button_s button;
	Touch_s touch;
	GuiAnchor_s anchor;
	BorderData_s borderData;
    FontData_s fontData;
    char text[GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH_INC_NULL];
    file_key_e textBmp;
    uint16_t iconWidth;
    uint8_t iconLeftMargin;
    uint8_t textLeftMargin;
} ButtonCustom_s;

ButtonCustom_s *button_custom_new(void);
ButtonCustom_s *button_custom_newInit(void);

void button_custom_delete(BaseComponent_s *p_buttonBase);
void button_custom_init(ButtonCustom_s *p_button);

void button_custom_setIcon(ButtonCustom_s *p_button, const file_key_e icon);
void button_custom_setTextBmp(ButtonCustom_s *p_button, const file_key_e text);
void button_custom_setText(ButtonCustom_s *p_button, const char *p_text);
void button_custom_setFont(ButtonCustom_s *p_button, const uint8_t font);

void button_custom_setColor(ButtonCustom_s *p_button, const Color_t color);
void button_custom_showBorderOnly(ButtonCustom_s *p_button, const bool showBorderOnly);
void button_custom_setBorderColor(ButtonCustom_s *p_button, const Color_t color);
void button_custom_setBorderThickness(ButtonCustom_s *p_button, const uint8_t thickness);
void button_custom_setRadius(ButtonCustom_s *p_button, const uint8_t radius);


#endif /* CUSTOMCOMPONENTS_GUI_BUTTON_CUSTOM_H_ */
