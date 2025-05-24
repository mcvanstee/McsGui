#include "gui_app.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "fs_file_search.h"
#include "fs_font_search.h"
#include "external_display.h"
#include "logger.h"

#include "style.h"
#include "gui_control_bar.h"
#include "display_api.h"
#include "gui_image.h"
#include "gui_settings.h"
#include "Graphics/gui_graphics.h"
#include "external_display.h"
#include "colors.h"
#include "touch_api.h"
#include "touch_driver.h"
#include "temp_recorder.h"
#include "utils_array.h"
#include "utils_data.h"
#include "main.h"
#include "ff.h"

#include "main_view.h"
#include "settings_view.h"
#include "setup_view.h"
#include "measurement_view.h"
#include "recordings_view.h"
#include "calibrate_touch_view.h"

static void gui_app_initDisplay(void);
static void gui_app_initExternalDisplay(void);
static void gui_app_createFolders(void);
static void gui_app_initSettings(void);
static void gui_app_initControlBar(void);
static void gui_app_addPointToEvent(GuiEvent_s *p_guiEvent, const uint8_t event, const TouchPoint_s *p_point);
static void gui_app_handleUartData(void);
static void gui_app_setRTCDateTime(const uint8_t *p_eventArgs);
static void gui_app_clearUartRx(void);
static void gui_app_configureUartDmaRx(void);
static TouchPoint_s tp_getTouchPoint(const uint8_t *p_eventArgs);
static uint32_t gui_app_calculateCrc(FIL *p_file);

extern UART_HandleTypeDef hlpuart1;
extern RTC_HandleTypeDef hrtc;
extern CRC_HandleTypeDef hcrc;

LogLevel system_log_level = LOG_LEVEL_DEBUG;
GuiApplication_s g_guiApp;
static FATFS m_fatFs;
static ControlBar_s m_controlBar;

static uint8_t m_uartRxBuffer[ED_IN_BUFFER_LENGTH];
static volatile bool m_uartDataReceived;


void gui_app_start(void)
{
    gui_app_initDisplay();
    gui_app_initExternalDisplay();
    gui_app_createFolders();
    gui_app_initSettings();

	gui_app_drawBackground();
	view_init(&g_guiApp.view);
	gui_app_initControlBar();
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

        const bool tempRecSampleAdded = temp_recorder_handler();

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
        else if (tempRecSampleAdded)
        {
            guiEvent.event = CUSTOM_GUI_EVENT_REC_NUMBER_CHANGED;
        }
        else if (adc1ConvCmplt())
        {
            guiEvent.event = CUSTOM_GUI_EVENT_MEASREMANT_READY;
        }
        else if (updateDateTime() && (g_guiApp.showTime || g_guiApp.showDate))
        {
        	guiEvent.event = CUSTOM_GUI_EVENT_UPDATE_DATE_TIME;
        }
        else
        {
        }

        if (GUI_EVENT_NONE != guiEvent.event)
        {
            view_handleEvent(&g_guiApp.view, &guiEvent);
        }

        graphics_flushDisplayUpdates();
	}
}

static void gui_app_initDisplay(void)
{
    display_init(DisplayDriver_ILI9486, STYLE_DISPLAY_HEIGHT, STYLE_DISPLAY_WIDTH, LandscapeFlip, false);
    display_setBacklight(DISPLAY_DEFAULT_BRIGTHNESS);

#ifdef USE_DISPLAY_AND_SD_CARD
    FRESULT mountRes = f_mount(&m_fatFs, "", 1);
    if (FR_OK != mountRes)
    {
        log_error("FATFS failed to mount");
    }

    bool guiImageInitialized = gui_image_initialize();
    if (!guiImageInitialized)
    {
        log_error("Failed to initialize gui image");
    }
#endif /* USE_DISPLAY_AND_SD_CARD */

    touch_dr_init();
}

static void gui_app_initExternalDisplay(void)
{
    EdSetup_s setup = {0};
    setup.width = STYLE_DISPLAY_WIDTH;
    setup.height = STYLE_DISPLAY_HEIGHT;
    setup.useKeyNav = false;
    setup.useTouch = true;
    strcpy(setup.description, "McsGui Demo 3!");
    ed_setSetup(setup);
    log_debug("Log is working");
}

static void gui_app_createFolders(void)
{
    bool folderCreated = utils_data_createFolderIfNotExist("Settings");
    if (!folderCreated)
    {
        log_error("Failed to create Settings folder");
    }

    folderCreated = utils_data_createFolderIfNotExist("Recordings");
    if (!folderCreated)
    {
        log_error("Failed to create Recordings folder");
    }

    folderCreated = utils_data_createFolderIfNotExist("Recordings/new");
    if (!folderCreated)
    {
        log_error("Failed to create Recordings/new folder");
    }
}

static void gui_app_initSettings(void)
{
    settings_load();
    GuiSettings_s settings = settings_getSettings();

    g_guiApp.language = (Language_e)settings.language;
    g_guiApp.temperatureUnit = (TemperatureUnit_e)settings.temperatureUnit;
    g_guiApp.showTime = settings.showTime;
    g_guiApp.showDate = settings.showDate;
    g_guiApp.displayBrightness = settings.displayBrightness;

    TouchCalibrationValues_s calibrationValues = {0};
    calibrationValues.gainX = settings.gainX;
    calibrationValues.gainY = settings.gainY;
    calibrationValues.offsetX = settings.offsetX;
	calibrationValues.offsetY = settings.offsetY;
	touch_dr_setCalibrationValues(&calibrationValues);
}

