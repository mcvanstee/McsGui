#include "accent_color_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"

#include "settings_view.h"

#define AC_VIEW_ACCENT_RED_CHECKBOX_ID 1
#define AC_VIEW_ACCENT_BLUE_CHECKBOX_ID 2
#define AC_VIEW_ACCENT_GREEN_CHECKBOX_ID 3

static void ac_create(View_s *p_view);
static void ac_addAccentColorButtons(View_s *p_view, Pane_s *p_pane);
static void ac_accentColorSelectionChanged(RadioGroup_s *p_radioGroup);


void accent_color_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, ac_create);
}

static void ac_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_COLORS);
    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    ac_addAccentColorButtons(p_view, p_pane);

    view_getComponentById(p_view, AC_VIEW_ACCENT_RED_CHECKBOX_ID);
    view_getComponentById(p_view, AC_VIEW_ACCENT_BLUE_CHECKBOX_ID);
    view_getComponentById(p_view, AC_VIEW_ACCENT_GREEN_CHECKBOX_ID);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BUTTON_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);
}

static void ac_addAccentColorButtons(View_s *p_view, Pane_s *p_pane)
{
    Row_s *p_row = row_newInit();
    row_setSpacing(p_row, 10);
    base_setBackground(p_row, theme_getPaneColor());
    base_setTransparent(p_row, false);
    base_addNewInitAnchor(p_row);
    anchor_setTopAnchor(p_row, p_pane, Gui_Anchor_Top);
    anchor_setTopMargin(p_row, 10);
    anchor_setLeftAnchor(p_row, p_pane, Gui_Anchor_Left);
    anchor_setLeftMargin(p_row, 10);

    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, ac_accentColorSelectionChanged);

    Label_s *p_label = label_new();
    label_initBmpPos(p_label, FILE_KEY_TEXT_PANE_ACCENT_COLOR, 20, 20);
    theme_setTheme(p_label);
    gui_translate(p_label);

    ColorCheckbox_s *p_redCheckbox = color_checkbox_newInit();
    color_checkbox_setColor(p_redCheckbox, COLOR_ACCENT_RED);
    base_setId(p_redCheckbox, AC_VIEW_ACCENT_RED_CHECKBOX_ID);

    ColorCheckbox_s *p_blueCheckbox = color_checkbox_newInit();
    color_checkbox_setColor(p_blueCheckbox, COLOR_ACCENT_BLUE);
    base_setId(p_blueCheckbox, AC_VIEW_ACCENT_BLUE_CHECKBOX_ID);

    ColorCheckbox_s *p_greenCheckbox = color_checkbox_newInit();
    color_checkbox_setColor(p_greenCheckbox, COLOR_ACCENT_GREEN);
    base_setId(p_greenCheckbox, AC_VIEW_ACCENT_GREEN_CHECKBOX_ID);

    row_addComponent(p_row, p_redCheckbox);
    row_addComponent(p_row, p_blueCheckbox);
    row_addComponent(p_row, p_greenCheckbox);
    row_addComponent(p_row, p_label);

    radiogroup_addButton(p_radioGroup, &p_redCheckbox->checkbox);
    radiogroup_addButton(p_radioGroup, &p_blueCheckbox->checkbox);
    radiogroup_addButton(p_radioGroup, &p_greenCheckbox->checkbox);

    if (g_guiApp.theme.accentColor == PROPERTY_ACCENT_COLOR_VALUE_RED)
    {
        radiogroup_setSelectedAtIndex(p_radioGroup, 0);
    }
    else if (g_guiApp.theme.accentColor == PROPERTY_ACCENT_COLOR_VALUE_BLUE)
    {
        radiogroup_setSelectedAtIndex(p_radioGroup, 1);
    }
    else if (g_guiApp.theme.accentColor == PROPERTY_ACCENT_COLOR_VALUE_GREEN)
    {
        radiogroup_setSelectedAtIndex(p_radioGroup, 2);
    }
    else
    {
    }

    view_addComponent(p_view, p_row);
    view_addComponent(p_view, p_radioGroup);
}

static void ac_accentColorSelectionChanged(RadioGroup_s *p_radioGroup)
{
    const int8_t selectedIndex = radiogroup_getSelectedIndex(p_radioGroup);

    if (selectedIndex == 0)
    {
        g_guiApp.theme.accentColor = PROPERTY_ACCENT_COLOR_VALUE_RED;
    }
    else if (selectedIndex == 1)
    {
        g_guiApp.theme.accentColor = PROPERTY_ACCENT_COLOR_VALUE_BLUE;
    }
    else if (selectedIndex == 2)
    {
        g_guiApp.theme.accentColor = PROPERTY_ACCENT_COLOR_VALUE_GREEN;
    }
    else
    {
    }
}
