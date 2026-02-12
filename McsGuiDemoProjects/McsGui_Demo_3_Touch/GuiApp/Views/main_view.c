#include "main_view.h"

#include <stdio.h>

#include "gui_app.h"
#include "gui_custom_components.h"
#include "main.h"

#include "stm32l4xx_hal.h"

extern RTC_HandleTypeDef hrtc;

#define PANE_WIDTH 203
#define PANE_1_HEIGHT ((STYLE_DISPLAY_HEIGHT / 2) - 10)
#define PANE_2_HEIGHT ((STYLE_DISPLAY_HEIGHT / 2) - 15)

#define MV_TEMP_TEXTBLOCK_ID 1
#define MV_TIME_TEXTBLOCK_ID 2
#define MV_DATE_TEXTBLOCK_ID 3

static void mv_create(View_s *p_view);

static void mv_tempPaneAddContent(Pane_s *p_pane);
static void mv_timePaneAddContent(Pane_s *p_pane);
static void mv_historyPaneAddContent(Pane_s *p_pane);
static void mv_infoPaneAddContent(Pane_s *p_pane);

static void mv_setTime(TextBlock_s *p_textBlock, RTC_TimeTypeDef *p_time);
static void mv_setDate(TextBlock_s *p_textBlock, RTC_DateTypeDef *p_date);

static void mv_updateDateTime(const bool forceUpdate);
static void mv_updateTemp(View_s *p_view, GuiEvent_s *p_event);
static void mv_setTemp(TextBlock_s *p_textBlock);


void mainview_navigateTo(void)
{
	view_navigateTo(gui_app_getView(), mv_create);
}

static void mv_create(View_s *p_view)
{
    gui_app_clearView();
	view_setHandleEvent(p_view, mv_updateTemp);

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setDimensions(p_item, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT);
    view_addComponent(p_view, p_item);

	Pane_s *p_tempPane = pane_newInit();
	pane_setBorderPane(p_tempPane, true);
	base_setDimensions(&p_tempPane->base, PANE_WIDTH, PANE_1_HEIGHT);
    base_addNewInitAnchor(p_tempPane);
    anchor_setTopAnchor(p_tempPane, p_item, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_tempPane, p_item, Gui_Anchor_Left);
    anchor_setTopMargin(p_tempPane, 10);
    anchor_setLeftMargin(p_tempPane, 10);
	view_addComponent(p_view, p_tempPane);

	Pane_s *p_paneHistory = pane_newInit();
	base_setDimensions(&p_paneHistory->base, PANE_WIDTH, PANE_1_HEIGHT);
	pane_setBorderPane(p_paneHistory, true);
	base_addNewInitAnchor(p_paneHistory);
	anchor_setLeftAnchor(p_paneHistory, p_tempPane, Gui_Anchor_Left);
	anchor_setTopAnchor(p_paneHistory, p_tempPane, Gui_Anchor_Bottom);
	view_addComponent(p_view, p_paneHistory);

	Pane_s *p_timePane = pane_newInit();
	base_setDimensions(&p_timePane->base, PANE_WIDTH, PANE_2_HEIGHT);
	base_addNewInitAnchor(p_timePane);
	anchor_setLeftAnchor(p_timePane, p_tempPane, Gui_Anchor_Right);
	anchor_setTopAnchor(p_timePane, p_tempPane, Gui_Anchor_Top);
	anchor_setLeftMargin(p_timePane, 11);
	view_addComponent(p_view, p_timePane);

	Pane_s *p_infoPane = pane_newInit();
	base_setDimensions(&p_infoPane->base, PANE_WIDTH, PANE_2_HEIGHT);
	base_addNewInitAnchor(p_infoPane);
	anchor_setLeftAnchor(p_infoPane, p_tempPane, Gui_Anchor_Right);
	anchor_setTopAnchor(p_infoPane, p_timePane, Gui_Anchor_Bottom);
	anchor_setLeftMargin(p_infoPane, 11);
	anchor_setTopMargin(p_infoPane, 10);
	view_addComponent(p_view, p_infoPane);

	mv_tempPaneAddContent(p_tempPane);
	mv_timePaneAddContent(p_timePane);
	mv_historyPaneAddContent(p_paneHistory);
	mv_infoPaneAddContent(p_infoPane);
}

