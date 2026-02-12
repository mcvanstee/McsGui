#include "settings_view.h"

#include "gui_app.h"

#include "main_view.h"
#include "language_view.h"
#include "theme_view.h"
#include "brightness_view.h"
#include "units_view.h"
#include "info_view.h"


static void sv_create(View_s *p_view);
static void sv_activeItemChanged(ListView_s *p_listView);
void sv_navigateToInfoView(void);

static int8_t m_itemIndex = 0;

void settings_view_navigateTo(void)
{
    m_itemIndex = 0;
    view_navigateTo(gui_app_getView(), sv_create);
}

void settings_view_navigateBackTo(void)
{
    view_navigateTo(gui_app_getView(), sv_create);
}

static void sv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_SETTINGS);

    ListView_s *p_listView = listview_ext_newNavigationListView();
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_ARROW_BACK, FILE_KEY_TEXT_BACK, mainview_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_GLOBAL, FILE_KEY_TEXT_LANGUAGE, language_view_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_BRUSH, FILE_KEY_TEXT_THEME, theme_view_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_BRIGHTNESS, FILE_KEY_TEXT_BRIGHTNESS, brightness_view_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_SLIDERS, FILE_KEY_TEXT_UNITS, units_view_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_INFO, FILE_KEY_TEXT_INFO, sv_navigateToInfoView);

    listview_setOnActiveItemChanged(p_listView, sv_activeItemChanged);
    listview_setActiveIndex(p_listView, m_itemIndex);
    base_setFocus(p_listView, true);
    view_addComponent(p_view, p_listView);
}

void sv_navigateToInfoView(void)
{
    info_view_navigateTo(settings_view_navigateBackTo);
}

static void sv_activeItemChanged(ListView_s *p_listView)
{
    listview_ext_activeNavigationItemChanged(p_listView);
    m_itemIndex = listview_getActiveIndex(p_listView);
}

