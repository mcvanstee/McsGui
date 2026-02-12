#include "settings_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

#include "main_view.h"
#include "brightness_view.h"
#include "language_view.h"
#include "accent_color_view.h"
#include "theme_view.h"
#include "set_time_view.h"

static void sv_create(View_s *p_view);


void settings_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), sv_create);
}

static void sv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_SETTINGS);

    Grid_s *p_grid = gui_addPageButtonGrid(p_view);

    PageButton_s *p_themeButton = gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_BRUSH, FILE_KEY_TEXT_THEME, theme_view_navigateTo);
    gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_PALETTE,FILE_KEY_TEXT_ACCENT_COLOR, accent_color_view_navigateTo);
    gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_BRIGHTNESS, FILE_KEY_TEXT_BRIGHTNESS, brightness_view_navigateTo);
    PageButton_s *p_languageButton = gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_GLOBAL, FILE_KEY_TEXT_LANGUAGE, language_view_navigateTo);
    PageButton_s *p_dateButton = gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_AGENDA, FILE_KEY_TEXT_DATE, set_time_view_navigateTo);
    PageButton_s *p_timebutton = gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_CLOCK, FILE_KEY_TEXT_TIME, set_time_view_navigateTo);
    base_setFocus(p_themeButton, true);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);

    FooterButton_s *p_footerButton = gui_addFooterButton(p_footer, FILE_KEY_ICON_BUTTON_ARROW_BACK, mainview_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);

    keynav_down(p_languageButton, p_footerButton);
    keynav_down(p_dateButton, p_languageButton);
    keynav_down(p_timebutton, p_dateButton);
    keynav_up(p_footerButton, p_languageButton);
}



