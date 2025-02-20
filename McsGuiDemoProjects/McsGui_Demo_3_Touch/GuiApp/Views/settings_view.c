#include "settings_view.h"

#include "display_api.h"

#include "gui_app.h"
#include "gui_settings.h"
#include "gui_custom_components.h"
#include "gui_component_extensions.h"
#include "fonts.h"

#include "display_settings_view.h"
#include "datetime_settings_view.h"
#include "language_settings_view.h"

#define GROUP_BOX_LARGE_WIDTH 416
#define GROUP_BOX_HEIGHT 280


static void sv_create(View_s *p_view);


void settings_view_navigateTo(void)
{
	view_navigateTo(&g_guiApp.view, sv_create);
}

static void sv_create(View_s *p_view)
{
	gui_app_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setSize(p_item, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT);
    view_addComponent(p_view, p_item);

    GroupBox_s *p_displayGB = group_box_newInitTitleSize(
            FILE_KEY_TITLE_SETTINGS, GROUP_BOX_LARGE_WIDTH, GROUP_BOX_HEIGHT);
    base_addNewInitAnchor(p_displayGB);
    anchor_setTopAnchor(p_displayGB, p_item, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_displayGB, p_item, Gui_Anchor_Left);
    anchor_setTopMargin(p_displayGB, 20);
    anchor_setLeftMargin(p_displayGB, 10);
    view_addComponent(p_view, p_displayGB);

    ButtonCustom_s *p_displayButton = custom_cmp_createIconNavButton(
            FILE_KEY_ICON_DISPLAY, FILE_KEY_TITLE_DISPLAY, display_settings_view_navigateTo);
    anchor_setTopAnchor(p_displayButton, p_displayGB, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_displayButton, p_displayGB, Gui_Anchor_Left);
    anchor_setTopMargin(p_displayButton, 20);
    anchor_setLeftMargin(p_displayButton, 20);
    group_box_addComponent(p_displayGB, p_displayButton);

    ButtonCustom_s *p_languageButton = custom_cmp_createIconNavButton(
            FILE_KEY_ICON_LANGUAGE, FILE_KEY_TITLE_LANGUAGE, language_settings_view_navigateTo);
    anchor_setTopAnchor(p_languageButton, p_displayButton, Gui_Anchor_Bottom);
    anchor_setLeftAnchor(p_languageButton, p_displayButton, Gui_Anchor_Left);
    anchor_setTopMargin(p_languageButton, 15);
    group_box_addComponent(p_displayGB, p_languageButton);

    ButtonCustom_s *p_dateTimeButton = custom_cmp_createIconNavButton(
            FILE_KEY_ICON_CLOCK, FILE_KEY_TITLE_DATE_TIME, datetime_settings_view_navigateTo);
    anchor_setTopAnchor(p_dateTimeButton, p_languageButton, Gui_Anchor_Bottom);
    anchor_setLeftAnchor(p_dateTimeButton, p_languageButton, Gui_Anchor_Left);
    anchor_setTopMargin(p_dateTimeButton, 15);
    group_box_addComponent(p_displayGB, p_dateTimeButton);
}

void settings_view_saveSettings(View_s *p_view)
{
    GuiSettings_s settings = settings_getSettings();
    settings.language = g_guiApp.language;
    settings.showTime = g_guiApp.showTime;
    settings.showDate = g_guiApp.showDate;
    settings.displayBrightness = g_guiApp.displayBrightness;
    settings_setSettings(settings);

    settings_save();
}
