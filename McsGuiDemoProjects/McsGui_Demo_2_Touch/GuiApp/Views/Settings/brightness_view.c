#include "brightness_view.h"

#include "display_api.h"

#include "gui_app.h"
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

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    Slider_s *p_slider = slider_newInit();
    slider_setValue(p_slider, gui_app_getDisplayBrightness());
    slider_setStep(p_slider, 10);
    slider_setOnValueChanged(p_slider, bv_sliderValueChanged);
    slider_setLeftColor(p_slider, COLOR_ACCENT_BLUE);
    base_addNewInitAnchor(p_slider);
    anchor_setCenterInParent(p_slider, p_pane);
    view_addComponent(p_view, p_slider);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BUTTON_ARROW_BACK, settings_view_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);
}

static void bv_sliderValueChanged(Slider_s *p_slider)
{
    display_setBacklight(p_slider->value);
    gui_app_setDisplayBrightness(p_slider->value);
}