static void mv_tempPaneAddContent(Pane_s *p_pane)
{
	Row_s *p_row = row_newInit();
	row_setSpacing(p_row, 10);
	base_addNewInitAnchor(p_row);
	anchor_setCenterInParent(p_row, p_pane);
	pane_addComponent(p_pane, p_row);

	Label_s *p_tempLabel = label_newInit();
	label_initBmp(p_tempLabel, FILE_KEY_ICON_THERMOMETER);
	row_addComponent(p_row, p_tempLabel);

	TextBlock_s *p_tempTextBlock = textblock_newInit();
    textblock_initTextSize(p_tempTextBlock, "-", 40, 24);
    textblock_setFont(p_tempTextBlock, FONT_KEY_ROBOTO_18_R_DEFAULT_TEXT);
    textblock_setFontBackColor(p_tempTextBlock, COLOR_BACKGROUND);
    textblock_setHorizontalTextAlignment(p_tempTextBlock, Text_Align_Right);
    base_setTransparent(p_tempTextBlock, false);
    base_setId(p_tempTextBlock, MV_TEMP_TEXTBLOCK_ID);
    mv_setTemp(p_tempTextBlock);
    row_addComponent(p_row, p_tempTextBlock);

    const file_key_e tempUnitKey = (TemperatureUnit_Celsius == settings_getTemperatureUnit()) ?
            FILE_KEY_TEXT_DEG_CEL : FILE_KEY_TEXT_DEG_FAR;

    Label_s *p_tempUnitLabel = label_newInit();
    label_initBmp(p_tempUnitLabel, tempUnitKey);
    base_setHeight(p_tempUnitLabel, 24);
    base_setTopPadding(p_tempUnitLabel, 2);
    row_addComponent(p_row, p_tempUnitLabel);
}

static void mv_timePaneAddContent(Pane_s *p_pane)
{
	Column_s *p_columnLeft = column_newInit();
	column_setSpacing(p_columnLeft, 8);
	base_addNewInitAnchor(p_columnLeft);
	anchor_setLeftAnchor(p_columnLeft, p_pane, Gui_Anchor_Left);
	anchor_setTopAnchor(p_columnLeft, p_pane, Gui_Anchor_Top);
	anchor_setLeftMargin(p_columnLeft, 10);
	anchor_setTopMargin(p_columnLeft, 10);
	pane_addComponent(p_pane, p_columnLeft);

	Column_s *p_columnRight = column_newInit();
	column_setSpacing(p_columnRight, 8);
	base_addNewInitAnchor(p_columnRight);
	anchor_setLeftAnchor(p_columnRight, p_columnLeft, Gui_Anchor_Right);
	anchor_setTopAnchor(p_columnRight, p_columnLeft, Gui_Anchor_Top);
	anchor_setLeftMargin(p_columnRight, 10);
	pane_addComponent(p_pane, p_columnRight);

    RTC_DateTypeDef sDate = {0};
    RTC_TimeTypeDef sTime = {0};
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

	if (settings_getShowTime())
	{
		Label_s *p_timeLabel = label_newInit();
		label_initBmp(p_timeLabel, FILE_KEY_ICON_PANE_CLOCK);
		base_setHeight(p_timeLabel, 30);
		column_addComponent(p_columnLeft, p_timeLabel);

		TextBlock_s *p_timeTextBlock = textblock_newInit();
		textblock_setFont(p_timeTextBlock, FONT_KEY_ROBOTO_16_R_PANE_TEXT);
		textblock_setFontBackColor(p_timeTextBlock, COLOR_PANE);
		textblock_setHorizontalTextAlignment(p_timeTextBlock, Text_Align_Left);
		textblock_setTopTextPadding(p_timeTextBlock, 2);
		base_setTransparent(p_timeTextBlock, false);
		base_setId(p_timeTextBlock, MV_TIME_TEXTBLOCK_ID);
		base_setHeight(p_timeTextBlock, 30);
		column_addComponent(p_columnRight, p_timeTextBlock);

		mv_setTime(p_timeTextBlock, &sTime);
	}

	if (settings_getShowDate())
	{
		Label_s *p_dateLabel = label_newInit();
		label_initBmp(p_dateLabel, FILE_KEY_ICON_PANE_AGENDA);
		base_setHeight(p_dateLabel, 30);
		column_addComponent(p_columnLeft, p_dateLabel);

		TextBlock_s *p_dateTextBlock = textblock_newInit();
		textblock_setFont(p_dateTextBlock, FONT_KEY_ROBOTO_16_R_PANE_TEXT);
		textblock_setFontBackColor(p_dateTextBlock, COLOR_PANE);
		textblock_setHorizontalTextAlignment(p_dateTextBlock, Text_Align_Left);
		textblock_setTopTextPadding(p_dateTextBlock, 2);
		base_setTransparent(p_dateTextBlock, false);
		base_setId(p_dateTextBlock, MV_DATE_TEXTBLOCK_ID);
		base_setHeight(p_dateTextBlock, 30);
		column_addComponent(p_columnRight, p_dateTextBlock);

		mv_setDate(p_dateTextBlock, &sDate);
	}
}

