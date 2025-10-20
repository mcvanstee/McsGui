#ifndef STYLE_GUI_THEME_H_
#define STYLE_GUI_THEME_H_

#include <stdint.h>

#include "fs_file_search.h"
#include "fs_font_search.h"
#include "mcsgui.h"
#include "gui_colors.h"
#include "gui_style.h"

typedef enum
{
    GuiTheme_Light = 0,
    GuiTheme_Dark
} GuiTheme_e;

typedef struct
{
    GuiTheme_e theme;
    Color_t accentColor;
    Color_t cursorColor;
} GuiThemeSetting_s;

void theme_init(GuiThemeSetting_s *p_themeSetting);
void theme_setGuiTheme(GuiTheme_e theme);
void theme_setAccentColor(Color_t accentColor);
void theme_setCursorColor(Color_t cursorColor);

GuiTheme_e theme_getGuiTheme(void);
Color_t theme_getAccentColor(void);
Color_t theme_getCursorColor(void);

void theme_setThemeProperty(void *p_component);
void theme_setButtonIcon(Label_s *p_label);
void theme_setHeaderIcon(Label_s *p_label);
void theme_setCheckboxIcon(Checkbox_s *p_label);
void theme_setButtonText(Label_s *p_label);
void theme_setHeaderText(Label_s *p_label);
void theme_setFooterText(Label_s *p_label);
void theme_setPaneText(Label_s *p_label);
void theme_setPaneTextBlock(TextBlock_s *p_textBlock);

Color_t theme_getButtonFontColor(void);
Color_t theme_getBackgroundColor(void);
Color_t theme_getSeparatorColor(void);
Color_t theme_getHeaderColor(void);
Color_t theme_getFooterColor(void);

Color_t theme_keyboard_getTextBackColor(void);
Color_t theme_getPaneColor(void);
Color_t theme_getPaneBorderColor(void);
Color_t theme_getPaneTextColor(void);
Color_t theme_getComponentColor(void);
Color_t theme_getButtonBorderColor(void);
Color_t theme_getButtonBackgroundColor(void);
Color_t theme_getSliderColor(void);
Color_t theme_getNumberInputColor(void);

font_key_e theme_getKeyboardFont(void);
font_key_e theme_getHeaderFontLarge(void);
font_key_e theme_getHeaderFontSmall(void);
font_key_e theme_getDefaultFont(void);
font_key_e theme_getComponentFont(void);

#endif /* STYLE_GUI_THEME_H_ */
