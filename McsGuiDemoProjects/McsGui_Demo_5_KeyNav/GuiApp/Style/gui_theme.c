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

void theme_setThemeProperty(void *p_component)
{
    const property_value_theme_e themeProperty =
            (m_p_themeSetting->theme == GuiTheme_Dark) ? PROPERTY_THEME_VALUE_DARK : PROPERTY_THEME_VALUE_LIGHT;

    base_setProperty(p_component, FILE_PROPERTY_THEME, themeProperty);
}

void theme_setAccentColor(Color_t accentColor)
{
    m_p_themeSetting->accentColor = accentColor;
}

GuiTheme_e theme_getGuiTheme(void)
{
    return m_p_themeSetting->theme;
}

Color_t theme_getAccentColor(void)
{
    return m_p_themeSetting->accentColor;
}

Color_t theme_getCursorColor(void)
{
    return m_p_themeSetting->cursorColor;
}

void theme_setCursorColor(Color_t cursorColor)
{
    m_p_themeSetting->cursorColor = cursorColor;
}

void theme_setButtonIcon(Label_s *p_label)
{
    base_setBackground(p_label, theme_getButtonBackgroundColor());
    base_setForeColor(p_label, theme_getAccentColor());
}

void theme_setHeaderIcon(Label_s *p_label)
{
    base_setBackground(p_label, theme_getHeaderColor());
    base_setForeColor(p_label, COLOR_ACCENT_WHITE);
}

void theme_setCheckboxIcon(Checkbox_s *p_checkbox)
{
    const Color_t iconColor = p_checkbox->base.focused ? theme_getAccentColor() : theme_getPaneTextColor();
    base_setBackground(p_checkbox, theme_getPaneColor());
    base_setForeColor(p_checkbox, iconColor);
}

void theme_setButtonText(Label_s *p_label)
{
    base_setBackground(p_label, theme_getButtonBackgroundColor());
    base_setForeColor(p_label, theme_getButtonFontColor());
}

void theme_setHeaderText(Label_s *p_label)
{
    base_setBackground(p_label, theme_getHeaderColor());
    base_setForeColor(p_label, COLOR_ACCENT_WHITE);
    base_setTransparent(p_label, false);
}

void theme_setFooterText(Label_s *p_label)
{
    base_setBackground(p_label, theme_getFooterColor());
    base_setForeColor(p_label, theme_getButtonFontColor());
    base_setTransparent(p_label, false);
}

void theme_setPaneText(Label_s *p_label)
{
    base_setBackground(p_label, theme_getPaneColor());
    base_setForeColor(p_label, theme_getPaneTextColor());
    base_setTransparent(p_label, false);
}

void theme_setPaneTextBlock(TextBlock_s *p_textBlock)
{
    textblock_setFontBackColor(p_textBlock, theme_getPaneColor());
    textblock_setFontForeColor(p_textBlock, theme_getPaneTextColor());
    base_setBackground(p_textBlock, theme_getPaneColor());
    base_setTransparent(p_textBlock, false);
}

Color_t theme_getButtonFontColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_ACCENT_WHITE : COLOR_ACCENT_BLACK;
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

Color_t theme_getPaneTextColor(void)
{
    return (m_p_themeSetting->theme == GuiTheme_Dark) ? COLOR_ACCENT_WHITE : COLOR_ACCENT_BLACK;
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
    return FONT_KEY_ROBOTO_22_R;
}

font_key_e theme_getHeaderFontLarge(void)
{
    return FONT_KEY_ROBOTO_22_R;
}

font_key_e theme_getHeaderFontSmall(void)
{
    return FONT_KEY_ROBOTO_20_R;
}

font_key_e theme_getDefaultFont(void)
{
    return FONT_KEY_ROBOTO_18_R;
}

font_key_e theme_getComponentFont(void)
{
    return FONT_KEY_ROBOTO_16_R;
}