static void mv_historyPaneAddContent(Pane_s *p_pane)
{
	Row_s *p_row = row_newInit();
	row_setSpacing(p_row, 5);
	base_addNewInitAnchor(p_row);
	anchor_setCenterInParent(p_row, p_pane);
	anchor_setLeftMargin(p_row, 15);
	pane_addComponent(p_pane, p_row);

	for (uint32_t i = 0; i < 5; i++)
	{
		Bar_s *p_bar = bar_newInit();
		row_addComponent(p_row, p_bar);

		if (i < 3)
		{
			bar_setLevel(p_bar, 95);
		}

		if (i == 3)
		{
			bar_setLevel(p_bar, 60);
		}

		if (i == 4)
		{
			bar_setLevel(p_bar, 78);
		}
	}

    TextBlock_s *p_maxTB = textblock_newInit();
    textblock_setFont(p_maxTB, FONT_KEY_ROBOTO_13_R_DEFAULT_TEXT);
    textblock_setText(p_maxTB, "100%");
    base_addNewInitAnchor(p_maxTB);
    anchor_setTopAnchor(p_maxTB, p_row, Gui_Anchor_Top);
    anchor_setRightAnchor(p_maxTB, p_row, Gui_Anchor_Left);
    anchor_setRightMargin(p_maxTB, 5);
    pane_addComponent(p_pane, p_maxTB);

    TextBlock_s *p_minTB = textblock_newInit();
    textblock_setFont(p_minTB, FONT_KEY_ROBOTO_13_R_DEFAULT_TEXT);
    textblock_setText(p_minTB, "0%");
    base_addNewInitAnchor(p_minTB);
    anchor_setBottomAnchor(p_minTB, p_row, Gui_Anchor_Bottom);
    anchor_setRightAnchor(p_minTB, p_row, Gui_Anchor_Left);
    anchor_setRightMargin(p_minTB, 5);
    pane_addComponent(p_pane, p_minTB);
}

