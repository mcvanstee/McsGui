#include "gui_footer.h"

#include "Graphics/gui_graphics.h"


static void footer_backButtonFocusChanged(BaseComponent_s *p_buttonBase);
static void footer_displayButton(BaseComponent_s *p_buttonBase);

void footer_init(Footer_s *p_footer)
{
    button_init(&p_footer->button);
    button_setOnFocusChanged(&p_footer->button, footer_backButtonFocusChanged);
    base_setDimensions(&p_footer->button, STYLE_FOOTER_BUTTON_WIDTH, STYLE_FOOTER_BUTTON_HEIGHT);
    base_setPosition(&p_footer->button, STYLE_FOOTER_BUTTON_X, STYLE_FOOTER_BUTTON_Y);
    base_setBmpKey(&p_footer->button, FILE_KEY_ICON_ARROW_BACK);
    base_setVisible(&p_footer->button, false);
    base_setOnDisplay(&p_footer->button, footer_displayButton);

    keynav_init(&p_footer->keyNavigation);
    base_addKeyNavigation(&p_footer->button.base, &p_footer->keyNavigation);
}

static void footer_backButtonFocusChanged(BaseComponent_s *p_buttonBase)
{
    base_display(p_buttonBase);
}

static void footer_displayButton(BaseComponent_s *p_buttonBase)
{
    if (!p_buttonBase->visible)
    {
        return;
    }

    Color_t backgroundColor =
            p_buttonBase->focused ? theme_getFocusItemColor(true) : theme_getBackgroundColor();

    Color_t borderColor =
            p_buttonBase->focused ? COLOR_ACCENT_RED : theme_getBackgroundColor();

    Rectangle_s background;
    rectangle_initFillBorderPosSize(
            &background, backgroundColor,
            STYLE_FOOTER_BUTTON_X, STYLE_FOOTER_BUTTON_Y,
            STYLE_FOOTER_BUTTON_WIDTH, STYLE_FOOTER_BUTTON_HEIGHT,
            2, borderColor);
    base_display(&background);

    const property_value_focus_e propertyValueFocus =
            (p_buttonBase->focused) ? PROPERTY_FOCUS_VALUE_TRUE : PROPERTY_FOCUS_VALUE_FALSE;
    base_setProperty(p_buttonBase, FILE_PROPERTY_FOCUS, propertyValueFocus);
    theme_applyThemeProperty(p_buttonBase);

    graphics_displayComponent(p_buttonBase);
}

void footer_showLogo(void)
{
    Item_s item;
    item_init(&item);
    base_setPosition(&item, STYLE_FOOTER_X, STYLE_FOOTER_Y);
    base_setDimensions(&item, STYLE_FOOTER_WIDTH, STYLE_FOOTER_HEIGHT);

    Label_s logo;
    label_init(&logo);
    GuiAnchor_s logoAnchor;
    anchor_init(&logoAnchor);
    base_addAnchor(&logo, &logoAnchor);
    anchor_setRightAnchor(&logo, &item, Gui_Anchor_Right);
    anchor_setVerticalCenter(&logo, &item);
    anchor_setRightMargin(&logo, 1);
    label_setBmpKey(&logo, FILE_KEY_ANIMATION_IRL_LOGO);
    base_setDimensions(&logo, 38, 37);
    base_setBackground(&logo, COLOR_IRL_BLUE);
    base_setTransparent(&logo, false);
    base_display(&logo);

    Label_s mcsGui;
    label_initBmp(&mcsGui, FILE_KEY_TEXT_MCSGUI);
    theme_applyThemeProperty(&mcsGui);
    GuiAnchor_s mcsGuiAnchor;
    anchor_init(&mcsGuiAnchor);
    base_addAnchor(&mcsGui.base, &mcsGuiAnchor);
    anchor_setRightAnchor(&mcsGui, &logo, Gui_Anchor_Left);
    anchor_setVerticalCenter(&mcsGui, &logo);
    anchor_setRightMargin(&mcsGui, 10);
    base_display(&mcsGui.base);
}

void footer_drawBackground(void)
{
    Rectangle_s background;
    rectangle_initFillPosSize(
        &background, theme_getFooterColor(),
        STYLE_FOOTER_X, STYLE_FOOTER_Y, STYLE_DISPLAY_WIDTH, STYLE_FOOTER_HEIGHT);
    base_display(&background);

    Rectangle_s separatorBottom;
    rectangle_initFillPosSize(
        &separatorBottom, theme_getSeparatorColor(),
        STYLE_FOOTER_X, STYLE_FOOTER_SEPARATOR_Y, STYLE_DISPLAY_WIDTH, STYLE_FOOTER_SEPARATOR_HEIGHT);
    base_display(&separatorBottom);

    footer_showLogo();
}

void footer_resetButton(Footer_s *p_footer)
{
    if (p_footer->button.base.visible)
    {
        Rectangle_s background;
        rectangle_initFillPosSize(
            &background, theme_getBackgroundColor(),
            STYLE_FOOTER_BUTTON_X, STYLE_FOOTER_BUTTON_Y,
            STYLE_FOOTER_BUTTON_WIDTH, STYLE_FOOTER_BUTTON_HEIGHT);
        base_display(&background);
    }

    button_setOnReleasedEvent(&p_footer->button, NULL);
    base_setFocus(&p_footer->button, false);
    base_setVisible(&p_footer->button, false);
}

void footer_setOnReleased(Footer_s *p_footer, void (*onReleased)(void))
{
    button_setOnReleasedEvent(&p_footer->button, onReleased);
    base_setVisible(&p_footer->button, true);
}
