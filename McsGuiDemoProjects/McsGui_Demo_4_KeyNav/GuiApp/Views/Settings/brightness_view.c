#include "brightness_view.h"

#include "display_api.h"

#include "gui_app.h"
#include "gui_app_settings.h"
#include "gui_custom_components.h"

#include "settings_view.h"

static void bv_create(View_s *p_view);
static void bv_sliderValueChanged(Slider_s *p_slider);


void brightness_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), bv_create);
}

static void bv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_BRIGHTNESS);

    gui_app_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setDimensions(p_item, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);

    Slider_s *p_slider = slider_newInit();
    slider_setValue(p_slider, settings_getDisplayBrightness());
    slider_setStep(p_slider, 10);
    slider_setOnValueChanged(p_slider, bv_sliderValueChanged);
    base_addNewInitAnchor(p_slider);
    anchor_setCenterInParent(p_slider, p_item);
    view_addComponent(p_view, p_slider);

    Footer_s *p_footer = gui_app_getFooter();
    Button_s *p_footerButton = &p_footer->button;

    footer_setOnReleased(p_footer, settings_view_navigateBackTo);

    keynav_up(p_footerButton, &p_slider->minusButton);
    keynav_down(&p_slider->minusButton, p_footerButton);
    keynav_down(&p_slider->plusButton, p_footerButton);

    base_setFocus(p_footerButton, true);
}

static void bv_sliderValueChanged(Slider_s *p_slider)
{
    display_setBacklight(p_slider->value);
    settings_setDisplayBrightness(p_slider->value);
}
