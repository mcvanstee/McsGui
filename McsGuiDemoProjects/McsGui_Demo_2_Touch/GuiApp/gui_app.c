#include "gui_app.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>

#include "external_display.h"
#include "display_api.h"
#include "gui_image.h"
#include "Graphics/gui_graphics.h"
#include "external_display.h"
#include "main_view.h"
#include "message_dialog.h"
#include "touch_driver.h"
#include "touch_api.h"
#include "sys_buttons.h"
#include "utils_array.h"
#include "main.h"
#include "ff.h"

#include "stm32l4xx_hal.h"

#define DISPLAY_DEFAULT_BRIGTHNESS 100

static void gui_app_initDisplay(void);
static void gui_app_initExternalDisplay(void);
static void gui_app_initSettings(void);
static void gui_app_handleUartData(void);
static void gui_app_addPointToEvent(GuiEvent_s *p_guiEvent, const uint8_t event, const TouchPoint_s *p_point);
static void gui_app_showLogo(const bool showAnimation);
static void gui_app_setRTCDateTime(const uint8_t *p_eventArgs);
static void gui_app_clearUartRx(void);
static void gui_app_configureUartDmaRx(void);
static uint32_t gui_app_calculateCrc(FIL *p_file);
static TouchPoint_s tp_getTouchPoint(const uint8_t *p_eventArgs);
static void gui_setButtonEvent(const uint8_t event);

extern UART_HandleTypeDef hlpuart1;
extern RTC_HandleTypeDef hrtc;
extern CRC_HandleTypeDef hcrc;

static GuiApplication_s m_guiApp;
static FATFS m_fatFs;

static uint8_t m_uartRxBuffer[ED_IN_BUFFER_LENGTH];
static volatile bool m_uartDataReceived;


void gui_app_start(void)
{
    gui_app_initDisplay();
    gui_app_initExternalDisplay();
    gui_app_initSettings();
	gui_app_showLogo(true);
	gui_app_drawBackground();

	touch_dr_init();

	graphics_flushDisplayUpdates();

	view_init(&m_guiApp.view);
    mainview_navigateTo();
    graphics_flushDisplayUpdates();

    gui_app_clearUartRx();
    gui_app_configureUartDmaRx();

	while (true)
	{
        gui_app_handleUartData();
        touch_dr_scan();
        TouchPoint_s point = {0};
        TouchState_e tpState = touch_handlePressed(&point);

        GuiEvent_s guiEvent;
        guiEvent.event = GUI_EVENT_NONE;

        if (TouchState_OnPressed == tpState)
        {
            gui_app_addPointToEvent(&guiEvent, GUI_EVENT_TOUCH_ON_PRESSED, &point);
        }
        else if (TouchState_OnReleased == tpState)
        {
            gui_app_addPointToEvent(&guiEvent, GUI_EVENT_TOUCH_ON_RELEASED, &point);
        }
        else if (TouchState_Pressed == tpState)
        {
            gui_app_addPointToEvent(&guiEvent, GUI_EVENT_TOUCH_PRESSED, &point);
        }
        else if (adc1ConvCmplt())
        {
            guiEvent.event = CUSTOM_GUI_EVENT_MEASREMANT_READY;
        }
        else if (updateDateTime())
        {
            header_updateDateTime(false);
        }
        else if (m_guiApp.alarmActive)
        {
            if (HAL_GetTick() >= m_guiApp.alarmTime_ms)
            {
                m_guiApp.alarmActive = false;
                message_dialog_show(FILE_KEY_TITLE_ALARM, FILE_KEY_TEXT_ALARM, mainview_navigateTo);
                header_showAlarm(false);
            }
        }
        else
        {
        }

        if (GUI_EVENT_NONE != guiEvent.event)
        {
            view_handleEvent(&m_guiApp.view, &guiEvent);
        }

        graphics_flushDisplayUpdates();
	}
}

void gui_app_clearView(void)
{
    Rectangle_s background;
    rectangle_initFillPosSize(
        &background, theme_getBackgroundColor(),
        0, STYLE_VIEW_Y, STYLE_DISPLAY_WIDTH, STYLE_VIEW_HEIGHT);
    base_display(&background);
}

