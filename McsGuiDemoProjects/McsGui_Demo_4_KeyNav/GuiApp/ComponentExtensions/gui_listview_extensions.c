#include "gui_listview_extensions.h"

#include "gui_app.h"
#include "gui_theme.h"

#define STYLE_NAV_ICON_WIDTH 40
#define STYLE_NAV_LISTVIEW_ROW_HEIGHT 40


static void listview_ext_displayNavigationItem(BaseComponent_s *p_itemBase);
static void listview_ext_displayRadioItem(BaseComponent_s *p_itemBase);
static bool listview_ext_handleEvent(BaseComponent_s *p_listViewBase, const GuiEvent_s *p_event);
static void listview_ext_updateSelection(Checkbox_s *p_checkbox);
static void listview_ext_selectionChanged(Checkbox_s *p_checkbox);

ListView_s *listview_ext_newNavigationListView(void)
{
    ListView_s *p_listView = listview_newInit();
    listview_setRowHight(p_listView, STYLE_NAV_LISTVIEW_ROW_HEIGHT);
    listview_setItemsVisible(p_listView, 4);
    listview_setOnActiveItemChanged(p_listView, listview_ext_activeNavigationItemChanged);
    base_setOnHandleEvent(p_listView, listview_ext_handleEvent);
    base_setPosition(p_listView, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setDimensions(p_listView, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);
    base_setBackground(p_listView, theme_getBackgroundColor());
    base_setTransparent(p_listView, false);
    base_addNewInitKeyNavigation(p_listView);

    return p_listView;
}

void listview_ext_addNavigationItem(ListView_s *p_listView, file_key_e icon, file_key_e text, void (*p_onPressed)(void))
{
    ListViewItem_s *p_item = listviewitem_newInit();
    listviewitem_setOnReleasedEvent(p_item, p_onPressed);
    listview_addItem(p_listView, p_item);
    base_setOnDisplay(p_item, listview_ext_displayNavigationItem);

    Label_s *p_icon = label_new();
    label_initBmp(p_icon, icon);
    theme_applyThemeProperty(p_icon);
    listviewitem_addComponent(p_item, p_icon);

    Label_s *p_text = label_new();
    label_initBmp(p_text, text);
    theme_applyThemeProperty(p_text);
    gui_app_translate(p_text);
    listviewitem_addComponent(p_item, p_text);
}

ListView_s *listview_ext_newRadioListView(void)
{
    ListView_s *p_listView = listview_newInit();
    listview_setRowHight(p_listView, STYLE_NAV_LISTVIEW_ROW_HEIGHT);
    listview_setItemsVisible(p_listView, 4);
    listview_setOnActiveItemChanged(p_listView, listview_ext_activeNavigationItemChanged);
    base_setOnHandleEvent(p_listView, listview_ext_handleEvent);
    base_setPosition(p_listView, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setDimensions(p_listView, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);
    base_setBackground(p_listView, theme_getBackgroundColor());
    base_setTransparent(p_listView, false);
    base_addNewInitKeyNavigation(p_listView);

    return p_listView;
}

void listview_ext_addRadioItem(
    ListView_s *p_listView, file_key_e text, RadioGroup_s *p_radioGroup)
{
    ListViewItem_s *p_item = listviewitem_newInit();
    listview_addItem(p_listView, p_item);
    base_setOnDisplay(p_item, listview_ext_displayRadioItem);

    Checkbox_s *p_checkbox = checkbox_new();
    checkbox_initBmp(p_checkbox, FILE_KEY_ICON_RADIO_BUTTON_UNCHECKED);
    checkbox_setOnSelectionChanged(p_checkbox, listview_ext_selectionChanged);
    theme_applyThemeProperty(p_checkbox);
    listviewitem_addComponent(p_item, p_checkbox);

    Label_s *p_text = label_new();
    label_initBmp(p_text, text);
    theme_applyThemeProperty(p_text);
    gui_app_translate(p_text);
    listviewitem_addComponent(p_item, p_text);

    radiogroup_addButton(p_radioGroup, p_checkbox);
}

void listview_ext_activeNavigationItemChanged(ListView_s *p_listView)
{
    const bool viewWindowChanged = listview_getViewWindowChanged(p_listView);

    if (viewWindowChanged)
    {
        base_display(p_listView);

        return;
    }

    BaseComponent_s *p_previousActiveItem = listview_getPreviousActive(p_listView);

    if (p_previousActiveItem != NULL)
    {
        base_display(p_previousActiveItem);
    }

    BaseComponent_s *p_activeItem = listview_getActive(p_listView);

    if (p_activeItem != NULL)
    {
        base_display(p_activeItem);
    }
}

static void listview_ext_displayNavigationItem(BaseComponent_s *p_itemBase)
{
    ListViewItem_s *p_listViewItem = (ListViewItem_s*) p_itemBase;
    ListView_s *p_listView = (ListView_s*) p_itemBase->p_parent;

    const bool activeItem = (p_listView->activeIndex == p_listViewItem->index);
    const Color_t backgroundColor = theme_getFocusItemColor(activeItem);
    const property_value_focus_e focusProperty = (activeItem) ? PROPERTY_FOCUS_VALUE_TRUE : PROPERTY_FOCUS_VALUE_FALSE;

    Rectangle_s background;
    rectangle_initFillPosSize(&background, backgroundColor, p_itemBase->x, p_itemBase->y, p_itemBase->width, p_itemBase->height);

    Label_s *p_icon = (Label_s*) p_listViewItem->base.p_childList;
    base_setHeight(p_icon, p_itemBase->height);
    base_setWidth(p_icon, STYLE_NAV_ICON_WIDTH);
    base_setPosition(p_icon, p_itemBase->x, p_itemBase->y);
    base_setProperty(p_icon, FILE_PROPERTY_FOCUS, focusProperty);

    Label_s *p_text = (Label_s*) p_icon->base.p_nextBaseComponent;
    base_setHeight(p_text, p_itemBase->height);
    base_setWidth(p_text, p_itemBase->width - STYLE_NAV_ICON_WIDTH);
    base_setPosition(p_text, p_itemBase->x + STYLE_NAV_ICON_WIDTH, p_itemBase->y);
    base_setHorizontalAlignment(p_text, Gui_Align_Left);
    base_setTopPadding(p_text, 1);
    base_setProperty(p_text, FILE_PROPERTY_FOCUS, focusProperty);

    base_display(&background);
    base_display(p_icon);
    base_display(p_text);
}

static void listview_ext_displayRadioItem(BaseComponent_s *p_itemBase)
{
    ListViewItem_s *p_listViewItem = (ListViewItem_s*) p_itemBase;
    ListView_s *p_listView = (ListView_s*) p_itemBase->p_parent;

    const bool activeItem = (p_listView->activeIndex == p_listViewItem->index);
    const Color_t backgroundColor = theme_getFocusItemColor(activeItem);
    const property_value_focus_e focusProperty = (activeItem) ? PROPERTY_FOCUS_VALUE_TRUE : PROPERTY_FOCUS_VALUE_FALSE;

    Rectangle_s background;
    rectangle_initFillPosSize(&background, backgroundColor, p_itemBase->x, p_itemBase->y, p_itemBase->width, p_itemBase->height);

    Checkbox_s *p_checkbox = (Checkbox_s*) p_listViewItem->base.p_childList;
    base_setHeight(p_checkbox, p_itemBase->height);
    base_setWidth(p_checkbox, STYLE_NAV_ICON_WIDTH);
    base_setPosition(p_checkbox, p_itemBase->x, p_itemBase->y);
    base_setProperty(p_checkbox, FILE_PROPERTY_FOCUS, focusProperty);
    base_setBmpKey(p_checkbox, (p_checkbox->checked ? FILE_KEY_ICON_RADIO_BUTTON_CHECKED : FILE_KEY_ICON_RADIO_BUTTON_UNCHECKED));

    Label_s *p_text = (Label_s*) p_checkbox->base.p_nextBaseComponent;
    base_setHeight(p_text, p_itemBase->height);
    base_setWidth(p_text, p_itemBase->width - STYLE_NAV_ICON_WIDTH);
    base_setPosition(p_text, p_itemBase->x + STYLE_NAV_ICON_WIDTH, p_itemBase->y);
    base_setHorizontalAlignment(p_text, Gui_Align_Left);
    base_setTopPadding(p_text, 1);
    base_setProperty(p_text, FILE_PROPERTY_FOCUS, focusProperty);

    base_display(&background);
    base_display(p_checkbox);
    base_display(p_text);
}

static bool listview_ext_handleEvent(BaseComponent_s *p_listViewBase, const GuiEvent_s *p_event)
{
    bool eventHandled = listview_handleEvent(p_listViewBase, p_event);

    if (!eventHandled && (GUI_EVENT_KEY_LEFT_PRESS == p_event->event))
    {
        ListView_s *p_listView = (ListView_s*) p_listViewBase;

        if (p_listView->activeIndex != 0)
        {
            listview_setActiveIndexNotifyChanged(p_listView, 0);
        }

        eventHandled = true;
    }

    return eventHandled;
}

static void listview_ext_selectionChanged(Checkbox_s *p_checkbox)
{
    listview_ext_updateSelection(p_checkbox);
    base_display(p_checkbox);
}

static void listview_ext_updateSelection(Checkbox_s *p_checkbox)
{
    if (p_checkbox->checked)
    {
        base_setBmpKey(p_checkbox, FILE_KEY_ICON_RADIO_BUTTON_CHECKED);
    }
    else
    {
        base_setBmpKey(p_checkbox, FILE_KEY_ICON_RADIO_BUTTON_UNCHECKED);
    }
}
