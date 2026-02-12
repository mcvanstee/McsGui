#include "main_view.h"

#include "gui_app.h"

#include "measurement_view.h"
#include "settings_view.h"
#include "setup_view.h"
#include "info_view.h"


static void mv_create(View_s *p_view);
void mv_navigateToInfoView(void);


void mainview_navigateTo(void)
{
	view_navigateTo(gui_app_getView(), mv_create);
}

static void mv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_MAIN_MENU);

    ListView_s *p_listView = listview_ext_newNavigationListView();
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_FOCUS, FILE_KEY_TEXT_MEASUREMENT, measurement_view_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_SLIDERS, FILE_KEY_TEXT_SETUP, setup_view_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_GEAR, FILE_KEY_TEXT_SETTINGS, settings_view_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_INFO, FILE_KEY_TEXT_INFO, mv_navigateToInfoView);
    listview_setActiveIndex(p_listView, 0);
    base_setFocus(p_listView, true);

    view_addComponent(p_view, p_listView);
}

void mv_navigateToInfoView(void)
{
    info_view_navigateTo(mainview_navigateTo);
}
