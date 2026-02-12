#include "measurement_view.h"

#include <stddef.h>
#include <stdio.h>

#include "main.h"
#include "gui_app.h"
#include "gui_app_settings.h"
#include "gui_utils_unit_converter.h"

#include "main_view.h"

#define MV_TEMP_TEXT_BLOCK_ID 1

static void msmv_create(View_s *p_view);
static void msnv_updateTemp(View_s *p_view, GuiEvent_s *p_event);
static void msnv_setTemp(TextBlock_s *p_textBlock);
static font_key_e msmv_getFontKey(const float_t temperature);


void measurement_view_navigateTo(void)
{
    view_navigateTo(gui_app_getView(), msmv_create);
}

static void msmv_create(View_s *p_view)
{
    p_view->handleEvent = msnv_updateTemp;
    header_setTitle(FILE_KEY_TITLE_MEASUREMENT);
    gui_app_clearView();

    Item_s *p_item = item_newInit();
    base_setDimensions(p_item, STYLE_VIEW_WIDTH, STYLE_VIEW_HEIGHT);
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    view_addComponent(p_view, p_item);

    Label_s *p_tempLabel = label_newInit();
    label_initBmp(p_tempLabel, FILE_KEY_TEXT_INTERN_TEMP);
    base_addNewInitAnchor(p_tempLabel);
    anchor_setCenterInParent(p_tempLabel, p_item);
    anchor_setRightMargin(p_tempLabel, 50);
    gui_app_translate(p_tempLabel);
    theme_applyThemeProperty(p_tempLabel);
    view_addComponent(p_view, p_tempLabel);

    TextBlock_s *p_tempTextBlock = textblock_newInit();
    textblock_initTextSize(p_tempTextBlock, "0", 55, 30);
    textblock_setFont(p_tempTextBlock, theme_getDefaultFont());
    textblock_setFontBackColor(p_tempTextBlock, theme_getBackgroundColor());
    textblock_setHorizontalTextAlignment(p_tempTextBlock, Text_Align_Right);
    textblock_setTopTextPadding(p_tempTextBlock, 1);
    base_setTransparent(p_tempTextBlock, false);
    base_setId(p_tempTextBlock, MV_TEMP_TEXT_BLOCK_ID);
    base_addNewInitAnchor(p_tempTextBlock);
    anchor_setLeftAnchor(p_tempTextBlock, p_tempLabel, Gui_Anchor_Right);
    anchor_setVerticalCenter(p_tempTextBlock, p_tempLabel);

    msnv_setTemp(p_tempTextBlock);
    view_addComponent(p_view, p_tempTextBlock);

    Label_s *p_tempUnitLabel = label_newInit();
    label_initBmp(p_tempUnitLabel, unit_converter_getTemperatureUnitFileKey());
    theme_applyThemeProperty(p_tempUnitLabel);
    base_addNewInitAnchor(p_tempUnitLabel);
    anchor_setLeftAnchor(p_tempUnitLabel, p_tempTextBlock, Gui_Anchor_Right);
    anchor_setVerticalCenter(p_tempUnitLabel, p_tempTextBlock);
    anchor_setLeftMargin(p_tempUnitLabel, 5);
    view_addComponent(p_view, p_tempUnitLabel);

    Footer_s *p_footer = gui_app_getFooter();

    footer_setOnReleased(p_footer, mainview_navigateTo);
    base_setFocus(&p_footer->button, true);
}

static void msnv_updateTemp(View_s *p_view, GuiEvent_s *p_event)
{
    if (CUSTOM_GUI_EVENT_MEASUREMENT_READY == p_event->event)
    {
        TextBlock_s *p_tempTextBlock = (TextBlock_s *)view_getComponentById(p_view, MV_TEMP_TEXT_BLOCK_ID);
        msnv_setTemp(p_tempTextBlock);
        base_display(&p_tempTextBlock->base);
    }
}

static void msnv_setTemp(TextBlock_s *p_textBlock)
{
    float_t temp = getAdcTemp();
    unit_converter_getTemperatureStr(p_textBlock->text, TEXTBLOCK_MAX_STRING_LENGTH, temp);
    textblock_setFont(p_textBlock, msmv_getFontKey(temp));
}

static font_key_e msmv_getFontKey(const float_t temperature)
{
    const GuiTheme_e theme = theme_getGuiTheme();
    const uint32_t lowerLimit = measurement_setup_getLowerLimit();
    const uint32_t upperLimit = measurement_setup_getUpperLimit();

    if (theme == GuiTheme_Dark)
    {
        if (temperature < lowerLimit)
        {
            return FONT_KEY_TEXT_DARK_TEXT_ACCENT_BLUE;
        }
        else if (temperature > upperLimit)
        {
            return FONT_KEY_TEXT_DARK_TEXT_ACCENT_RED;
        }
        else
        {
            return FONT_KEY_TEXT_DARK;
        }
    }
    else
    {
        if (temperature < lowerLimit)
        {
            return FONT_KEY_TEXT_LIGHT_TEXT_ACCENT_BLUE;
        }
        else if (temperature > upperLimit)
        {
            return FONT_KEY_TEXT_LIGHT_TEXT_ACCENT_RED;
        }
        else
        {
            return FONT_KEY_TEXT_LIGHT;
        }
    }
}
