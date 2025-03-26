#include "calibrate_touch_view.h"

#include <math.h>
#include <stdio.h>

#include "gui_app.h"
#include "gui_custom_components.h"
#include "gui_settings.h"
#include "display_api.h"
#include "touch_driver.h"
#include "fonts.h"
#include "utils_def.h"

#include "main_view.h"

#define CTV_CALIBRATION_POINT_OFFSET 50
#define CTV_CALIBRATION_POINT_RANGE 20

#define CTV_BACKGROUND_COLOR 0xFFFFFFU
#define CTV_CROSSHAIR_COLOR 0xFF0000U

#define CTV_CROSSHAIR_SIZE 30
#define CTV_TOLERANCE 10

#define CTB_POINT_TEXTBLOCK_ID 1
#define CTB_ADC_VALUES_TEXTBLOCK_ID 2
#define CTB_EXIT_BUTTON_TEXT_ID 3

const static GuiPoint_s p_1 = {CTV_CALIBRATION_POINT_OFFSET, CTV_CALIBRATION_POINT_OFFSET};
const static GuiPoint_s p_2 = {STYLE_DISPLAY_WIDTH - CTV_CALIBRATION_POINT_OFFSET, CTV_CALIBRATION_POINT_OFFSET};
const static GuiPoint_s p_3 = {CTV_CALIBRATION_POINT_OFFSET, STYLE_DISPLAY_HEIGHT - CTV_CALIBRATION_POINT_OFFSET};
const static GuiPoint_s p_4 = {STYLE_DISPLAY_WIDTH - CTV_CALIBRATION_POINT_OFFSET, STYLE_DISPLAY_HEIGHT - CTV_CALIBRATION_POINT_OFFSET};

static void ctv_create(View_s *p_view);
static void ctv_createCalibrationView(void);
static void cvt_drawCalibrationCrosshair(uint16_t x, uint16_t y, Color_t color);
static void cvt_handleEvent(View_s *p_view, GuiEvent_s *p_event);
static void cvt_handlePressed(GuiPoint_s pointPressed);
static void cvt_updateTouchPointValues(View_s *p_view, GuiPoint_s pointPressed);
static void cvt_showCalibrationResult(const bool passed);
static TouchCalibrationValues_s cvt_calculateCalibrationValues(void);
static void cvt_saveCalibrationValues(void);
static void cvt_nextCalibrationPoint(GuiPoint_s pointPressed, GuiPoint_s previousPoint, GuiPoint_s nextPoint);
static float_t cvt_calculateGain(float_t p1, float_t p2, float_t p_pressed_1, float_t p_pressed_2);
static float_t cvt_calculateOffset(float_t p1, float_t p2, float_t p_pressed_1, float_t p_pressed_2);
static bool cvt_validatePoint(GuiPoint_s pointCrosshair, GuiPoint_s pointPressed);
static void cvt_exitCalibration(void *p_baseComponent);

static GuiPoint_s m_calibrationPoints[3];
static uint8_t m_calibrationPointIndex = 0;


void calibrate_touch_view_navigateTo(void)
{
	view_navigateTo(&g_guiApp.view, ctv_create);
}

static void ctv_create(View_s *p_view)
{
	view_setHandleEvent(p_view, cvt_handleEvent);
	gui_app_setVisibiltyControlBar(false);
	touch_dr_resetCalibration();
	ctv_createCalibrationView();

	TextBlock_s *p_instructionTB = textblock_new();
	textblock_initTextPosSize(
			p_instructionTB, "Touch the crosshair with a stylus",
			0, 0, STYLE_DISPLAY_WIDTH, STYLE_DISPLAY_HEIGHT);
	textblock_setFont(p_instructionTB, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_PANE_TEXT);

	TextBlock_s *p_pointTB = textblock_new();
	textblock_initText(p_pointTB, "(x, y) = (0, 0)");
	textblock_setFont(p_pointTB, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_PANE_TEXT);
	base_setBackground(p_pointTB, CTV_BACKGROUND_COLOR);
	base_setWidth(p_pointTB, 200);
	base_setId(p_pointTB, CTB_POINT_TEXTBLOCK_ID);
	base_addNewInitAnchor(p_pointTB);
	anchor_setCenterInParent(p_pointTB, p_instructionTB);
	anchor_setTopMargin(p_pointTB, 20);

	TextBlock_s *p_adcValuesTB = textblock_new();
	textblock_initText(p_adcValuesTB, "ADC (x,y,z): (0, 0, 0)");
	textblock_setFont(p_adcValuesTB, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_PANE_TEXT);
	base_setBackground(p_adcValuesTB, CTV_BACKGROUND_COLOR);
	base_setWidth(p_adcValuesTB, 200);
	base_setId(p_adcValuesTB, CTB_ADC_VALUES_TEXTBLOCK_ID);
	base_addNewInitAnchor(p_adcValuesTB);
	anchor_setTopAnchor(p_adcValuesTB, p_pointTB, Gui_Anchor_Bottom);
	anchor_setHorizontalCenter(p_adcValuesTB, p_pointTB);

	TextBlock_s *p_button = textblock_new();
	textblock_initText(p_button, "Exit");
	textblock_setFont(p_button, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_PANE_TEXT);
	base_setId(p_button, CTB_EXIT_BUTTON_TEXT_ID);
	base_setWidth(p_button, 100);
	base_setHeight(p_button, 20);
	base_addNewInitAnchor(p_button);
	base_setVisible(p_button, false);
	base_setBackground(p_button, COLOR_BACKGROUND);
	base_addNewInitTouch(p_button);
	touch_setOnPressed(p_button->base.p_touch, cvt_exitCalibration);
	anchor_setTopAnchor(p_button, p_adcValuesTB, Gui_Anchor_Bottom);
	anchor_setHorizontalCenter(p_button, p_adcValuesTB);
	anchor_setTopMargin(p_button, 60);

	view_addComponent(p_view, p_instructionTB);
	view_addComponent(p_view, p_pointTB);
	view_addComponent(p_view, p_adcValuesTB);
	view_addComponent(p_view, p_button);
}