void gui_app_drawBackground(void)
{
    gui_app_drawHeaderBackground();
    gui_app_clearView();
    gui_app_drawFooterBackground();
}

void gui_app_drawHeaderBackground(void)
{
    Rectangle_s background;
    rectangle_initFillPosSize(
        &background, theme_getHeaderColor(),
        STYLE_HEADER_X, STYLE_HEADER_Y, STYLE_DISPLAY_WIDTH, STYLE_HEADER_HEIGHT);
    base_display(&background);

    Rectangle_s separatorTop;
    rectangle_initFillPosSize(
        &separatorTop, theme_getSeparatorColor(),
        STYLE_HEADER_X, SYTLE_HEADER_SEPARATOR_Y, STYLE_DISPLAY_WIDTH, STYLE_HEADER_SEPARATOR_HEIGHT);
    base_display(&separatorTop);

    Label_s clock;
    label_initBmpPosSize(
        &clock, FILE_KEY_ICON_HEADER_CLOCK,
        STYLE_HEADER_X, STYLE_HEADER_Y, STYLE_HEADER_ICON_WIDTH, STYLE_HEADER_ICON_HEIGHT);
    theme_applyThemeProperty(&clock.base);
    base_display(&clock.base);

    Label_s wifi;
    label_initBmpPosSize(
        &wifi, FILE_KEY_ICON_HEADER_WIFI,
        (STYLE_DISPLAY_WIDTH - STYLE_HEADER_ICON_WIDTH), STYLE_HEADER_Y, STYLE_HEADER_ICON_HEIGHT, STYLE_HEADER_HEIGHT);
    theme_applyThemeProperty(&wifi.base);
    base_display(&wifi.base);

    header_updateDateTime(true);
}

void gui_app_drawFooterBackground(void)
{
    Rectangle_s separatorBottom;
    rectangle_initFillPosSize(
        &separatorBottom, theme_getSeparatorColor(),
        STYLE_FOOTER_X, STYLE_FOOTER_SEPARATOR_Y, STYLE_DISPLAY_WIDTH, STYLE_FOOTER_SEPARATOR_HEIGHT);
    base_display(&separatorBottom);

    Rectangle_s background;
    rectangle_initFillPosSize(
        &background, theme_getFooterColor(),
        STYLE_FOOTER_X, STYLE_FOOTER_Y, STYLE_DISPLAY_WIDTH, STYLE_FOOTER_HEIGHT);
    base_display(&background);
}

void gui_app_showFooterLogo(void)
{
    Item_s item;
    item_init(&item);
    base_setPosition(&item, STYLE_FOOTER_X, STYLE_FOOTER_Y);
    base_setDimensions(&item, STYLE_FOOTER_WIDTH, STYLE_FOOTER_HEIGHT);

    Label_s logo;
    label_init(&logo);
    GuiAnchor_s logoAnchor;
    anchor_init(&logoAnchor);
    base_addAnchor(&logo, &logoAnchor);
    anchor_setRightAnchor(&logo, &item, Gui_Anchor_Right);
    anchor_setVerticalCenter(&logo, &item);
    anchor_setRightMargin(&logo, 10);
    label_setBmpKey(&logo, FILE_KEY_IRL_LOGO_48);
    base_display(&logo);

    Label_s mcsGui;
    label_initBmp(&mcsGui, FILE_KEY_TEXT_FOOTER_MCSGUI);
    theme_applyThemeProperty(&mcsGui);
    GuiAnchor_s mcsGuiAnchor;
    anchor_init(&mcsGuiAnchor);
    base_addAnchor(&mcsGui.base, &mcsGuiAnchor);
    anchor_setRightAnchor(&mcsGui, &logo, Gui_Anchor_Left);
    anchor_setVerticalCenter(&mcsGui, &logo);
    anchor_setRightMargin(&mcsGui, 10);
    base_display(&mcsGui.base);
}

