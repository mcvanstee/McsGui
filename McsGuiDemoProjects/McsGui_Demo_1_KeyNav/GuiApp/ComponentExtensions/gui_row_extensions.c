#include "gui_row_extensions.h"


Row_s *gui_addFooterButtonRow(View_s *p_view)
{
    Rectangle_s *p_rect = rectangle_newInit();
    rectangle_showBorderOnly(p_rect, true);
    rectangle_setBorderThickness(p_rect, 6);
    rectangle_setBorderColor(p_rect, theme_getFooterColor());
    base_setSize(&p_rect->base, STYLE_DISPLAY_WIDTH - 10, 48);
    base_setPosition(&p_rect->base, 5, 266);
    view_addComponent(p_view, p_rect);

    Row_s *p_row = row_newInit();
    row_setSpacing(p_row, 10);
    base_setBackground(p_row, theme_getBackgroundColor());
    base_addNewInitAnchor(p_row);
    anchor_setCenterInParent(p_row, p_rect);
    view_addComponent(p_view, p_row);

    return p_row;
}

FooterButton_s *gui_addFooterButton(Row_s *p_row, const file_key_e icon, void (*onPressed)(void))
{
    FooterButton_s *p_footerButton = footer_btn_new();
    footer_btn_initIcon(p_footerButton, icon, onPressed);
    row_addComponent(p_row, p_footerButton);

    return p_footerButton;
}

void gui_addFooterSpacer(Row_s *p_row)
{
    Rectangle_s *p_rect = rectangle_new();
    rectangle_initFillSize(p_rect, theme_getBackgroundColor(), FOOTER_BTN_WIDTH, FOOTER_BTN_HEIGHT);
    row_addComponent(p_row, p_rect);
}
