#include "measurement_view.h"

#include <stddef.h>
#include <stdio.h>

#include "gui_app.h"
#include "gui_custom_components.h"
#include "main.h"

#include "main_view.h"

#define MV_TEMP_TEXT_BLOCK_ID 1

static void msmv_create(View_s *p_view);
static void msnv_updateTemp(View_s *p_view, GuiEvent_s *p_event);
static void msnv_setTemp(TextBlock_s *p_textBlock);
static float celsiusToFahrenheit(float celsius);


void measurement_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, msmv_create);
}

static void msmv_create(View_s *p_view)
{
    p_view->handleEvent = msnv_updateTemp;
    header_setTitle(FILE_KEY_TITLE_MEASUREMENT);

    Pane_s *p_pane = pane_newInit();
    view_addComponent(p_view, p_pane);

    Label_s *p_tempLabel = label_newInit();
    label_initBmp(p_tempLabel, FILE_KEY_TEXT_PANE_INTERN_TEMP);
    base_addNewInitAnchor(p_tempLabel);
    anchor_setCenterInParent(p_tempLabel, p_pane);
    anchor_setRightMargin(p_tempLabel, 50);
    gui_translate(p_tempLabel);
    theme_setTheme(p_tempLabel);
    view_addComponent(p_view, p_tempLabel);

    TextBlock_s *p_tempTextBlock = textblock_newInit();
    textblock_initTextSize(p_tempTextBlock, "0", 55, 30);
    textblock_setFont(p_tempTextBlock, theme_getDefaultFont());
    base_setId(p_tempTextBlock, MV_TEMP_TEXT_BLOCK_ID);
    base_setBackground(&p_tempTextBlock->base, theme_getPaneColor());
    base_setTransparent(p_tempTextBlock, false);
    base_setHorizontalAlignment(&p_tempTextBlock->base, Gui_Align_Right);
    base_addNewInitAnchor(p_tempTextBlock);
    anchor_setLeftAnchor(p_tempTextBlock, p_tempLabel, Gui_Anchor_Right);
    anchor_setVerticalCenter(p_tempTextBlock, p_tempLabel);
    msnv_setTemp(p_tempTextBlock);
    view_addComponent(p_view, p_tempTextBlock);

    const file_key_e tempUnitKey = (TemperatureUnit_Celsius == g_guiApp.temperatureUnit) ?
            FILE_KEY_TEXT_PANE_DEG_CEL : FILE_KEY_TEXT_PANE_DEG_FAR;

    Label_s *p_tempUnitLabel = label_newInit();
    label_initBmp(p_tempUnitLabel, tempUnitKey);
    theme_setTheme(p_tempUnitLabel);
    base_addNewInitAnchor(p_tempUnitLabel);
    anchor_setLeftAnchor(p_tempUnitLabel, p_tempTextBlock, Gui_Anchor_Right);
    anchor_setVerticalCenter(p_tempUnitLabel, p_tempTextBlock);
    anchor_setLeftMargin(p_tempUnitLabel, 5);
    view_addComponent(p_view, p_tempUnitLabel);

    Row_s *p_footer = gui_addFooterButtonRow(p_view);
    gui_addFooterButton(p_footer, FILE_KEY_ICON_BUTTON_ARROW_BACK, mainview_navigateTo);
    gui_addFooterSpacer(p_footer);
    gui_addFooterSpacer(p_footer);
}

static void msnv_updateTemp(View_s *p_view, GuiEvent_s *p_event)
{
    if (CUSTOM_GUI_EVENT_MEASREMANT_READY == p_event->event)
    {
        TextBlock_s *p_tempTextBlock = (TextBlock_s *)view_getComponentById(p_view, MV_TEMP_TEXT_BLOCK_ID);
        msnv_setTemp(p_tempTextBlock);
        base_display(&p_tempTextBlock->base);
    }
}

static void msnv_setTemp(TextBlock_s *p_textBlock)
{
    float temp = getAdcTemp();

    if (g_guiApp.temperatureUnit == TemperatureUnit_Fahrenheit)
    {
        temp = celsiusToFahrenheit(temp);
    }

    const int32_t tempInt = (int32_t)temp;
    const int32_t tempFrac = (int32_t)((temp - tempInt) * 10);
    sprintf(p_textBlock->text, "%ld.%ld", tempInt, tempFrac);
}

static float celsiusToFahrenheit(float celsius)
{
    return (celsius * 9.0f / 5.0f) + 32.0f;
}