static void gui_app_initControlBar(void)
{
    control_bar_init(&m_controlBar);
    control_bar_addButton(&m_controlBar, 0, FILE_KEY_ICON_HOME, mainview_navigateTo);
    control_bar_addButton(&m_controlBar, 1, FILE_KEY_ICON_BULLSEYE, measurement_view_navigateTo);
    control_bar_addButton(&m_controlBar, 2, FILE_KEY_ICON_SLIDERS, setup_view_navigateTo);
    control_bar_addButton(&m_controlBar, 3, FILE_KEY_ICON_FOCUS, recordings_view_navigateTo);
    control_bar_addButton(&m_controlBar, 7, FILE_KEY_ICON_GEAR, settings_view_navigateTo);
    control_bar_setSelected(&m_controlBar, 0);
    base_setId(&m_controlBar.base, CONTROL_BAR_ID);
    view_addTopComponent(&g_guiApp.view, &m_controlBar.base);
}

static void gui_app_addPointToEvent(GuiEvent_s *p_guiEvent, const uint8_t event, const TouchPoint_s *p_point)
{
    p_guiEvent->event = event;
    memcpy(p_guiEvent->eventArgs, &p_point->x, sizeof(uint16_t));
    memcpy(&p_guiEvent->eventArgs[2], &p_point->y, sizeof(uint16_t));
}

extern void ed_eventRecevied(GuiEvent_s guiEvent)
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
            gui_app_setVisibiltyControlBar(true);
            control_bar_setSelected(&m_controlBar, 0);
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
        log_error("Failed to open file for writing");

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
            log_error("File write timeout");

            break;
        }
    }

    if (fileWriteCanceled)
    {
        f_close(&file);
        f_unlink(filePath);
        log_info("File write canceled");
    }
    else
    {
        const uint32_t crc = gui_app_calculateCrc(&file);
        ed_sendRequestResponseData((uint8_t *)&crc, sizeof(uint32_t));

        if (totalBytesWritten != fileSize)
        {
            log_error("Failed to write all bytes to file");
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
	switch (logLevel)
	{
		case GUI_LOG_LEVEL_ERROR:
			log_error(p_message);
			break;
		case GUI_LOG_LEVEL_WARNING:
			log_warning(p_message);
			break;
		case GUI_LOG_LEVEL_DEBUG:
			log_debug(p_message);
			break;
		default:
			break;
	}
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

void gui_app_drawBackground(void)
{
    Rectangle_s controlBarBackground;
    rectangle_initFillPosSize(&controlBarBackground, COLOR_BACKGROUND, 0, 0, STYLE_CONTROL_BAR_WIDTH, STYLE_DISPLAY_HEIGHT);
    base_display(&controlBarBackground);

	Rectangle_s separatorLeft;
	rectangle_initFillPosSize(
	        &separatorLeft, COLOR_SEPARATOR, STYLE_CONTROL_BAR_WIDTH, 0, STYLE_CONTROL_BAR_SEPARATOR_WIDTH, STYLE_DISPLAY_HEIGHT);
	base_display(&separatorLeft);
    gui_app_clearView();
}

void gui_app_clearView(void)
{
    Rectangle_s background;
    rectangle_initFillPosSize(&background, COLOR_BACKGROUND, 42, 0, (STYLE_DISPLAY_WIDTH - 42), STYLE_DISPLAY_HEIGHT);
    base_display(&background);
}

void gui_app_translate(void *p_component)
{
    property_value_language_e languageProperty;

    switch (g_guiApp.language)
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

void gui_app_setVisibiltyControlBar(const bool visible)
{
    base_setVisible(&m_controlBar.base, visible);
}

uint32_t gui_app_getTimeStamp(void)
{
    RTC_TimeTypeDef time = {0};
    RTC_DateTypeDef date = {0};

    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);

    return gui_app_convertTimeStampToSeconds(&time, &date);
}

uint32_t gui_app_convertTimeStampToSeconds(RTC_TimeTypeDef *p_time, RTC_DateTypeDef *p_date)
{
    struct tm dateTime = {0};
    dateTime.tm_year = p_date->Year + 100;
    dateTime.tm_mday = p_date->Date;
    dateTime.tm_mon = p_date->Month - 1;
    dateTime.tm_hour = p_time->Hours;
    dateTime.tm_min = p_time->Minutes;
    dateTime.tm_sec = p_time->Seconds;

    return (uint32_t) mktime(&dateTime);
}

static void gui_app_setRTCDateTime(const uint8_t *p_eventArgs)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

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
	TouchPoint_s point = {0};
    point.x = utils_array_getUint16(p_eventArgs, 0);
    point.y = utils_array_getUint16(p_eventArgs, 2);

    return point;
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

static void gui_app_handleUartData(void)
{
    if (m_uartDataReceived)
    {
        ed_handleRequest(m_uartRxBuffer);
        gui_app_configureUartDmaRx();
    }
}

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