static void ctv_createCalibrationView(void)
{
	Rectangle_s background;
	rectangle_initFillPosSize(&background, CTV_BACKGROUND_COLOR , 0, 0, STYLE_DISPLAY_WIDTH, STYLE_DISPLAY_HEIGHT);
	base_display(&background);

	m_calibrationPointIndex = 0;
	cvt_drawCalibrationCrosshair(p_1.x, p_1.y, CTV_CROSSHAIR_COLOR);
}

static void cvt_drawCalibrationCrosshair(uint16_t x, uint16_t y, Color_t color)
{
	Rectangle_s horizontalLine;
	rectangle_initFillPosSize(&horizontalLine, color, x - (CTV_CROSSHAIR_SIZE / 2), y, CTV_CROSSHAIR_SIZE, 1);
	base_display(&horizontalLine);

	Rectangle_s verticalLine;
	rectangle_initFillPosSize(&verticalLine, color, x, y - (CTV_CROSSHAIR_SIZE / 2), 1, CTV_CROSSHAIR_SIZE);
	base_display(&verticalLine);
}

static void cvt_handleEvent(View_s *p_view, GuiEvent_s *p_event)
{
	if (p_event->event == GUI_EVENT_TOUCH_ON_PRESSED)
	{
		GuiPoint_s pointPressed = {
				p_event->eventArgs[0] + (p_event->eventArgs[1] << 8),
				p_event->eventArgs[2] + (p_event->eventArgs[3] << 8) };

		cvt_updateTouchPointValues(p_view, pointPressed);
		cvt_handlePressed(pointPressed);
	}
	else if ((m_calibrationPointIndex >= 4) && (p_event->event == GUI_EVENT_TOUCH_PRESSED))
	{
		GuiPoint_s pointPressed = {
				p_event->eventArgs[0] + (p_event->eventArgs[1] << 8),
				p_event->eventArgs[2] + (p_event->eventArgs[3] << 8) };

		display_drawRectangleFill(pointPressed.x + 1, pointPressed.y + 1, 3, 3, 0x0000FF);
	}
}

static void cvt_handlePressed(GuiPoint_s pointPressed)
{
	if (m_calibrationPointIndex == 0)
	{
		cvt_nextCalibrationPoint(pointPressed, p_1, p_2);
	}
	else if (m_calibrationPointIndex == 1)
	{
		cvt_nextCalibrationPoint(pointPressed, p_2, p_3);
	}
	else if (m_calibrationPointIndex == 2)
	{
		cvt_nextCalibrationPoint(pointPressed, p_3, p_4);
		const TouchCalibrationValues_s calibrationValues = cvt_calculateCalibrationValues();
		touch_dr_setCalibrationValues(&calibrationValues);
	}
	else if (m_calibrationPointIndex == 3)
	{
		cvt_drawCalibrationCrosshair(p_4.x, p_4.y, CTV_BACKGROUND_COLOR);
		m_calibrationPointIndex++;
		const bool valid = cvt_validatePoint(p_4, pointPressed);
		cvt_showCalibrationResult(valid);

		if (valid)
		{
			cvt_saveCalibrationValues();

			TextBlock_s *p_buttonText = (TextBlock_s *)view_getComponentById(&g_guiApp.view, CTB_EXIT_BUTTON_TEXT_ID);
			base_setVisible(p_buttonText, true);
			base_display(p_buttonText);
		}
		else
		{
			touch_dr_resetCalibration();
		}
	}
	else
	{
	}
}

