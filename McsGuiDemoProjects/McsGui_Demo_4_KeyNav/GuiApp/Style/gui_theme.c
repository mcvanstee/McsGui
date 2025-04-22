#include "gui_theme.h"

#include "gui_app.h"

void theme_setTheme(void *p_component)
{
    base_setProperty(p_component, FILE_PROPERTY_THEME, g_guiApp.theme.theme);
}


Color_t theme_getBackgroundColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_BACKGROUND_LIGHT;
    }
}

Color_t theme_getSeparatorColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_SEPARATOR_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_SEPARATOR_LIGHT;
    }
}

Color_t theme_getHeaderColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_HEADER_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_HEADER_BACKGROUND_LIGHT;
    }
}

Color_t theme_getFooterColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_FOOTER_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_FOOTER_BACKGROUND_LIGHT;
    }
}

Color_t theme_getFocusItemColor(const bool focused)
{
    if (focused)
    {
        switch (g_guiApp.theme.theme)
        {
            case PROPERTY_THEME_VALUE_DARK:
                return COLOR_FOCUS_BACKGROUND_DARK;
            case PROPERTY_THEME_VALUE_LIGHT:
            default:
                return COLOR_FOCUS_BACKGROUND_LIGHT;
        }
    }
    else
    {
        return theme_getBackgroundColor();
    }
}

Color_t theme_getSliderColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_IRL_BLUE;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_IRL_BLUE;
    }
}

Color_t theme_getNumberInputColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_BACKGROUND_LIGHT;
    }
}

font_key_e theme_getDefaultFont(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return FONT_KEY_TEXT_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return FONT_KEY_TEXT_LIGHT;
    }
}

font_key_e theme_getHeaderFont(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return FONT_KEY_TITLE_SMALL_HEADER_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return FONT_KEY_TITLE_SMALL_HEADER_LIGHT;
    }
}
