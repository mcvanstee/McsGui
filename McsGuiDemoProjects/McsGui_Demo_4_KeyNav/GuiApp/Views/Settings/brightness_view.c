#include "brightness_view.h"

#include "display_api.h"

#include "gui_app.h"
#include "gui_custom_components.h"

#include "settings_view.h"

static void bv_create(View_s *p_view);
static void bv_sliderValueChanged(Slider_s *p_slider);


void brightness_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, bv_create);
}

static void bv_create(View_s *p_view)
{
    header_setTitle(FILE_KEY_TITLE_BRIGHTNESS);

    gui_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setSize(p_item, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);

    Slider_s *p_slider = slider_newInit();
    slider_setValue(p_slider, g_guiApp.displayBrightness);
    slider_setStep(p_slider, 10);
    slider_setOnValueChanged(p_slider, bv_sliderValueChanged);
    base_addNewInitAnchor(p_slider);
    anchor_setCenterInParent(p_slider, p_item);
    view_addComponent(p_view, p_slider);

    footer_setOnReleased(&g_guiApp.footer, settings_view_navigateBackTo);

    keynav_up(&g_guiApp.footer.button, &p_slider->minusButton);
    keynav_down(&p_slider->minusButton, &g_guiApp.footer.button);
    keynav_down(&p_slider->plusButton, &g_guiApp.footer.button);

    base_setFocus(&g_guiApp.footer.button, true);
}

static void bv_sliderValueChanged(Slider_s *p_slider)
{
    display_setBacklight(p_slider->value);
    g_guiApp.displayBrightness = p_slider->value;
}
