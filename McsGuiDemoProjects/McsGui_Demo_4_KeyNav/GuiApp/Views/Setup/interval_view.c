#include "interval_view.h"

#include "gui_app.h"

#include "setup_view.h"

static void iv_create(View_s *p_view);
static void iv_valueChanged(NumberInput_s *p_numberInput);

void interval_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, iv_create);
}

static void iv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_INTERVAL);

    gui_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setSize(p_item, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);
    view_addComponent(p_view, p_item);

    NumberInput_s *p_numberInput = num_input_newInit();
    num_input_setMinMaxValue(p_numberInput, 1, 30);
    num_input_setValue(p_numberInput, g_guiApp.intervalTime_s);
    num_input_setOnValueChanged(p_numberInput, iv_valueChanged);
    base_addNewInitAnchor(p_numberInput);
    anchor_setCenterInParent(p_numberInput, p_item);
    view_addComponent(p_view, p_numberInput);

    keynav_up(&g_guiApp.footer.button, &p_numberInput->decreaseButton);
    keynav_down(&p_numberInput->decreaseButton, &g_guiApp.footer.button);
    keynav_down(&p_numberInput->increaseButton, &g_guiApp.footer.button);

    footer_setOnReleased(&g_guiApp.footer, setup_view_navigateBackTo);
    base_setFocus(&g_guiApp.footer.button, true);
}

static void iv_valueChanged(NumberInput_s *p_numberInput)
{
    g_guiApp.intervalTime_s = p_numberInput->value;
}
