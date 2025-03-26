#include "measurement_view.h"

#include <stdio.h>

#include "main.h"
#include "gui_app.h"
#include "gui_custom_components.h"
#include "gui_settings.h"
#include "fonts.h"
#include "fs_file_search.h"
#include "temp_recorder.h"
#include "logger.h"

#define MSMV_PANE_WIDTH 203

#define MSMV_TEXTBLOCK_TEMP_ID 1
#define MSMV_TEXTBLOCK_MIN_TEMP_ID 2
#define MSMV_TEXTBLOCK_MAX_TEMP_ID 3
#define MSMV_TEXTBLOCK_REC_NUMBER_ID 4
#define MSMV_START_BUTTON_ID 5
#define MSMV_STOP_BUTTON_ID 6

static void msmv_create(View_s *p_view);
static void msmv_addTempPaneContent(Pane_s *p_tempPane);
static void msmv_addInfoPaneContent(Pane_s *p_infoPane);
static TextBlock_s *msmv_addTempLabel(Grid_s *p_grid, int32_t textBlockId, file_key_e icon);
static TextBlock_s *msmv_addInfoLabel(Grid_s *p_grid, file_key_e icon);
static void msmv_handleEvent(View_s *p_view, GuiEvent_s *p_event);
static void msmv_updateRecNumber(void);

static void msmv_startButtonPressed(Button_s *p_startButton);
static void msmv_startButtonReleased(Button_s *p_startButton);
static void msmv_stopButtonPressed(Button_s *p_stopButton);
static void msmv_stopButtonReleased(Button_s *p_stopButton);

static float_t m_temperature_C;
static float_t m_minTemperature_C;
static float_t m_maxTemperature_C;


void measurement_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, msmv_create);
}

static void msmv_create(View_s *p_view)
{
    gui_app_clearView();
    view_setHandleEvent(p_view, msmv_handleEvent);

    m_temperature_C = getAdcTemp();
    m_minTemperature_C = m_temperature_C;
    m_maxTemperature_C = m_temperature_C;

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setSize(p_item, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT);
    view_addComponent(p_view, p_item);

    Pane_s *p_tempPane = pane_newInit();
    p_tempPane->borderPane = true;
    base_setSize(p_tempPane, MSMV_PANE_WIDTH, (STYLE_DISPLAY_HEIGHT / 2) - 10);
    base_addNewInitAnchor(p_tempPane);
    anchor_setTopAnchor(p_tempPane, p_item, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_tempPane, p_item, Gui_Anchor_Left);
    anchor_setTopMargin(p_tempPane, 10);
    anchor_setLeftMargin(p_tempPane, 10);
    view_addComponent(p_view, p_tempPane);
    msmv_addTempPaneContent(p_tempPane);

    Pane_s *p_infoPane = pane_newInit();
    p_infoPane->borderPane = true;
    base_setSize(p_infoPane, MSMV_PANE_WIDTH, (STYLE_DISPLAY_HEIGHT / 2) - 10);
    base_addNewInitAnchor(p_infoPane);
    anchor_setTopAnchor(p_infoPane, p_tempPane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_infoPane, p_tempPane, Gui_Anchor_Right);
    anchor_setLeftMargin(p_infoPane, 11);
    view_addComponent(p_view, p_infoPane);
    msmv_addInfoPaneContent(p_infoPane);

    Item_s *p_btnItem = item_newInit();
    base_setSize(p_btnItem, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT / 2);
    base_addNewInitAnchor(p_btnItem);
    anchor_setHorizontalCenter(p_btnItem, p_item);
    anchor_setBottomAnchor(p_btnItem, p_item, Gui_Anchor_Bottom);
    view_addComponent(p_view, p_btnItem);

    Button_s *p_startRecButton = button_new();
    button_initBmp(p_startRecButton, FILE_KEY_BUTTON_PLAY);
    button_setOnPressed(p_startRecButton, msmv_startButtonPressed);
    button_setOnReleased(p_startRecButton, msmv_startButtonReleased);
    base_addNewInitAnchor(p_startRecButton);
    anchor_setCenterInParent(p_startRecButton, p_btnItem);
    base_setId(p_startRecButton, MSMV_START_BUTTON_ID);
    base_addNewInitTouch(&p_startRecButton->base);
    item_addComponent(p_btnItem, p_startRecButton);

    Button_s *p_stopRecButton = button_new();
    button_initBmp(p_stopRecButton, FILE_KEY_BUTTON_STOP);
    button_setOnPressed(p_stopRecButton, msmv_stopButtonPressed);
    button_setOnReleased(p_stopRecButton, msmv_stopButtonReleased);
    base_addNewInitAnchor(p_stopRecButton);
    anchor_setCenterInParent(p_stopRecButton, p_btnItem);
    base_setId(p_stopRecButton, MSMV_STOP_BUTTON_ID);
    base_addNewInitTouch(&p_stopRecButton->base);
    base_setVisible(p_stopRecButton, false);
    item_addComponent(p_btnItem, p_stopRecButton);

    if (temp_recorder_isRecording())
    {
        base_setVisible(p_startRecButton, false);
        base_setVisible(p_stopRecButton, true);
    }
}

