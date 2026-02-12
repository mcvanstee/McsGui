#include "gui_theme.h"

#include "gui_app.h"

static GuiThemeSetting_s *m_p_themeSetting;


void theme_init(GuiThemeSetting_s *p_themeSetting)
{
    m_p_themeSetting = p_themeSetting;
}

void theme_setGuiTheme(GuiTheme_e theme)
{
    m_p_themeSetting->theme = theme;
}

void theme_applyThemeProperty(void *p_component)
{
    const property_value_theme_e themeProperty =
            (m_p_themeSetting->theme == GuiTheme_Dark) ? PROPERTY_THEME_VALUE_DARK : PROPERTY_THEME_VALUE_LIGHT;

    base_setProperty(p_component, FILE_PROPERTY_THEME, themeProperty);
}

void theme_applyAccentColorProperty(void *p_component)
{
    base_setProperty(p_component, FILE_PROPERTY_ACCENT_COLOR, m_p_themeSetting->accentColorProperty);
}

GuiTheme_e theme_getGuiTheme(void)
{
    return m_p_themeSetting->theme;
}

Color_t theme_getAccentColor(void)
{
    switch (m_p_themeSetting->accentColorProperty)
    {
        case PROPERTY_ACCENT_COLOR_VALUE_RED:
            return COLOR_ACCENT_RED;
        case PROPERTY_ACCENT_COLOR_VALUE_GREEN:
            return COLOR_ACCENT_GREEN;
        case PROPERTY_ACCENT_COLOR_VALUE_BLUE:
            return COLOR_ACCENT_BLUE;
        default:
            return PROPERTY_ACCENT_COLOR_VALUE_RED;
    }
}

property_value_theme_e theme_getThemePropertyValue(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? PROPERTY_THEME_VALUE_DARK : PROPERTY_THEME_VALUE_LIGHT;
}

property_value_accent_color_e theme_getAccentColorPropertyValue(void)
{
    return m_p_themeSetting->accentColorProperty;
}

void theme_setAccentColorPropertyValue(property_value_accent_color_e value)
{
    m_p_themeSetting->accentColorProperty = value;
}

Color_t theme_getBackgroundColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_BACKGROUND_DARK : COLOR_BACKGROUND_LIGHT;
}

Color_t theme_getSeparatorColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_SEPARATOR_DARK : COLOR_SEPARATOR_LIGHT;
}

Color_t theme_getHeaderColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_HEADER_BACKGROUND_DARK : COLOR_HEADER_BACKGROUND_LIGHT;
}

Color_t theme_getFooterColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_FOOTER_BACKGROUND_DARK : COLOR_FOOTER_BACKGROUND_LIGHT;
}

Color_t theme_keyboard_getTextBackColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_KEYBOARD_BUTTON_BACKGROUND_DARK : COLOR_KEYBOARD_BUTTON_BACKGROUND_LIGHT;
}

Color_t theme_getPaneColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_PANE_BACKGROUND_DARK : COLOR_PANE_BACKGROUND_LIGHT;
}

Color_t theme_getPaneBorderColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_PANE_BORDER_DARK : COLOR_PANE_BORDER_LIGHT;
}

Color_t theme_getComponentColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_COMPONENT_BACKGROUND_DARK : COLOR_COMPONENT_BACKGROUND_LIGHT;
}

Color_t theme_getButtonBorderColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_COMPONENT_BORDER_DARK : COLOR_COMPONENT_BORDER_LIGHT;
}

Color_t theme_getButtonBackgroundColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_BUTTON_BACKGROUND_DARK : COLOR_BUTTON_BACKGROUND_LIGHT;
}

Color_t theme_getSliderColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_BUTTON_BACKGROUND_DARK : COLOR_COMPONENT_BACKGROUND_LIGHT;
}

Color_t theme_getNumberInputColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_COMPONENT_BACKGROUND_DARK : COLOR_PANE_BACKGROUND_LIGHT;
}

font_key_e theme_getKeyboardFont(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? FONT_KEY_ROBOTO_22_R_KEYBOARD_DARK : FONT_KEY_ROBOTO_22_R_KEYBOARD_LIGHT;
}

font_key_e theme_getHeaderFontLarge(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? FONT_KEY_ROBOTO_22_R_HEADER_DARK : FONT_KEY_ROBOTO_22_R_HEADER_LIGHT;
}

font_key_e theme_getHeaderFontSmall(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? FONT_KEY_ROBOTO_20_R_HEADER_DARK : FONT_KEY_ROBOTO_20_R_HEADER_LIGHT;
}

font_key_e theme_getDefaultFont(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? FONT_KEY_ROBOTO_18_R_PANE_DARK : FONT_KEY_ROBOTO_18_R_PANE_LIGHT;
}

font_key_e theme_getComponentFont(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? FONT_KEY_ROBOTO_16_R_BUTTON_DARK : FONT_KEY_ROBOTO_16_R_BUTTON_LIGHT;
}
