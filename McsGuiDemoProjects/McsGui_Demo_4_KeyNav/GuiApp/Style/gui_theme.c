#include "gui_theme.h"

#include "gui_app.h"

static GuiThemeSettings_s *m_p_themeSetting;


void theme_init(GuiThemeSettings_s *p_themeSetting)
{
    m_p_themeSetting = p_themeSetting;
}

void theme_setToDefault(GuiThemeSettings_s *p_themeSetting)
{
    p_themeSetting->theme = GuiTheme_Light;
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

GuiTheme_e theme_getGuiTheme(void)
{
    return m_p_themeSetting->theme;
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

Color_t theme_getFocusItemColor(const bool focused)
{
    if (focused)
    {
        return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_FOCUS_BACKGROUND_DARK : COLOR_FOCUS_BACKGROUND_LIGHT;
    }
    else
    {
        return theme_getBackgroundColor();
    }
}

Color_t theme_getSliderColor(void)
{
    return COLOR_IRL_BLUE;
}

Color_t theme_getNumberInputColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_BACKGROUND_DARK : COLOR_BACKGROUND_LIGHT;
}

font_key_e theme_getDefaultFont(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? FONT_KEY_TEXT_DARK : FONT_KEY_TEXT_LIGHT;
}

font_key_e theme_getHeaderFont(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? FONT_KEY_TITLE_SMALL_HEADER_DARK : FONT_KEY_TITLE_SMALL_HEADER_LIGHT;
}