void gui_app_translate(void *p_component)
{
    property_value_language_e languageProperty;

    switch (m_guiApp.language)
    {
        case Language_English:
            languageProperty = PROPERTY_LANGUAGE_VALUE_ENGLISH;
            break;
        case Language_Dutch:
            languageProperty = PROPERTY_LANGUAGE_VALUE_DUTCH;
            break;
        case Lanugage_German:
            languageProperty = PROPERTY_LANGUAGE_VALUE_GERMAN;
            break;
        case Language_French:
            languageProperty = PROPERTY_LANGUAGE_VALUE_FRENCH;
            break;
        case Language_Spanish:
            languageProperty = PROPERTY_LANGUAGE_VALUE_SPANISH;
            break;
        case Language_Italian:
            languageProperty = PROPERTY_LANGUAGE_VALUE_ITALIAN;
            break;
        case Language_Russian:
            languageProperty = PROPERTY_LANGUAGE_VALUE_RUSSIAN;
            break;
        case Language_Chinese:
            languageProperty = PROPERTY_LANGUAGE_VALUE_CHINESE;
            break;
        case Language_Japanese:
            languageProperty = PROPERTY_LANGUAGE_VALUE_JAPANESE;
            break;
        case Language_Korean:
            languageProperty = PROPERTY_LANGUAGE_VALUE_KOREAN;
            break;
        default:
            languageProperty = PROPERTY_LANGUAGE_VALUE_ENGLISH;
            break;
    }

    base_setProperty(p_component, FILE_PROPERTY_LANGUAGE, languageProperty);
}

void gui_app_activateAlarm(void)
{
    m_guiApp.alarmTime_ms = HAL_GetTick() + (m_guiApp.alarmTime_mm * 60000);
    m_guiApp.alarmActive = true;
    header_showAlarm(true);
}

View_s* gui_app_getView(void)
{
    return &m_guiApp.view;
}

Language_e gui_app_getLanguage(void)
{
    return m_guiApp.language;
}

TemperatureUnit_e gui_app_getTemperatureUnit(void)
{
    return m_guiApp.temperatureUnit;
}

uint8_t gui_app_getDisplayBrightness(void)
{
    return m_guiApp.displayBrightness;
}

bool gui_app_getUpdateDateTime(void)
{
    return m_guiApp.updateDateTime;
}

void gui_app_setLanguage(const Language_e language)
{
    m_guiApp.language = language;
}

void gui_app_setTemperatureUnit(const TemperatureUnit_e temperatureUnit)
{
    m_guiApp.temperatureUnit = temperatureUnit;
}

void gui_app_setDisplayBrightness(const uint8_t brightness)
{
    m_guiApp.displayBrightness = brightness;
}

void gui_app_setAlarmTime(const uint8_t alarmTime_mm)
{
    m_guiApp.alarmTime_mm = alarmTime_mm;
}

void gui_app_setUpdateDateTime(const bool update)
{
    m_guiApp.updateDateTime = update;
}


static void gui_app_initDisplay(void)
{
    display_init(DisplayDriver_ILI9486, STYLE_DISPLAY_HEIGHT, STYLE_DISPLAY_WIDTH, LandscapeFlip, false);
    display_setBacklight(DISPLAY_DEFAULT_BRIGTHNESS);

#ifdef USE_DISPLAY_AND_SD_CARD
    FRESULT mountRes = f_mount(&m_fatFs, "", 1);
    if (FR_OK != mountRes)
    {
        gui_log_error("FATFS failed to mount");
    }

    bool guiImageInitialized = gui_image_initialize();
    if (!guiImageInitialized)
    {
        gui_log_error("Failed to initialize gui image");
    }
#endif /* USE_DISPLAY_AND_SD_CARD */
}

static void gui_app_initExternalDisplay(void)
{
    EdSetup_s setup = {0};
    setup.width = STYLE_DISPLAY_WIDTH;
    setup.height = STYLE_DISPLAY_HEIGHT;
    setup.useKeyNav = false;
    setup.useTouch = true;
    strcpy(setup.description, "McsGui Demo 2!");
    ed_setSetup(setup);
    gui_log_debug("Log is working");
}

