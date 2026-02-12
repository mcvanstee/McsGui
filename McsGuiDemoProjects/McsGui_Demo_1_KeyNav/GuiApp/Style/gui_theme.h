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
    property_value_accent_color_e accentColorProperty;
    property_value_accent_color_e cursorColorProperty;
} GuiThemeSetting_s;

void theme_init(GuiThemeSetting_s *p_themeSetting);
void theme_setGuiTheme(GuiTheme_e theme);
void theme_setAccentColorPropertyValue(property_value_accent_color_e value);
void theme_setCursorColorPropertyValue(property_value_accent_color_e value);

GuiTheme_e theme_getGuiTheme(void);
Color_t theme_getAccentColor(void);
Color_t theme_getCursorColor(void);
property_value_theme_e theme_getThemePropertyValue(void);
property_value_accent_color_e theme_getAccentColorPropertyValue(void);
property_value_accent_color_e theme_getCursorColorPropertyValue(void);

void theme_applyThemeProperty(void *p_component);
void theme_applyAccentColorProperty(void *p_component);
void theme_applyCursorColorProperty(void *p_component);

Color_t theme_getAccentColor(void);
Color_t theme_getCursorColor(void);
Color_t theme_getBackgroundColor(void);
Color_t theme_getSeparatorColor(void);
Color_t theme_getHeaderColor(void);
Color_t theme_getFooterColor(void);

Color_t theme_keyboard_getTextBackColor(void);
Color_t theme_getPaneColor(void);
Color_t theme_getPaneBorderColor(void);
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