static void cvt_exitCalibration(void *p_baseComponent)
{
    UNUSED(p_baseComponent);
	gui_app_setVisibiltyControlBar(true);
	gui_app_drawBackground();
	mainview_navigateTo();
}

static void cvt_nextCalibrationPoint(GuiPoint_s pointPressed, GuiPoint_s previousPoint, GuiPoint_s nextPoint)
{
	m_calibrationPoints[m_calibrationPointIndex] = pointPressed;
	m_calibrationPointIndex++;
	cvt_drawCalibrationCrosshair(previousPoint.x, previousPoint.y, CTV_BACKGROUND_COLOR);
	cvt_drawCalibrationCrosshair(nextPoint.x, nextPoint.y, CTV_CROSSHAIR_COLOR);
}

static void cvt_updateTouchPointValues(View_s *p_view, GuiPoint_s pointPressed)
{
	TextBlock_s *p_pointTB = (TextBlock_s *)view_getComponentById(p_view, CTB_POINT_TEXTBLOCK_ID);
	snprintf(
			p_pointTB->text,
			GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH_INC_NULL,
			"(x, y) = (%d, %d)",
			pointPressed.x, pointPressed.y);
	base_display(p_pointTB);

	TouchADCValues_s adcValues = touch_dr_getAdcValues();

	TextBlock_s *p_adcValuesTB = (TextBlock_s *)view_getComponentById(p_view, CTB_ADC_VALUES_TEXTBLOCK_ID);
	snprintf(
			p_adcValuesTB->text,
			GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH_INC_NULL,
			"ADC (x,y,z): (%d, %d, %d)",
			adcValues.x, adcValues.y, adcValues.z);
	base_display(p_adcValuesTB);
}

static void cvt_showCalibrationResult(const bool passed)
{
	TextBlock_s resultTB;
	textblock_initTextPos(&resultTB,
			(passed ? "Calibration successful" : "Calibration failed"),
			0, 150);
	base_setWidth(&resultTB, STYLE_DISPLAY_WIDTH);
	base_setBackground(&resultTB, CTV_BACKGROUND_COLOR);
	textblock_setFont(&resultTB, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_PANE_TEXT);
	base_display(&resultTB);
}

static TouchCalibrationValues_s cvt_calculateCalibrationValues(void)
{
	const float_t x1 = p_1.x;
	const float_t x2 = p_2.x;
	const float_t y1 = p_1.y;
	const float_t y2 = p_3.y;

	TouchCalibrationValues_s calibrationValues = {0};
	calibrationValues.gainX = cvt_calculateGain(x1, x2, m_calibrationPoints[0].x, m_calibrationPoints[1].x);
	calibrationValues.offsetX = cvt_calculateOffset(x1, x2, m_calibrationPoints[0].x, m_calibrationPoints[1].x);
	calibrationValues.gainY = cvt_calculateGain(y1, y2, m_calibrationPoints[0].y, m_calibrationPoints[2].y);
	calibrationValues.offsetY = cvt_calculateOffset(y1, y2, m_calibrationPoints[0].y, m_calibrationPoints[2].y);

	return calibrationValues;
}

static void cvt_saveCalibrationValues(void)
{
	TouchCalibrationValues_s calibrationValues = cvt_calculateCalibrationValues();

	GuiSettings_s settings = settings_getSettings();
	settings.gainX = calibrationValues.gainX;
	settings.gainY = calibrationValues.gainY;
	settings.offsetX = calibrationValues.offsetX;
	settings.offsetY = calibrationValues.offsetY;
	settings_setSettings(settings);
	settings_save();
}

static bool cvt_validatePoint(GuiPoint_s pointCrosshair, GuiPoint_s pointPressed)
{
	return (fabs(pointCrosshair.x - pointPressed.x) < CTV_TOLERANCE) &&
		   (fabs(pointCrosshair.y - pointPressed.y) < CTV_TOLERANCE);
}

static float_t cvt_calculateGain(float_t p1, float_t p2, float_t p_pressed_1, float_t p_pressed_2)
{
	return (p1 - p2) / (p_pressed_1 - p_pressed_2);
}

static float_t cvt_calculateOffset(float_t p1, float_t p2, float_t p_pressed_1, float_t p_pressed_2)
{
	return p1 - (p_pressed_1 * cvt_calculateGain(p1, p2, p_pressed_1, p_pressed_2));
}