static void msmv_addTempPaneContent(Pane_s *p_tempPane)
{
    Grid_s *p_grid = grid_newInit();
    grid_setColumns(p_grid, 3);
    grid_setRows(p_grid, 3);
    grid_setColumnSpacing(p_grid, 10);
    grid_setRowSpacing(p_grid, 10);
    base_addNewInitAnchor(&p_grid->base);
    anchor_setTopAnchor(p_grid, p_tempPane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_grid, p_tempPane, Gui_Anchor_Left);
    anchor_setTopMargin(p_grid, 10);
    anchor_setLeftMargin(p_grid, 10);
    pane_addComponent(p_tempPane, p_grid);

    TextBlock_s *p_tempTB = msmv_addTempLabel(p_grid, MSMV_TEXTBLOCK_TEMP_ID, FILE_KEY_NONE);
    TextBlock_s *p_maxTempTB = msmv_addTempLabel(p_grid, MSMV_TEXTBLOCK_MAX_TEMP_ID, FILE_KEY_ICON_ARROW_UP_SMALL);
    TextBlock_s *p_minTempTB = msmv_addTempLabel(p_grid, MSMV_TEXTBLOCK_MIN_TEMP_ID, FILE_KEY_ICON_ARROW_DOWN_SMALL);
    unit_converter_getTemperatureStr(
            p_tempTB->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, m_temperature_C, g_guiApp.temperatureUnit);
    textblock_setText(p_minTempTB, "--.-");
    textblock_setText(p_maxTempTB, "--.-");
}

