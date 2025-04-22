#include "info_view.h"

#include <stdio.h>

#include "gui_app.h"


static void iv_create(View_s *p_view, void (*p_navBackView)(void));

void info_view_navigateTo(void (*p_navBackView)(void))
{
    view_navigateAway(&g_guiApp.view);
    view_beforeNavigateTo(&g_guiApp.view);
    iv_create(&g_guiApp.view, p_navBackView);
    view_display(&g_guiApp.view);
    view_afterNavigatedTo(&g_guiApp.view);
}

static void iv_create(View_s *p_view, void (*p_navBackView)(void))
{
    header_setTitle(FILE_KEY_TITLE_INFO);
    gui_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setSize(p_item, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);
    base_addNewInitAnchor(p_item);

    TextBlock_s *p_irlTB = textblock_newInit();
    textblock_setFont(p_irlTB, theme_getDefaultFont());
    textblock_setText(p_irlTB, "IRL Software");
    base_addNewInitAnchor(p_irlTB);
    anchor_setLeftAnchor(p_irlTB, p_item, Gui_Anchor_Left);
    anchor_setTopAnchor(p_irlTB, p_item, Gui_Anchor_Top);
    anchor_setLeftMargin(p_irlTB, 10);
    anchor_setTopMargin(p_irlTB, 10);
    view_addComponent(p_view, p_irlTB);

    TextBlock_s *p_mailTB = textblock_newInit();
    textblock_setFont(p_mailTB, theme_getDefaultFont());
    textblock_setText(p_mailTB, "info@irlsoftware.nl");
    base_addNewInitAnchor(p_mailTB);
    anchor_setLeftAnchor(p_mailTB, p_irlTB, Gui_Anchor_Left);
    anchor_setTopAnchor(p_mailTB, p_irlTB, Gui_Anchor_Bottom);
    anchor_setTopMargin(p_mailTB, 10);
    view_addComponent(p_view, p_mailTB);

    TextBlock_s *p_mcsguiTB = textblock_newInit();
    textblock_setFont(p_mcsguiTB, theme_getDefaultFont());
    snprintf(p_mcsguiTB->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "McsGui V%d.%d.%d",
            MCSGUI_VERSION_MAJOR, MCSGUI_VERSION_MINOR, MCSGUI_VERSION_PATCH);
    base_addNewInitAnchor(p_mcsguiTB);
    anchor_setLeftAnchor(p_mcsguiTB, p_mailTB, Gui_Anchor_Left);
    anchor_setTopAnchor(p_mcsguiTB, p_mailTB, Gui_Anchor_Bottom);
    anchor_setTopMargin(p_mcsguiTB, 20);
    view_addComponent(p_view, p_mcsguiTB);

    Label_s *p_label = label_new();
    label_initBmp(p_label, FILE_KEY_IRL_LOGO_128);
    base_addNewInitAnchor(p_label);
    anchor_setRightAnchor(p_label, p_item, Gui_Anchor_Right);
    anchor_setTopAnchor(p_label, p_item, Gui_Anchor_Top);
    anchor_setRightMargin(p_label, 10);
    anchor_setTopMargin(p_label, 10);
    view_addComponent(p_view, p_label);

    footer_setOnReleased(&g_guiApp.footer, p_navBackView);
    base_setFocus(&g_guiApp.footer.button, true);
}
