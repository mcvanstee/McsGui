#include "gui_theme.h"

#include "gui_app.h"

void theme_setTheme(void *p_component)
{
    base_setProperty(p_component, FILE_PROPERTY_THEME, g_guiApp.theme.theme);
}

void theme_setAccentColor(void *p_component)
{
    base_setProperty(p_component, FILE_PROPERTY_ACCENT_COLOR, g_guiApp.theme.accentColor);
}

Color_t theme_getAccentColor(void)
{
    switch (g_guiApp.theme.accentColor)
    {
        case PROPERTY_ACCENT_COLOR_VALUE_WHITE:
            return COLOR_ACCENT_WHITE;
        case PROPERTY_ACCENT_COLOR_VALUE_RED:
            return COLOR_ACCENT_RED;
        case PROPERTY_ACCENT_COLOR_VALUE_GREEN:
            return COLOR_ACCENT_GREEN;
        case PROPERTY_ACCENT_COLOR_VALUE_BLUE:
            return COLOR_ACCENT_BLUE;
        default:
            return COLOR_ACCENT_WHITE;
    }
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

Color_t theme_keyboard_getTextBackColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_KEYBOARD_BUTTON_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_KEYBOARD_BUTTON_BACKGROUND_LIGHT;
    }
}

Color_t theme_getPaneColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_PANE_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_PANE_BACKGROUND_LIGHT;
    }
}

Color_t theme_getPaneBorderColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_PANE_BORDER_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_PANE_BORDER_LIGHT;
    }
}

Color_t theme_getComponentColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_COMPONENT_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_COMPONENT_BACKGROUND_LIGHT;
    }
}

Color_t theme_getButtonBorderColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_COMPONENT_BORDER_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_COMPONENT_BORDER_LIGHT;
    }
}

Color_t theme_getButtonBackgroundColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_BUTTON_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_BUTTON_BACKGROUND_LIGHT;
    }
}

Color_t theme_getSliderColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_BUTTON_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_COMPONENT_BACKGROUND_LIGHT;
    }
}

Color_t theme_getNumberInputColor(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return COLOR_COMPONENT_BACKGROUND_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return COLOR_PANE_BACKGROUND_LIGHT;
    }
}

font_key_e theme_getKeyboardFont(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return FONT_KEY_ROBOTO_22_R_KEYBOARD_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return FONT_KEY_ROBOTO_22_R_KEYBOARD_LIGHT;
    }
}

font_key_e theme_getHeaderFontLarge(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return FONT_KEY_ROBOTO_22_R_HEADER_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return FONT_KEY_ROBOTO_22_R_HEADER_LIGHT;
    }
}

font_key_e theme_getHeaderFontSmall(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return FONT_KEY_ROBOTO_20_R_HEADER_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return FONT_KEY_ROBOTO_20_R_HEADER_LIGHT;
    }
}

font_key_e theme_getDefaultFont(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return FONT_KEY_ROBOTO_18_R_PANE_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return FONT_KEY_ROBOTO_18_R_PANE_LIGHT;
    }
}

font_key_e theme_getComponentFont(void)
{
    switch (g_guiApp.theme.theme)
    {
        case PROPERTY_THEME_VALUE_DARK:
            return FONT_KEY_ROBOTO_16_R_BUTTON_DARK;
        case PROPERTY_THEME_VALUE_LIGHT:
        default:
            return FONT_KEY_ROBOTO_16_R_BUTTON_LIGHT;
    }
}