static void gui_app_initSettings(void)
{
    m_guiApp.language = Language_English;
    m_guiApp.temperatureUnit = TemperatureUnit_Celsius;
    m_guiApp.updateDateTime = true;
    m_guiApp.alarmActive = false;
    m_guiApp.alarmTime_mm = 0;
    m_guiApp.alarmTime_ms = 0;
    m_guiApp.displayBrightness = DISPLAY_DEFAULT_BRIGTHNESS;
    m_guiApp.themeSetting.theme = GuiTheme_Light;
    m_guiApp.themeSetting.accentColorProperty = PROPERTY_ACCENT_COLOR_VALUE_RED;

    theme_init(&m_guiApp.themeSetting);

    TouchCalibrationValues_s calibrationValues = {0};
    calibrationValues.gainX = 1.11764705f;
    calibrationValues.gainY = 1.12244892f;
    calibrationValues.offsetX = -24.8823547f;
    calibrationValues.offsetY = -16.2244873f;
    touch_dr_setCalibrationValues(&calibrationValues);
}

static void gui_app_handleUartData(void)
{
    if (m_uartDataReceived)
    {
        ed_handleRequest(m_uartRxBuffer);
        gui_app_configureUartDmaRx();
    }
}

static void gui_app_addPointToEvent(GuiEvent_s *p_guiEvent, const uint8_t event, const TouchPoint_s *p_point)
{
    p_guiEvent->event = event;
    memcpy(p_guiEvent->eventArgs, &p_point->x, sizeof(uint16_t));
    memcpy(&p_guiEvent->eventArgs[2], &p_point->y, sizeof(uint16_t));
}

void ed_eventRecevied(GuiEvent_s guiEvent)
{
	switch (guiEvent.event)
	{
	    case GUI_EVENT_DATE_TIME_CHANGED:
            gui_app_setRTCDateTime(guiEvent.eventArgs);
            break;
        case GUI_EVENT_KEY_ENTER_PRESS:
        case GUI_EVENT_KEY_LEFT_PRESS:
        case GUI_EVENT_KEY_UP_PRESS:
        case GUI_EVENT_KEY_RIGHT_PRESS:
        case GUI_EVENT_KEY_DOWN_PRESS:
        case GUI_EVENT_KEY_ENTER_RELEASE:
        case GUI_EVENT_KEY_LEFT_RELEASE:
        case GUI_EVENT_KEY_UP_RELEASE:
        case GUI_EVENT_KEY_RIGHT_RELEASE:
        case GUI_EVENT_KEY_DOWN_RELEASE:
            gui_setButtonEvent(guiEvent.event);
            break;
        case GUI_EVENT_TOUCH_ON_PRESSED:
        {
            const TouchPoint_s point = tp_getTouchPoint(guiEvent.eventArgs);
            touch_setState(TouchState_Pressed, point);

            break;
        }
        case GUI_EVENT_TOUCH_ON_RELEASED:
        {
            const TouchPoint_s point = tp_getTouchPoint(guiEvent.eventArgs);
            touch_setState(TouchState_Released, point);

            break;
        }
        case GUI_EVENT_NAVIGATE_TO_HOME:
            gui_app_drawBackground();
            mainview_navigateTo();
            break;
        default:
            break;
	}
}

extern void ed_writeBuffer(uint8_t *p_buffer, uint32_t bytesToWrite)
{
    HAL_UART_Transmit(&hlpuart1, p_buffer, bytesToWrite, 1000);
}

extern uint32_t ed_calculateCrc(const uint8_t *p_data, const uint32_t length)
{
    const uint32_t crc = HAL_CRC_Calculate(&hcrc, (uint32_t *)p_data, length);

    return crc;
}

