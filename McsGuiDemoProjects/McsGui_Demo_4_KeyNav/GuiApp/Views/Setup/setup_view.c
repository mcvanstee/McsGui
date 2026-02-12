#include "setup_view.h"

#include <stdio.h>

#include "gui_app.h"

#include "main_view.h"
#include "limits_view.h"
#include "interval_view.h"

static void setup_view_create(View_s *p_view);
static void sv_activeItemChanged(ListView_s *p_listView);

static int8_t m_itemIndex = 0;

void setup_view_navigateTo(void)
{
    m_itemIndex = 0;
    view_navigateTo(gui_app_getView(), setup_view_create);
}

void setup_view_navigateBackTo(void)
{
    view_navigateTo(gui_app_getView(), setup_view_create);
}

static void setup_view_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_SETUP);

    ListView_s *p_listView = listview_ext_newNavigationListView();
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_ARROW_BACK, FILE_KEY_TEXT_BACK, mainview_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_PULSE, FILE_KEY_TEXT_INTERVAL, interval_view_navigateTo);
    listview_ext_addNavigationItem(p_listView, FILE_KEY_ICON_LIMIT, FILE_KEY_TEXT_LIMITS, limits_view_navigateTo);

    listview_setOnActiveItemChanged(p_listView, sv_activeItemChanged);
    listview_setActiveIndex(p_listView, m_itemIndex);
    base_setFocus(p_listView, true);
    view_addComponent(p_view, p_listView);
}

static void sv_activeItemChanged(ListView_s *p_listView)
{
    listview_ext_activeNavigationItemChanged(p_listView);
    m_itemIndex = listview_getActiveIndex(p_listView);
}


