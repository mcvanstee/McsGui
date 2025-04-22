#include "limits_view.h"

#include "gui_app.h"

#include "setup_view.h"

static void lv_create(View_s *p_view);
static void lv_upperLimitChanged(NumberInput_s *p_numberInput);
static void lv_lowerLimitChanged(NumberInput_s *p_numberInput);

void limits_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, lv_create);
}

static void lv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_LIMITS);

    gui_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setSize(p_item, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);
    view_addComponent(p_view, p_item);

    Row_s *p_upperRow = row_newInit();
    row_setSpacing(p_upperRow, 10);
    base_addNewInitAnchor(p_upperRow);
    anchor_setLeftAnchor(p_upperRow, p_item, Gui_Anchor_Left);
    anchor_setTopAnchor(p_upperRow, p_item, Gui_Anchor_Top);
    anchor_setTopMargin(p_upperRow, 42);
    anchor_setLeftMargin(p_upperRow, 50);
    view_addComponent(p_view, p_upperRow);

    Label_s *p_upperLimitLabel = label_newInit();
    label_setBmpKey(p_upperLimitLabel, FILE_KEY_TEXT_HIGH);
    gui_translate(p_upperLimitLabel);
    theme_setTheme(&p_upperLimitLabel->base);
    row_addComponent(p_upperRow, p_upperLimitLabel);

    NumberInput_s *p_upperLimitInput = num_input_newInit();
    num_input_setMinMaxValue(p_upperLimitInput, 0, 50);
    num_input_setValue(p_upperLimitInput, g_guiApp.upperLimit);
    num_input_setOnValueChanged(p_upperLimitInput, lv_upperLimitChanged);
    row_addComponent(p_upperRow, p_upperLimitInput);

    Row_s *p_lowerRow = row_newInit();
    row_setSpacing(p_lowerRow, 13);
    base_addNewInitAnchor(p_lowerRow);
    anchor_setLeftAnchor(p_lowerRow, p_upperRow, Gui_Anchor_Left);
    anchor_setTopAnchor(p_lowerRow, p_upperRow, Gui_Anchor_Bottom);
    anchor_setTopMargin(p_lowerRow, 10);
    view_addComponent(p_view, p_lowerRow);

    Label_s *p_lowerLimitLabel = label_newInit();
    label_setBmpKey(p_lowerLimitLabel, FILE_KEY_TEXT_LOW);
    base_setAlignment(p_lowerLimitLabel, Gui_Align_Right, Gui_Align_Center);
    gui_translate(p_lowerLimitLabel);
    theme_setTheme(&p_lowerLimitLabel->base);
    row_addComponent(p_lowerRow, p_lowerLimitLabel);

    NumberInput_s *p_lowerLimitInput = num_input_newInit();
    num_input_setMinMaxValue(p_lowerLimitInput, 0, 50);
    num_input_setValue(p_lowerLimitInput, g_guiApp.lowerLimit);
    num_input_setOnValueChanged(p_lowerLimitInput, lv_lowerLimitChanged);
    row_addComponent(p_lowerRow, p_lowerLimitInput);

    keynav_connectUpDown(&p_upperLimitInput->increaseButton, &p_lowerLimitInput->increaseButton);
    keynav_connectUpDown(&p_upperLimitInput->decreaseButton, &p_lowerLimitInput->decreaseButton);
    keynav_connectUpDown(&p_lowerLimitInput->decreaseButton, &g_guiApp.footer.button);

    footer_setOnReleased(&g_guiApp.footer, setup_view_navigateBackTo);
    base_setFocus(&g_guiApp.footer.button, true);
}

static void lv_upperLimitChanged(NumberInput_s *p_numberInput)
{
    g_guiApp.upperLimit = p_numberInput->value;
}

static void lv_lowerLimitChanged(NumberInput_s *p_numberInput)
{
    g_guiApp.lowerLimit = p_numberInput->value;
}
