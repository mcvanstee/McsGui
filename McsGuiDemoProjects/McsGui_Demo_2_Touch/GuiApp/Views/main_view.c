#include "main_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

#include "settings_view.h"
#include "measurement_view.h"
#include "text_input_view.h"
#include "setup_view.h"
#include "set_alarm_view.h"
#include "info_view.h"

static void mv_create(View_s *p_view);

void mainview_navigateTo(void)
{
	view_navigateTo(&g_guiApp.view, mv_create);
}

static void mv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_MAIN_MENU);
    Grid_s *p_grid = gui_addPageButtonGrid(p_view);

    gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_FOCUS, FILE_KEY_TEXT_MEASUREMENT, measurement_view_navigateTo);
    gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_SLIDERS, FILE_KEY_TEXT_SETUP, setup_view_navigateTo);
    gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_GEAR, FILE_KEY_TEXT_SETTINGS, settings_view_navigateTo);
    gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_KEYBOARD, FILE_KEY_TEXT_KEYBOARD, text_input_view_navigateTo);
    gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_BELL, FILE_KEY_TEXT_ALARM, set_alarm_view_navigateTo);
    gui_addPageButton(p_grid, FILE_KEY_ICON_BUTTON_INFO, FILE_KEY_TEXT_INFO, info_view_navigateTo);

    gui_drawFooterBackground();
	gui_showFooterLogo();
}