static void msmv_addInfoPaneContent(Pane_s *p_infoPane)
{
    Grid_s *p_grid = grid_newInit();
    grid_setColumns(p_grid, 2);
    grid_setRows(p_grid, 2);
    grid_setColumnSpacing(p_grid, 10);
    grid_setRowSpacing(p_grid, 10);
    base_addNewInitAnchor(&p_grid->base);
    anchor_setTopAnchor(p_grid, p_infoPane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_grid, p_infoPane, Gui_Anchor_Left);
    anchor_setTopMargin(p_grid, 10);
    anchor_setLeftMargin(p_grid, 10);
    pane_addComponent(p_infoPane, p_grid);

    TextBlock_s *p_hashtagTB = textblock_newInit();
    textblock_setFont(p_hashtagTB, FONT_KEY_TEXT_LARGE_ROBOTO_18_R_DEFAULT_TEXT);
    textblock_setText(p_hashtagTB, "#");
    grid_addComponent(p_grid, p_hashtagTB);

    TextBlock_s *p_recNumberTB = textblock_newInit();
    textblock_setFont(p_recNumberTB, FONT_KEY_TEXT_LARGE_ROBOTO_18_R_DEFAULT_TEXT);
    base_setId(p_recNumberTB, MSMV_TEXTBLOCK_REC_NUMBER_ID);
    base_setBackground(p_recNumberTB, COLOR_BACKGROUND);
    base_setHorizontalAlignment(p_recNumberTB, Gui_Align_Left);
    grid_addComponent(p_grid, p_recNumberTB);

    if (temp_recorder_isRecording())
    {
        char recNumberStr[GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH_INC_NULL] = {0};
        const int32_t recNumber = temp_recorder_getNumSamples();
        snprintf(recNumberStr, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%ld", recNumber);
        textblock_setText(p_recNumberTB, recNumberStr);
    }
    else
    {
        textblock_setText(p_recNumberTB, "0");
    }

    char intervalStr[GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH_INC_NULL] = {0};
    snprintf(intervalStr, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%d s", (int16_t)settings_getInterval());
    TextBlock_s *p_intervalTB = msmv_addInfoLabel(p_grid, FILE_KEY_ICON_PULSE);
    textblock_setText(p_intervalTB, intervalStr);
}

static TextBlock_s *msmv_addTempLabel(Grid_s *p_grid, int32_t textBlockId, file_key_e arrowIcon)
{
    Label_s *p_thermometerIcon = label_newInit();
    label_setBmpKey(p_thermometerIcon, FILE_KEY_ICON_THERMOMETER);
    grid_addComponent(p_grid, p_thermometerIcon);

    if (arrowIcon != FILE_KEY_NONE)
    {
        Label_s *p_arrowLabel = label_newInit();
        label_setBmpKey(p_arrowLabel, arrowIcon);
        base_addNewInitAnchor(p_arrowLabel);
        anchor_setBottomAnchor(p_arrowLabel, p_thermometerIcon, Gui_Anchor_Bottom);
        anchor_setLeftAnchor(p_arrowLabel, p_thermometerIcon, Gui_Anchor_Right);
        base_addChild(&p_thermometerIcon->base, &p_arrowLabel->base);
    }

    TextBlock_s *p_tempTextRec = textblock_newInit();
    textblock_setFont(p_tempTextRec, FONT_KEY_TEXT_LARGE_ROBOTO_18_R_DEFAULT_TEXT);
    base_setId(p_tempTextRec, textBlockId);
    grid_addComponent(p_grid, p_tempTextRec);

    const file_key_e tempUnitKey = (TemperatureUnit_Celsius == g_guiApp.temperatureUnit) ?
            FILE_KEY_TEXT_DEG_CEL : FILE_KEY_TEXT_DEG_FAR;

    Label_s *p_tempUnitLabel = label_newInit();
    label_initBmp(p_tempUnitLabel, tempUnitKey);
    base_setHeight(p_tempUnitLabel, 24);
    base_setTopPadding(p_tempUnitLabel, 2);
    grid_addComponent(p_grid, p_tempUnitLabel);

    return p_tempTextRec;
}

static TextBlock_s *msmv_addInfoLabel(Grid_s *p_grid, file_key_e icon)
{
    Label_s *p_icon = label_newInit();
    label_setBmpKey(p_icon, icon);
    grid_addComponent(p_grid, p_icon);

    TextBlock_s *p_textBlock = textblock_newInit();
    textblock_setFont(p_textBlock, FONT_KEY_TEXT_LARGE_ROBOTO_18_R_DEFAULT_TEXT);
    grid_addComponent(p_grid, p_textBlock);

    return p_textBlock;
}

static void msmv_startButtonPressed(Button_s *p_startButton)
{
    base_setBmpKey(p_startButton, FILE_KEY_BUTTON_PLAY_PRESSED);
    base_display(p_startButton);
}

static void msmv_startButtonReleased(Button_s *p_startButton)
{
    const bool recordingStarted = temp_recorder_start();
    Button_s *p_stopButton = (Button_s *)view_getComponentById(&g_guiApp.view, MSMV_STOP_BUTTON_ID);

    base_setBmpKey(p_startButton, FILE_KEY_BUTTON_PLAY);

    if (recordingStarted)
    {
        base_setVisible(p_startButton, false);

        base_setVisible(p_stopButton, true);
        base_display(p_stopButton);

        msmv_updateRecNumber();
        ControlBar_s *p_controlBar = (ControlBar_s *)view_getComponentById(&g_guiApp.view, CONTROL_BAR_ID);
        control_bar_setButtonIcon(p_controlBar, 1, FILE_KEY_ICON_BULLSEYE);
        control_bar_drawButton(p_controlBar, 1);

        log_info("Recording started");
    }
    else
    {
        base_setBmpKey(p_stopButton, FILE_KEY_BUTTON_STOP);
        base_setVisible(p_stopButton, false);

        base_setVisible(p_startButton, true);
        base_display(p_startButton);

        log_error("Recording failed to start");
    }
}

static void msmv_stopButtonPressed(Button_s *p_stopButton)
{
    base_setBmpKey(p_stopButton, FILE_KEY_BUTTON_STOP_PRESSED);
    base_display(p_stopButton);
}

static void msmv_stopButtonReleased(Button_s *p_stopButton)
{
    base_setBmpKey(p_stopButton, FILE_KEY_BUTTON_STOP);
    base_setVisible(p_stopButton, false);

    Button_s *p_startButton = (Button_s *)view_getComponentById(&g_guiApp.view, MSMV_START_BUTTON_ID);
    base_setVisible(p_startButton, true);
    base_display(p_startButton);

    temp_recorder_stop();

    ControlBar_s *p_controlBar = (ControlBar_s *)view_getComponentById(&g_guiApp.view, CONTROL_BAR_ID);
    control_bar_setButtonIcon(p_controlBar, 1, FILE_KEY_ICON_BULLSEYE);
    control_bar_drawButton(p_controlBar, 1);

    log_info("Recording stopped");
}

static void msmv_handleEvent(View_s *p_view, GuiEvent_s *p_event)
{
    if (p_event->event == GUI_EVENT_TOUCH_ON_RELEASED)
    {
        Button_s *p_startButton = (Button_s *)view_getComponentById(p_view, MSMV_START_BUTTON_ID);
        Button_s *p_stopButton = (Button_s *)view_getComponentById(p_view, MSMV_STOP_BUTTON_ID);

        if (p_startButton->base.visible && (p_startButton->base.bmpKey == FILE_KEY_BUTTON_PLAY_PRESSED))
        {
            msmv_startButtonReleased(p_startButton);
        }
        else if (p_stopButton->base.visible && (p_stopButton->base.bmpKey == FILE_KEY_BUTTON_STOP_PRESSED))
        {
            msmv_stopButtonReleased(p_stopButton);
        }
    }
    else if (p_event->event == CUSTOM_GUI_EVENT_MEASREMANT_READY)
    {
        m_temperature_C = getAdcTemp();

        m_minTemperature_C = (m_temperature_C < m_minTemperature_C) ?
                m_temperature_C : m_minTemperature_C;

        m_maxTemperature_C = (m_temperature_C > m_maxTemperature_C) ?
                m_temperature_C : m_maxTemperature_C;

        TextBlock_s *p_tempTB = (TextBlock_s*) view_getComponentById(p_view, MSMV_TEXTBLOCK_TEMP_ID);
        unit_converter_getTemperatureStr(
                p_tempTB->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, m_temperature_C, g_guiApp.temperatureUnit);

        TextBlock_s *p_minTempTB = (TextBlock_s*) view_getComponentById(p_view, MSMV_TEXTBLOCK_MIN_TEMP_ID);
        unit_converter_getTemperatureStr(
                p_minTempTB->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, m_minTemperature_C, g_guiApp.temperatureUnit);

        TextBlock_s *p_maxTempTB = (TextBlock_s*) view_getComponentById(p_view, MSMV_TEXTBLOCK_MAX_TEMP_ID);
        unit_converter_getTemperatureStr(
                p_maxTempTB->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, m_maxTemperature_C, g_guiApp.temperatureUnit);

        base_display(p_tempTB);
        base_display(p_minTempTB);
        base_display(p_maxTempTB);
    }
    else if (p_event->event == CUSTOM_GUI_EVENT_REC_NUMBER_CHANGED)
    {
        msmv_updateRecNumber();
    }
}

static void msmv_updateRecNumber(void)
{
    TextBlock_s *p_recNumberTB = (TextBlock_s*) view_getComponentById(&g_guiApp.view, MSMV_TEXTBLOCK_REC_NUMBER_ID);
    char recNumberStr[GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH_INC_NULL] = {0};
    const int32_t recNumber = temp_recorder_getNumSamples();
    snprintf(recNumberStr, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%ld", recNumber);
    textblock_setText(p_recNumberTB, recNumberStr);
    base_display(p_recNumberTB);
}

