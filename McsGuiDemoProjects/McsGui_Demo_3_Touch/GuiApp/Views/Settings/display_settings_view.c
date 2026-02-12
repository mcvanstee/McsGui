#include "display_settings_view.h"

#include "display_api.h"

#include "gui_app.h"
#include "gui_custom_components.h"
#include "gui_settings.h"

#include "settings_view.h"
#include "calibrate_touch_view.h"

#define GROUP_BOX_LARGE_WIDTH 416
#define GROUP_BOX_SMALL_WIDTH ((GROUP_BOX_LARGE_WIDTH / 2) - 5)
#define GROUP_BOX_HEIGHT 110


static void dsv_create(View_s *p_view);
static void dsv_addBrightnessContent(GroupBox_s *p_displayGB);
static void dsv_sliderValueChanged(Slider_s *p_slider);
static void dsv_navigateBack(void);

void display_settings_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), dsv_create);
}

static void dsv_create(View_s *p_view)
{
    gui_app_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setDimensions(p_item, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT);
    view_addComponent(p_view, p_item);

    GroupBox_s *p_brightnessGB = group_box_newInitTitleSize(
            FILE_KEY_TITLE_BRIGHTNESS, GROUP_BOX_LARGE_WIDTH, GROUP_BOX_HEIGHT);
    base_addNewInitAnchor(p_brightnessGB);
    anchor_setTopAnchor(p_brightnessGB, p_item, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_brightnessGB, p_item, Gui_Anchor_Left);
    anchor_setTopMargin(p_brightnessGB, 20);
    anchor_setLeftMargin(p_brightnessGB, 10);
    dsv_addBrightnessContent(p_brightnessGB);
    view_addComponent(p_view, p_brightnessGB);

    GroupBox_s *p_calibrateTouchGB = group_box_newInitTitleSize(
            FILE_KEY_TITLE_CALIBRATE_TOUCH, GROUP_BOX_LARGE_WIDTH, GROUP_BOX_HEIGHT);
    base_addNewInitAnchor(p_calibrateTouchGB);
    anchor_setTopAnchor(p_calibrateTouchGB, p_brightnessGB, Gui_Anchor_Bottom);
    anchor_setLeftAnchor(p_calibrateTouchGB, p_brightnessGB, Gui_Anchor_Left);
    anchor_setTopMargin(p_calibrateTouchGB, 20);
    view_addComponent(p_view, p_calibrateTouchGB);

    ButtonCustom_s *p_calibrateButton = button_custom_newInit();
    base_setDimensions(p_calibrateButton, 150, 36);
    button_custom_setText(p_calibrateButton, "Calibrate");
    button_custom_setFont(p_calibrateButton, FONT_KEY_ROBOTO_16_R_DEFAULT_TEXT);
    button_setOnReleasedEvent(&p_calibrateButton->button, calibrate_touch_view_navigateTo);
    button_custom_setBorderColor(p_calibrateButton, COLOR_ACCENT_RED);
    button_custom_setColor(p_calibrateButton, COLOR_BACKGROUND);
    button_custom_setBorderThickness(p_calibrateButton, 1);
    anchor_setCenterInParent(p_calibrateButton, p_calibrateTouchGB);
    group_box_addComponent(p_calibrateTouchGB, p_calibrateButton);

    Button_s *p_backButton = button_new();
    button_initBmp(p_backButton, FILE_KEY_ICON_BACK);
    button_setOnReleasedEvent(p_backButton, dsv_navigateBack);
    base_addNewInitTouch(p_backButton);
    base_setDimensions(p_backButton, 50, 50);
    base_addNewInitAnchor(p_backButton);
    anchor_setBottomAnchor(p_backButton, p_item, Gui_Anchor_Bottom);
    anchor_setRightAnchor(p_backButton, p_item, Gui_Anchor_Right);
    anchor_setBottomMargin(p_backButton, 5);
    anchor_setRightMargin(p_backButton, 10);
    view_addComponent(p_view, p_backButton);
}

static void dsv_addBrightnessContent(GroupBox_s *p_brightnessGB)
{
    Slider_s *p_slider = slider_newInit();
    slider_setValue(p_slider, settings_getDisplayBrightness());
    slider_setStep(p_slider, 10);
    slider_setOnValueChanged(p_slider, dsv_sliderValueChanged);
    slider_setLeftColor(p_slider, COLOR_ACCENT_RED);
    base_addNewInitAnchor(p_slider);
    anchor_setCenterInParent(p_slider, p_brightnessGB);
    group_box_addComponent(p_brightnessGB, p_slider);
}

static void dsv_sliderValueChanged(Slider_s *p_slider)
{
    display_setBacklight(p_slider->value);
    settings_setDisplayBrightness(p_slider->value);
}

static void dsv_navigateBack(void)
{
    settings_save();
    settings_view_navigateTo();
}
