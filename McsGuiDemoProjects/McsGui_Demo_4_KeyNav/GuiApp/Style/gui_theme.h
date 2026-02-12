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
} GuiThemeSettings_s;

void theme_init(GuiThemeSettings_s *p_themeSetting);
void theme_setToDefault(GuiThemeSettings_s *p_themeSetting);
void theme_setGuiTheme(GuiTheme_e theme);
GuiTheme_e theme_getGuiTheme(void);

void theme_applyThemeProperty(void *p_component);

Color_t theme_getBackgroundColor(void);
Color_t theme_getSeparatorColor(void);
Color_t theme_getHeaderColor(void);
Color_t theme_getFooterColor(void);
Color_t theme_getFocusItemColor(const bool focused);

Color_t theme_getSliderColor(void);
Color_t theme_getNumberInputColor(void);

font_key_e theme_getDefaultFont(void);
font_key_e theme_getHeaderFont(void);

#endif /* STYLE_GUI_THEME_H_ */
