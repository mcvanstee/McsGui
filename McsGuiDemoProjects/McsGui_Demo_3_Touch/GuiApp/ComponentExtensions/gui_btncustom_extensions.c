#include "gui_btncustom_extensions.h"

#include "gui_app.h"
#include "colors.h"

ButtonCustom_s* custom_cmp_createIconNavButton(
    const file_key_e icon, const file_key_e text, void (*onReleased)(void))
{
    ButtonCustom_s *p_displayButton = button_custom_newInit();
    base_setSize(p_displayButton, 150, 36);
    button_custom_setTextBmp(p_displayButton, text);
    button_setOnReleasedEvent(&p_displayButton->button, onReleased);
    button_custom_setBorderColor(p_displayButton, COLOR_ACCENT_RED);
    button_custom_setColor(p_displayButton, COLOR_BACKGROUND);
    button_custom_setBorderThickness(p_displayButton, 1);
    button_custom_setRadius(p_displayButton, 3);
    button_custom_setIcon(p_displayButton, icon);
    gui_app_translate(p_displayButton);
    p_displayButton->textLeftMargin = 3;
    p_displayButton->iconLeftMargin = 5;
    p_displayButton->iconWidth = 30;

    return p_displayButton;
}
