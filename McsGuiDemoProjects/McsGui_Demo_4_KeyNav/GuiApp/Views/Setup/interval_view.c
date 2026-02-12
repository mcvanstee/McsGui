#include "interval_view.h"

#include "gui_app.h"
#include "gui_measurement_setup.h"

#include "setup_view.h"

static void iv_create(View_s *p_view);
static void iv_valueChanged(NumberInput_s *p_numberInput);

void interval_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), iv_create);
}

static void iv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_INTERVAL);

    gui_app_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setDimensions(p_item, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);
    view_addComponent(p_view, p_item);

    NumberInput_s *p_numberInput = num_input_newInit();
    num_input_setMinMaxValue(p_numberInput, 1, 30);
    num_input_setValue(p_numberInput, measurement_setup_getSampleInterval());
    num_input_setOnValueChanged(p_numberInput, iv_valueChanged);
    base_addNewInitAnchor(p_numberInput);
    anchor_setCenterInParent(p_numberInput, p_item);
    view_addComponent(p_view, p_numberInput);

    Footer_s *p_footer = gui_app_getFooter();
    Button_s *p_footerButton = &p_footer->button;

    keynav_up(p_footerButton, &p_numberInput->decreaseButton);
    keynav_down(&p_numberInput->decreaseButton, p_footerButton);
    keynav_down(&p_numberInput->increaseButton, p_footerButton);

    footer_setOnReleased(p_footer, setup_view_navigateBackTo);
    base_setFocus(p_footerButton, true);
}

static void iv_valueChanged(NumberInput_s *p_numberInput)
{
    measurement_setup_setSampleInterval(p_numberInput->value);
}