static void mv_infoPaneAddContent(Pane_s *p_pane)
{
	Label_s *p_irlLogo = label_new();
	label_initBmp(p_irlLogo, FILE_KEY_IRL_LOGO_48);
	base_addNewInitAnchor(p_irlLogo);
	anchor_setLeftAnchor(p_irlLogo, p_pane, Gui_Anchor_Left);
	anchor_setTopAnchor(p_irlLogo, p_pane, Gui_Anchor_Top);
	anchor_setLeftMargin(p_irlLogo, 10);
	anchor_setTopMargin(p_irlLogo, 10);
	pane_addComponent(p_pane, p_irlLogo);

	Rectangle_s *p_irlBorder = rectangle_new();
	rectangle_initBorderSize(p_irlBorder, 50, 50, 1, COLOR_PANE);
	rectangle_setRadius(p_irlBorder, 3);
	base_addNewInitAnchor(p_irlBorder);
	anchor_setCenterInParent(p_irlBorder, p_irlLogo);
	pane_addComponent(p_pane, p_irlBorder);

    TextBlock_s *p_irlTB = textblock_newInit();
    textblock_setFont(p_irlTB, FONT_KEY_ROBOTO_16_R_PANE_TEXT);
    textblock_setText(p_irlTB, "IRL Software");
    base_addNewInitAnchor(p_irlTB);
    anchor_setLeftAnchor(p_irlTB, p_irlLogo, Gui_Anchor_Right);
    anchor_setTopAnchor(p_irlTB, p_irlLogo, Gui_Anchor_Top);
    anchor_setLeftMargin(p_irlTB, 5);
    pane_addComponent(p_pane, p_irlTB);

    TextBlock_s *p_mailTB = textblock_newInit();
    textblock_setFont(p_mailTB, FONT_KEY_ROBOTO_13_R_PANE_TEXT);
    textblock_setText(p_mailTB, "info@irlsoftware.nl");
    base_addNewInitAnchor(p_mailTB);
    anchor_setLeftAnchor(p_mailTB, p_irlLogo, Gui_Anchor_Right);
    anchor_setTopAnchor(p_mailTB, p_irlTB, Gui_Anchor_Bottom);
    anchor_setLeftMargin(p_mailTB, 5);
    anchor_setTopMargin(p_mailTB, 2);
    pane_addComponent(p_pane, p_mailTB);

    TextBlock_s *p_mcsguiTB = textblock_newInit();
    textblock_setFont(p_mcsguiTB, FONT_KEY_ROBOTO_16_R_PANE_TEXT);
    textblock_setText(p_mcsguiTB, "McsGui");
    base_addNewInitAnchor(p_mcsguiTB);
    anchor_setLeftAnchor(p_mcsguiTB, p_irlLogo, Gui_Anchor_Left);
    anchor_setTopAnchor(p_mcsguiTB, p_irlLogo, Gui_Anchor_Bottom);
    anchor_setTopMargin(p_mcsguiTB, 10);
    pane_addComponent(p_pane, p_mcsguiTB);

    TextBlock_s *p_versionTB = textblock_newInit();
    textblock_setFont(p_versionTB, FONT_KEY_ROBOTO_13_R_PANE_TEXT);
    snprintf(p_versionTB->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "V%d.%d.%d",
            MCSGUI_VERSION_MAJOR, MCSGUI_VERSION_MINOR, MCSGUI_VERSION_PATCH);
    base_addNewInitAnchor(p_versionTB);
    anchor_setLeftAnchor(p_versionTB, p_mcsguiTB, Gui_Anchor_Right);
    anchor_setBottomAnchor(p_versionTB, p_mcsguiTB, Gui_Anchor_Bottom);
    anchor_setBottomMargin(p_versionTB, 3);
    anchor_setLeftMargin(p_versionTB, 7);
    pane_addComponent(p_pane, p_versionTB);
}

static void mv_updateTemp(View_s *p_view, GuiEvent_s *p_event)
{
    if (CUSTOM_GUI_EVENT_MEASREMANT_READY == p_event->event)
    {
    	TextBlock_s *p_tempTextBlock = (TextBlock_s *)view_getComponentById(p_view, MV_TEMP_TEXTBLOCK_ID);
        mv_setTemp(p_tempTextBlock);
        base_display(&p_tempTextBlock->base);
    }

    if (CUSTOM_GUI_EVENT_UPDATE_DATE_TIME == p_event->event)
    {
    	mv_updateDateTime(false);
	}
}

static void mv_setTemp(TextBlock_s *p_textBlock)
{
    float_t temp = getAdcTemp();
    unit_converter_getTemperatureStr(
            p_textBlock->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, temp, settings_getTemperatureUnit());
}

static void mv_updateDateTime(const bool forceUpdate)
{
    static int32_t lastMinute = -1;

    RTC_DateTypeDef sDate = {0};
    RTC_TimeTypeDef sTime = {0};
    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

    if (forceUpdate || (lastMinute != (int32_t)sTime.Minutes))
    {
        lastMinute = sTime.Minutes;

        View_s *p_view = gui_app_getView();

        if (settings_getShowTime())
        {
            TextBlock_s *p_timeTextBlock = (TextBlock_s*)view_getComponentById(p_view, MV_TIME_TEXTBLOCK_ID);

            if (p_timeTextBlock != NULL)
            {
                mv_setTime(p_timeTextBlock, &sTime);
                base_display(p_timeTextBlock);
            }
        }

        if (settings_getShowDate())
        {
            TextBlock_s *p_dateTextBlock = (TextBlock_s*)view_getComponentById(p_view, MV_DATE_TEXTBLOCK_ID);

            if (p_dateTextBlock != NULL)
            {
                mv_setDate(p_dateTextBlock, &sDate);
                base_display(p_dateTextBlock);
            }
        }
    }
}

static void mv_setTime(TextBlock_s *p_textBlock, RTC_TimeTypeDef *p_time)
{
	snprintf(p_textBlock->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH,
	        "%02d:%02d", p_time->Hours, p_time->Minutes);
}

static void mv_setDate(TextBlock_s *p_textBlock, RTC_DateTypeDef *p_date)
{
	snprintf(p_textBlock->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH,
	        "%02d-%02d-%04d", p_date->Date, p_date->Month, (p_date->Year + 2000));
}

