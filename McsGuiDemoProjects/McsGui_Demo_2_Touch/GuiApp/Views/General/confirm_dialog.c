#include "confirm_dialog.h"

#include "gui_app.h"
#include "gui_custom_components.h"

static void cd_create(View_s *p_view, const file_key_e title, const file_key_e message);

static void (*m_p_okBtnPressed)(void) = NULL;
static void (*m_p_cancelBtnPressed)(void) = NULL;

void confirm_dialog_show(
        const file_key_e title, const file_key_e message,
        void (*okBtnPressed)(void), void (*cancelBtnPressed)(void))
{
    m_p_okBtnPressed = okBtnPressed;
    m_p_cancelBtnPressed = cancelBtnPressed;
    View_s *p_view = &g_guiApp.view;

    view_beforeNavigateTo(p_view);
    cd_create(p_view, title, message);
    view_display(p_view);
    view_afterNavigatedTo(p_view);
}

static void cd_create(View_s *p_view, const file_key_e title, const file_key_e message)
{
    header_setTitle(title);

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    Label_s *p_message = label_newInit();
    label_setBmpKey(p_message, message);
    theme_setTheme(p_message);
    base_addNewInitAnchor(p_message);
    anchor_setCenterInParent(p_message, p_pane);
    view_addComponent(p_view, p_message);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BTN_CANCEL, m_p_cancelBtnPressed);
    gui_addFooterSpacer(p_footer);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BTN_CHECKMARK_LARGE, m_p_okBtnPressed);
}
