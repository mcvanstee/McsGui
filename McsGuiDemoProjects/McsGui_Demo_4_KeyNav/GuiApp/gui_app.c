#include "gui_app.h"

#include <stdbool.h>
#include <string.h>
#include <stdio.h>


#include "external_display.h"
#include "display_api.h"
#include "gui_app_settings.h"
#include "gui_image.h"
#include "Graphics/gui_graphics.h"
#include "external_display.h"
#include "nav_buttons.h"
#include "hal_buttons.h"
#include "utils_array.h"
#include "main.h"
#include "ff.h"

#include "main_view.h"

#include "stm32l4xx_hal.h"


static void gui_app_initDisplay(void);
static void gui_app_initExternalDisplay(void);
static void gui_app_initSettings(void);
static void gui_app_handleUartData(void);
static void gui_app_showLogo(const bool showAnimation);
static void gui_app_setRTCDateTime(const uint8_t *p_eventArgs);
static void gui_app_clearUartRx(void);
static void gui_app_configureUartDmaRx(void);
static uint32_t gui_app_calculateCrc(FIL *p_file);
static void gui_app_NavigateAway(View_s *p_view);


extern UART_HandleTypeDef hlpuart1;
extern RTC_HandleTypeDef hrtc;
extern CRC_HandleTypeDef hcrc;

static GuiApplication_s g_guiApp;
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

	nav_btn_init();
	footer_init(&g_guiApp.footer);
	view_init(&g_guiApp.view);
	view_setOnNavigateAway(&g_guiApp.view, gui_app_NavigateAway);
	view_addBottomComponent(&g_guiApp.view, &g_guiApp.footer);
    mainview_navigateTo();
    graphics_flushDisplayUpdates();

    gui_app_clearUartRx();
    gui_app_configureUartDmaRx();

	while (true)
	{
	    gui_app_handleUartData();
		hal_btn_handler();

        GuiEvent_s guiEvent;
        guiEvent.event = GUI_EVENT_NONE;

        if (nav_btn_okBtnPressed())
        {
            guiEvent.event = GUI_EVENT_KEY_ENTER_PRESS;
        }
        else if (nav_btn_leftBtnPressed())
        {
            guiEvent.event = GUI_EVENT_KEY_LEFT_PRESS;
        }
        else if (nav_btn_upBtnPressed())
        {
            guiEvent.event = GUI_EVENT_KEY_UP_PRESS;
        }
        else if (nav_btn_rightBtnPressed())
        {
            guiEvent.event = GUI_EVENT_KEY_RIGHT_PRESS;
        }
        else if (nav_btn_downBtnPressed())
        {
            guiEvent.event = GUI_EVENT_KEY_DOWN_PRESS;
        }
        else if (nav_btn_okBtnReleased())
        {
            guiEvent.event = GUI_EVENT_KEY_ENTER_RELEASE;
        }
        else if (nav_btn_leftBtnReleased())
        {
            guiEvent.event = GUI_EVENT_KEY_LEFT_RELEASE;
        }
        else if (nav_btn_upBtnReleased())
        {
            guiEvent.event = GUI_EVENT_KEY_UP_RELEASE;
        }
        else if (nav_btn_rightBtnReleased())
        {
            guiEvent.event = GUI_EVENT_KEY_RIGHT_RELEASE;
        }
        else if (nav_btn_downBtnReleased())
        {
            guiEvent.event = GUI_EVENT_KEY_DOWN_RELEASE;
        }
        else if (adc1ConvCmplt())
        {
            guiEvent.event = CUSTOM_GUI_EVENT_MEASUREMENT_READY;
        }
        else if (updateDateTime())
        {
            header_updateDateTime(false);
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

void gui_app_drawBackground(void)
{
    header_drawHeaderBackground();
    gui_app_clearView();
    footer_drawBackground();
}

void gui_app_clearView(void)
{
    Rectangle_s background;
    rectangle_initFillPosSize(
        &background, theme_getBackgroundColor(),
        STYLE_VIEW_X, STYLE_VIEW_Y, STYLE_DISPLAY_WIDTH, STYLE_VIEW_HEIGHT);
    base_display(&background);
}

void gui_app_translate(void *p_component)
{
    property_value_language_e languageProperty;

    switch (settings_getLanguage())
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

bool gui_app_getUpdateDateTime(void)
{
    return g_guiApp.updateDateTime;
}

void gui_app_setUpdateDateTime(const bool update)
{
    g_guiApp.updateDateTime = update;
}

View_s *gui_app_getView(void)
{
    return &g_guiApp.view;
}

Footer_s *gui_app_getFooter(void)
{
    return &g_guiApp.footer;
}

static void gui_app_NavigateAway(View_s *p_view)
{
    footer_resetButton(&g_guiApp.footer);
}

static void gui_app_initDisplay(void)
{
    display_init(DisplayDriver_ST7789, STYLE_DISPLAY_HEIGHT, STYLE_DISPLAY_WIDTH, Landscape, true);
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
    setup.useKeyNav = true;
    setup.useTouch = false;
    strcpy(setup.description, "McsGui Demo 4!");
    ed_setSetup(setup);
    gui_log_debug("Log is working");
}

static void gui_app_initSettings(void)
{
    g_guiApp.updateDateTime = true;
    settings_load();
}

static void gui_app_handleUartData(void)
{
    if (m_uartDataReceived)
    {
        ed_handleRequest(m_uartRxBuffer);
        gui_app_configureUartDmaRx();
    }
}

void ed_eventRecevied(GuiEvent_s guiEvent)
{
	switch (guiEvent.event)
	{
	    case GUI_EVENT_DATE_TIME_CHANGED:
            gui_app_setRTCDateTime(guiEvent.eventArgs);
            break;
        case GUI_EVENT_KEY_ENTER_PRESS:
            nav_btn_handleEvent(NavBtnEvent_OK_Pressed);
            break;
        case GUI_EVENT_KEY_LEFT_PRESS:
            nav_btn_handleEvent(NavBtnEvent_Left_Pressed);
            break;
        case GUI_EVENT_KEY_UP_PRESS:
            nav_btn_handleEvent(NavBtnEvent_Up_Pressed);
            break;
        case GUI_EVENT_KEY_RIGHT_PRESS:
            nav_btn_handleEvent(NavBtnEvent_Right_Pressed);
            break;
        case GUI_EVENT_KEY_DOWN_PRESS:
            nav_btn_handleEvent(NavBtnEvent_Down_Pressed);
            break;
        case GUI_EVENT_KEY_ENTER_RELEASE:
            nav_btn_handleEvent(NavBtnEvent_OK_Released);
            break;
        case GUI_EVENT_KEY_LEFT_RELEASE:
            nav_btn_handleEvent(NavBtnEvent_Left_Released);
            break;
        case GUI_EVENT_KEY_UP_RELEASE:
            nav_btn_handleEvent(NavBtnEvent_Up_Released);
            break;
        case GUI_EVENT_KEY_RIGHT_RELEASE:
            nav_btn_handleEvent(NavBtnEvent_Right_Released);
            break;
        case GUI_EVENT_KEY_DOWN_RELEASE:
            nav_btn_handleEvent(NavBtnEvent_Down_Released);
            break;
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
