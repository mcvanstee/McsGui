#include "info_view.h"

#include <stdio.h>

#include "gui_app.h"
#include "gui_custom_components.h"

#include "main_view.h"

static void iv_create(View_s *p_view);
static void iv_intitTextBlock(TextBlock_s *p_textBlock, const char *p_text);

void info_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), iv_create);
}

static void iv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_INFO);
    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    TextBlock_s *p_irlTB = textblock_newInit();
    iv_intitTextBlock(p_irlTB, "IRL Software");
    base_addNewInitAnchor(p_irlTB);
    anchor_setLeftAnchor(p_irlTB, p_pane, Gui_Anchor_Left);
    anchor_setTopAnchor(p_irlTB, p_pane, Gui_Anchor_Top);
    anchor_setLeftMargin(p_irlTB, 10);
    anchor_setTopMargin(p_irlTB, 10);
    view_addComponent(p_view, p_irlTB);

    TextBlock_s *p_mailTB = textblock_newInit();
    iv_intitTextBlock(p_mailTB, "info@irlsoftware.nl");
    base_addNewInitAnchor(p_mailTB);
    anchor_setLeftAnchor(p_mailTB, p_irlTB, Gui_Anchor_Left);
    anchor_setTopAnchor(p_mailTB, p_irlTB, Gui_Anchor_Bottom);
    anchor_setTopMargin(p_mailTB, 10);
    view_addComponent(p_view, p_mailTB);

    TextBlock_s *p_mcsguiTB = textblock_newInit();
    iv_intitTextBlock(p_mcsguiTB, "");
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
    anchor_setRightAnchor(p_label, p_pane, Gui_Anchor_Right);
    anchor_setTopAnchor(p_label, p_pane, Gui_Anchor_Top);
    anchor_setRightMargin(p_label, 10);
    anchor_setTopMargin(p_label, 10);
    view_addComponent(p_view, p_label);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    FooterButton_s *p_footerButton = gui_addFooterButton(p_footer, FILE_KEY_ICON_ARROW_BACK, mainview_navigateTo);
    base_setFocus(p_footerButton, true);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);
}

static void iv_intitTextBlock(TextBlock_s *p_textBlock, const char *p_text)
{
    textblock_setFont(p_textBlock, theme_getDefaultFont());
    textblock_setText(p_textBlock, p_text);
    textblock_setFontBackColor(p_textBlock, theme_getPaneColor());
    textblock_setFontForeColor(p_textBlock, theme_getPaneTextColor());
}
