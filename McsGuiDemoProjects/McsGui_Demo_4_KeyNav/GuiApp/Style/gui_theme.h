#ifndef STYLE_GUI_THEME_H_
#define STYLE_GUI_THEME_H_

#include <stdint.h>

#include "fs_file_search.h"
#include "fs_font_search.h"
#include "mcsgui.h"
#include "gui_colors.h"
#include "gui_style.h"

typedef struct
{
    property_value_theme_e theme;
} GuiTheme_s;

void theme_setTheme(void *p_component);

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