extern void ed_startFileWrite(uint32_t fileSize, const char *p_fileName)
{
    char filePath[128] = {0};
    snprintf(filePath, sizeof(filePath), "%s%s", GUI_IMAGE_DIRECTORY, p_fileName);

    FIL file = {0};
    FRESULT openRes = f_open(&file, filePath, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);

    uint32_t timeout = ED_FILE_WRITE_TIMEOUT + HAL_GetTick();
    uint32_t totalBytesWritten = 0;
    uint8_t buffer[ED_FILE_TRANSFER_BUFFER_LENGTH] = {0};
    bool fileWriteCanceled = false;

    if (FR_OK == openRes)
    {
        HAL_UART_Receive_DMA(&hlpuart1, buffer, ED_FILE_TRANSFER_BUFFER_LENGTH);
        m_uartDataReceived = false;

        ed_sendRequestResponseOK();
    }
    else
    {
        ed_sendRequestResponseError();
        gui_log_error("Failed to open file for writing");

        return;
    }

    for (;;)
    {
        if (m_uartDataReceived)
        {
            const uint32_t bytesReceived = utils_array_getUint32(buffer, 0);

            if (bytesReceived == 0)
            {
                fileWriteCanceled = true;

                break;
            }

            UINT bytesWritten = 0;
            f_write(&file, &buffer[4], bytesReceived, &bytesWritten);
            totalBytesWritten += bytesWritten;

            if (totalBytesWritten < fileSize)
            {
                m_uartDataReceived = false;
                HAL_UART_Receive_DMA(&hlpuart1, buffer, ED_FILE_TRANSFER_BUFFER_LENGTH);
                ed_sendRequestResponseOK();
            }

            timeout = ED_FILE_WRITE_TIMEOUT + HAL_GetTick();
        }

        if (totalBytesWritten >= fileSize)
        {
            break;
        }

        if (HAL_GetTick() > timeout)
        {
            gui_log_error("File write timeout");

            break;
        }
    }

    if (fileWriteCanceled)
    {
        f_close(&file);
        f_unlink(filePath);
        gui_log_info("File write canceled");
    }
    else
    {
        const uint32_t crc = gui_app_calculateCrc(&file);
        ed_sendRequestResponseData((uint8_t *)&crc, sizeof(uint32_t));

        if (totalBytesWritten != fileSize)
        {
            gui_log_error("Failed to write all bytes to file");
        }

        f_close(&file);
    }
}

static uint32_t gui_app_calculateCrc(FIL *p_file)
{
    f_rewind(p_file);

    uint32_t crc = 0;
    bool crcStart = true;
    bool dataRead = true;
    uint8_t buffer[ED_FILE_TRANSFER_BUFFER_LENGTH] = {0};

    while (dataRead)
    {
        UINT bytesRead = 0;
        f_read(p_file, buffer, ED_FILE_TRANSFER_BUFFER_LENGTH, &bytesRead);
        dataRead = bytesRead > 0;

        if (!dataRead)
        {
            break;
        }

        if (crcStart)
        {
            crcStart = false;
            crc = HAL_CRC_Calculate(&hcrc, (uint32_t*) buffer, bytesRead);
        }
        else
        {
            crc = HAL_CRC_Accumulate(&hcrc, (uint32_t*) buffer, bytesRead);
        }
    }

    return crc;
}


void gui_log_write(const uint8_t logLevel, const char *p_message)
{
    char logMessage[GUI_APP_LOG_MESSAGE_LENGTH_INC_NULL] = {0};

    switch (logLevel)
    {
        case GUI_LOG_LEVEL_ERROR:
            strcpy(logMessage, "[ERROR] ");
            break;
        case GUI_LOG_LEVEL_WARNING:
            strcpy(logMessage, "[WARNING] ");
            break;
        case GUI_LOG_LEVEL_DEBUG:
            strcpy(logMessage, "[DEBUG] ");
            break;
        case GUI_LOG_LEVEL_INFO:
            strcpy(logMessage, "[INFO] ");
            break;
        default:
            break;
    }

    strcat(logMessage, p_message);
    ed_log(logMessage);
}

EdButtonSetup_s ed_getCustomButton(const uint8_t index)
{
	EdButtonSetup_s setup = {0};

	if (0 == index)
	{
		setup.index = 1;
		setup.event = 110;
		strcpy(setup.description, "Button 1");
	}
	else if (1 == index)
	{
		setup.index = 3;
		setup.event = 111;
		strcpy(setup.description, "Button 2");
	}
	else if (2 == index)
	{
		setup.index = 5;
		setup.event = 112;
		strcpy(setup.description, "Button 3");
	}
	else if (3 == index)
	{
		setup.index = 6;
		setup.event = 113;
		strcpy(setup.description, "Button 4");
	}

	return setup;
}

static void gui_app_showLogo(const bool showAnimation)
{
    Rectangle_s background;
    rectangle_initFillSize(&background, COLOR_IRL_BLUE, STYLE_DISPLAY_WIDTH, STYLE_DISPLAY_HEIGHT);
    base_display(&background);

    int32_t i = (showAnimation) ? 0 : 23;

    for (; i < 24; i++)
    {
        Item_s item;
        item_init(&item);
        base_setPosition(&item, 0, 0);
        base_setDimensions(&item, STYLE_DISPLAY_WIDTH, STYLE_DISPLAY_HEIGHT);

        Label_s logo;
        label_initBmp(&logo, FILE_KEY_ANIMATION_IRL_LOGO);
        base_setDimensions(&logo, 128, 128);
        base_setProperty(&logo, FILE_PROPERTY_ANIMATION, (property_value_animation_e)i);
        GuiAnchor_s anchor;
        anchor_init(&anchor);
        base_addAnchor(&logo, &anchor);
        anchor_setCenterInParent(&logo, &item);

        graphics_displayComponent(&logo.base);
        graphics_flushDisplayUpdates();

        HAL_Delay(50);
    }
}

static void gui_app_clearUartRx(void)
{
    while (HAL_TIMEOUT != HAL_UART_Receive(&hlpuart1, m_uartRxBuffer, 1, 0));
}

static void gui_app_configureUartDmaRx(void)
{
    HAL_UART_Receive_DMA(&hlpuart1, m_uartRxBuffer, ED_IN_BUFFER_LENGTH);
    m_uartDataReceived = false;
}

static void gui_app_setRTCDateTime(const uint8_t *p_eventArgs)
{
    RTC_TimeTypeDef sTime = { 0 };
    RTC_DateTypeDef sDate = { 0 };

    sDate.Year = p_eventArgs[0];
    sDate.Month = p_eventArgs[1];
    sDate.Date = p_eventArgs[2];
    sTime.Hours = p_eventArgs[3];
    sTime.Minutes = p_eventArgs[4];
    sTime.Seconds = p_eventArgs[5];
    sDate.WeekDay = p_eventArgs[6];

    HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

static TouchPoint_s tp_getTouchPoint(const uint8_t *p_eventArgs)
{
    TouchPoint_s point = { 0 };
    point.x = utils_array_getUint16(p_eventArgs, 0);
    point.y = utils_array_getUint16(p_eventArgs, 2);

    return point;
}

static void gui_setButtonEvent(const uint8_t event)
{
    uint8_t idx = NUM_BUTTONS;
    ButtonState_e state = BtnState_Error;

    switch (event)
    {
        case GUI_EVENT_KEY_ENTER_PRESS:
            idx = BUTTON_OK_IDX;
            state = BtnState_Pressed;
            break;
        case GUI_EVENT_KEY_LEFT_PRESS:
            idx = BUTTON_LEFT_IDX;
            state = BtnState_Pressed;
            break;
        case GUI_EVENT_KEY_UP_PRESS:
            idx = BUTTON_UP_IDX;
            state = BtnState_Pressed;
            break;
        case GUI_EVENT_KEY_RIGHT_PRESS:
            idx = BUTTON_RIGHT_IDX;
            state = BtnState_Pressed;
            break;
        case GUI_EVENT_KEY_DOWN_PRESS:
            idx = BUTTON_DOWN_IDX;
            state = BtnState_Pressed;
            break;
        case GUI_EVENT_KEY_ENTER_RELEASE:
            idx = BUTTON_OK_IDX;
            state = BtnState_Released;
            break;
        case GUI_EVENT_KEY_LEFT_RELEASE:
            idx = BUTTON_LEFT_IDX;
            state = BtnState_Released;
            break;
        case GUI_EVENT_KEY_UP_RELEASE:
            idx = BUTTON_UP_IDX;
            state = BtnState_Released;
            break;
        case GUI_EVENT_KEY_RIGHT_RELEASE:
            idx = BUTTON_RIGHT_IDX;
            state = BtnState_Released;
            break;
        case GUI_EVENT_KEY_DOWN_RELEASE:
            idx = BUTTON_DOWN_IDX;
            state = BtnState_Released;
            break;
        default:
            break;
    }

    if (idx < NUM_BUTTONS)
    {
        btn_setBtnState(idx, state);
    }
}


// Interrupt callback function
//
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == LPUART1)
    {
        if (!m_uartDataReceived)
        {
            m_uartDataReceived = true;
        }
    }
}
