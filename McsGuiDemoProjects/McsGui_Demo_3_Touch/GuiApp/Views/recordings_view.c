#include "recordings_view.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "gui_app.h"
#include "gui_component_extensions.h"
#include "gui_custom_components.h"
#include "fonts.h"
#include "fs_file_search.h"
#include "temp_recorder.h"
#include "utils_math.h"

#include "ff.h"

#define RV_NUM_RECORDINGS_ITEMS 20
#define RV_NUM_READINGS_ITEMS 4
#define RV_PANEL_WIDTH 203
#define RV_PANEL_HEIGHT (STYLE_DISPLAY_HEIGHT - 40)
#define RV_PANEL_HEIGHT_SMALL ((RV_PANEL_HEIGHT / 2) - 8)
#define RV_SCROLLBAR_WIDTH 40
#define RV_INFO_LABEL_HEIGHT 23

#define RV_INTERVAL_TEXTBLOCK_ID 1
#define RV_READINGS_TEXTBLOCK_ID 2
#define RV_TEMP_MAX_TEXTBLOCK_ID 3
#define RV_TEMP_MIN_TEXTBLOCK_ID 4
#define RV_RECORDINGS_LISTVIEW_ID 5
#define RV_READINGS_LISTVIEW_ID 6
#define RV_DELETE_BUTTON_ID 7

typedef struct
{
    int8_t id;
    char start_time[16];
    char filename[64];
} Recording_s;

typedef struct
{
    uint8_t id;
    uint32_t temp;
} Reading_s;


static void rv_create(View_s *p_view);
static void rc_createRecordingsGroupBox(View_s *p_view, Item_s *p_item);
static void rc_createInfoPane(Item_s *p_item);
static void rc_createInfoLabel(Grid_s *p_grid, file_key_e label, uint8_t textBlockId);
static void rc_createInfoTempLabel(Grid_s *p_grid, file_key_e arrowIcon, uint8_t textBlockId);
static void rc_createReadingsPane(Item_s *p_item);
static void rc_addRecordingItems(ListView_s *p_listView);
static void rc_addReadingItems(ListView_s *p_listView, int32_t itemsVisible);
static void rc_displayRecordingItem(BaseComponent_s *p_itemBase);
static void rc_displayReadingItem(BaseComponent_s *p_itemBase);
static void rc_activeItemChanged(ListView_s *p_listView);
static void rc_getFileNameActiveItem(char *p_filename, int32_t strLength, ListView_s *p_listView);
static void rc_updateVisibilityDeleteButton(ListView_s *p_listView);
static void rc_displayHeaderInfo(RecFileHeader_s *p_header);
static void rc_displayReadings(FIL *p_file, int32_t startIndex);
static void rv_moveReadingsUpButtonPressed(void);
static void rc_moveReadingsDownButtonPressed(void);
static void rc_loadRecordings(void);
static void rc_getIdAndStartTimeFromFileName(FILINFO *p_fileInfo);
static void rc_deleteRecording(void);
static int rc_sortRecordingsId(const void *p_rec1, const void *p_rec2);


static RecFileHeader_s m_selectedRecordingHeader = {0};
static Recording_s m_recordings[RV_NUM_RECORDINGS_ITEMS] = {0};
static uint8_t m_numRecordings = 0;
static Reading_s m_readings[RV_NUM_READINGS_ITEMS] = {0};
static int32_t m_currentReadingIndex = 0;

void recordings_view_navigateTo(void)
{
    view_navigateTo(&g_guiApp.view, rv_create);
}

static void rv_create(View_s *p_view)
{
    gui_app_clearView();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setSize(p_item, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT);
    view_addComponent(p_view, p_item);

    Label_s *p_title = label_new();
    label_initBmp(p_title, FILE_KEY_TITLE_RECORDINGS);
    base_addNewInitAnchor(p_title);
    anchor_setTopAnchor(p_title, p_item, Gui_Anchor_Top);
    anchor_setHorizontalCenter(p_title, p_item);
    anchor_setTopMargin(p_title, 5);
    item_addComponent(p_item, p_title);

    rc_createRecordingsGroupBox(p_view, p_item);
    rc_createInfoPane(p_item);
    rc_createReadingsPane(p_item);
}

static void rc_createRecordingsGroupBox(View_s *p_view, Item_s *p_item)
{
    Pane_s *p_pane = pane_newInit();
    pane_setBorderPane(p_pane, true);
    base_setSize(&p_pane->base, RV_PANEL_WIDTH, RV_PANEL_HEIGHT);
    base_addNewInitAnchor(p_pane);
    anchor_setTopAnchor(p_pane, p_item, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_pane, p_item, Gui_Anchor_Left);
    anchor_setTopMargin(p_pane, 30);
    anchor_setLeftMargin(p_pane, 10);
    view_addComponent(p_view, p_pane);

    Rectangle_s *p_rect = rectangle_newInit();
    rectangle_initFillSize(p_rect, COLOR_SEPARATOR, p_pane->base.width, 1);
    base_addNewInitAnchor(p_rect);
    anchor_setTopAnchor(p_rect, p_pane, Gui_Anchor_Top);
    anchor_setTopMargin(p_rect, 30);
    anchor_setLeftAnchor(p_rect, p_pane, Gui_Anchor_Left);
    pane_addComponent(p_pane, p_rect);

    Label_s *p_idLabel = label_new();
    label_initBmp(p_idLabel, FILE_KEY_TITLE_ID);
    base_addNewInitAnchor(p_idLabel);
    anchor_setBottomAnchor(p_idLabel, p_rect, Gui_Anchor_Bottom);
    anchor_setLeftAnchor(p_idLabel, p_pane, Gui_Anchor_Left);
    anchor_setBottomMargin(p_idLabel, 2);
    anchor_setLeftMargin(p_idLabel, 15);
    pane_addComponent(p_pane, p_idLabel);

    Label_s *p_startTimeLabel = label_new();
    label_initBmp(p_startTimeLabel, FILE_KEY_TITLE_START);
    base_addNewInitAnchor(p_startTimeLabel);
    anchor_setBottomAnchor(p_startTimeLabel, p_rect, Gui_Anchor_Bottom);
    anchor_setLeftAnchor(p_startTimeLabel, p_idLabel, Gui_Anchor_Right);
    anchor_setBottomMargin(p_startTimeLabel, 2);
    anchor_setLeftMargin(p_startTimeLabel, 53);
    pane_addComponent(p_pane, p_startTimeLabel);

    const uint8_t rowHight = 27;
    const uint8_t itemsVisible = 9;
    const uint16_t listViewHigh = rowHight * itemsVisible;

    ListView_s *p_listView = listview_newInit();
    listview_setRowHight(p_listView, rowHight);
    p_listView->itemsVisible = itemsVisible;
    p_listView->onActiveItemChanged = rc_activeItemChanged;
    base_setSize(p_listView, p_pane->base.width - RV_SCROLLBAR_WIDTH, listViewHigh);
    base_setId(&p_listView->base, RV_RECORDINGS_LISTVIEW_ID);
    base_addNewInitTouch(p_listView);
    base_addNewInitAnchor(p_listView);
    anchor_setTopAnchor(p_listView, p_rect, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_listView, p_pane, Gui_Anchor_Left);
    anchor_setTopMargin(p_listView, 1);
    anchor_setLeftMargin(p_listView, 1);
    pane_addComponent(p_pane, p_listView);
    rc_addRecordingItems(p_listView);

    ScrollBar_s *p_scrollBar = scrollbar_newInit();
    scrollbar_setWidth(p_scrollBar, RV_SCROLLBAR_WIDTH);
    scrollbar_setHeight(p_scrollBar, p_listView->base.height);
    scrollbar_setButtonSize(p_scrollBar, RV_SCROLLBAR_WIDTH, RV_SCROLLBAR_WIDTH);
    scrollbar_setThumbAreaWidth(p_scrollBar, 16);
    scrollbar_setUpIcon(p_scrollBar, FILE_KEY_ICON_SCROLL_UP);
    scrollbar_setDownIcon(p_scrollBar, FILE_KEY_ICON_SCROLL_DOWN);
    scrollbar_addListview(p_scrollBar, p_listView);
    scrollbar_setThumbAreaColor(p_scrollBar, COLOR_BACKGROUND);
    scrollbar_setThumbColor(p_scrollBar, COLOR_ACCENT_RED);
    scrollbar_setThumbRadius(p_scrollBar, 4);
    anchor_setTopAnchor(p_scrollBar, p_listView, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_scrollBar, p_listView, Gui_Anchor_Right);
    pane_addComponent(p_pane, p_scrollBar);
}

static void rc_createInfoPane(Item_s *p_item)
{
    Pane_s *p_pane = pane_newInit();
    pane_setBorderPane(p_pane, true);
    base_setSize(&p_pane->base, RV_PANEL_WIDTH, RV_PANEL_HEIGHT_SMALL);
    base_addNewInitAnchor(p_pane);
    anchor_setTopAnchor(p_pane, p_item, Gui_Anchor_Top);
    anchor_setRightAnchor(p_pane, p_item, Gui_Anchor_Right);
    anchor_setTopMargin(p_pane, 30);
    anchor_setRightMargin(p_pane, 11);
    item_addComponent(p_item, p_pane);

    Button_s *p_deleteButton = button_new();
    button_initBmp(p_deleteButton, FILE_KEY_ICON_TRASH);
    button_setOnPressedEvent(p_deleteButton, rc_deleteRecording);
    base_setId(&p_deleteButton->base, RV_DELETE_BUTTON_ID);
    base_setVisible(p_deleteButton, false);
    base_setSize(&p_deleteButton->base, 30, 30);
    base_addNewInitTouch(p_deleteButton);
    base_addNewInitAnchor(p_deleteButton);
    anchor_setTopAnchor(p_deleteButton, p_pane, Gui_Anchor_Top);
    anchor_setRightAnchor(p_deleteButton, p_pane, Gui_Anchor_Right);
    anchor_setTopMargin(p_deleteButton, 5);
    anchor_setRightMargin(p_deleteButton, 5);
    pane_addComponent(p_pane, p_deleteButton);

    Grid_s *p_grid = grid_newInit();
    grid_setColumns(p_grid, 3);
    grid_setRows(p_grid, 4);
    grid_setColumnSpacing(p_grid, 10);
    grid_setRowSpacing(p_grid, 5);
    base_addNewInitAnchor(&p_grid->base);
    anchor_setTopAnchor(p_grid, p_pane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_grid, p_pane, Gui_Anchor_Left);
    anchor_setTopMargin(p_grid, 10);
    anchor_setLeftMargin(p_grid, 10);
    pane_addComponent(p_pane, p_grid);

    rc_createInfoLabel(p_grid, FILE_KEY_ICON_PULSE, RV_INTERVAL_TEXTBLOCK_ID);
    rc_createInfoLabel(p_grid, FILE_KEY_TEXT_HASHTAG, RV_READINGS_TEXTBLOCK_ID);
    rc_createInfoTempLabel(p_grid, FILE_KEY_ICON_ARROW_UP_SMALL, RV_TEMP_MAX_TEXTBLOCK_ID);
    rc_createInfoTempLabel(p_grid, FILE_KEY_ICON_ARROW_DOWN_SMALL, RV_TEMP_MIN_TEXTBLOCK_ID);
}

static void rc_createInfoLabel(Grid_s *p_grid, file_key_e label, uint8_t textBlockId)
{
    Label_s *p_label = label_new();
    label_initBmp(p_label, label);
    base_setHorizontalAlignment(p_label, Gui_Align_Left);
    grid_addComponent(p_grid, p_label);

    TextBlock_s *p_textBlock = textblock_newInit();
    textblock_setFont(p_textBlock, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_DEFAULT_TEXT);
    textblock_setText(p_textBlock, " ");
    base_setBackground(p_textBlock, COLOR_BACKGROUND);
    base_setHorizontalAlignment(p_textBlock, Gui_Align_Left);
    base_setId(p_textBlock, textBlockId);
    grid_addComponent(p_grid, p_textBlock);

    Label_s *p_dummyLabel = label_newInit();
    label_initBmp(p_dummyLabel, FILE_KEY_NONE);
    base_setVisible(p_dummyLabel, false);
    grid_addComponent(p_grid, p_dummyLabel);
}

static void rc_createInfoTempLabel(Grid_s *p_grid, file_key_e arrowIcon, uint8_t textBlockId)
{
    TextBlock_s *p_tempTextRec = textblock_newInit();
    textblock_setFont(p_tempTextRec, FONT_KEY_TEXT_LARGE_ROBOTO_18_R_DEFAULT_TEXT);
    textblock_setText(p_tempTextRec, "T");
    grid_addComponent(p_grid, p_tempTextRec);

    Label_s *p_arrowLabel = label_newInit();
    label_setBmpKey(p_arrowLabel, arrowIcon);
    base_addNewInitAnchor(p_arrowLabel);
    anchor_setBottomAnchor(p_arrowLabel, p_tempTextRec, Gui_Anchor_Bottom);
    anchor_setLeftAnchor(p_arrowLabel, p_tempTextRec, Gui_Anchor_Right);
    base_addChild(&p_tempTextRec->base, &p_arrowLabel->base);

    TextBlock_s *p_textBlock = textblock_newInit();
    textblock_setFont(p_textBlock, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_DEFAULT_TEXT);
    textblock_setText(p_textBlock, " ");
    base_setBackground(p_textBlock, COLOR_BACKGROUND);
    base_setHorizontalAlignment(p_textBlock, Gui_Align_Left);
    base_setId(p_textBlock, textBlockId);
    grid_addComponent(p_grid, p_textBlock);

    const file_key_e tempUnitKey = (TemperatureUnit_Celsius == g_guiApp.temperatureUnit) ?
            FILE_KEY_TEXT_DEG_CEL : FILE_KEY_TEXT_DEG_FAR;

    Label_s *p_unitLabel = label_new();
    label_initBmp(p_unitLabel, tempUnitKey);
    base_setWidth(p_unitLabel, 30);
    grid_addComponent(p_grid, p_unitLabel);
}

static void rc_createReadingsPane(Item_s *p_item)
{
    Pane_s *p_pane = pane_newInit();
    pane_setBorderPane(p_pane, true);
    base_setSize(&p_pane->base, RV_PANEL_WIDTH, RV_PANEL_HEIGHT_SMALL);
    base_addNewInitAnchor(p_pane);
    anchor_setBottomAnchor(p_pane, p_item, Gui_Anchor_Bottom);
    anchor_setRightAnchor(p_pane, p_item, Gui_Anchor_Right);
    anchor_setBottomMargin(p_pane, 10);
    anchor_setRightMargin(p_pane, 11);
    item_addComponent(p_item, p_pane);

    Label_s *p_readingsLabel = label_new();
    label_initBmp(p_readingsLabel, FILE_KEY_TEXT_HASHTAG);
    base_addNewInitAnchor(p_readingsLabel);
    anchor_setTopAnchor(p_readingsLabel, p_pane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_readingsLabel, p_pane, Gui_Anchor_Left);
    anchor_setTopMargin(p_readingsLabel, 7);
    anchor_setLeftMargin(p_readingsLabel, 12);
    pane_addComponent(p_pane, p_readingsLabel);

    TextBlock_s *p_tempTextRec = textblock_newInit();
    textblock_setFont(p_tempTextRec, FONT_KEY_TEXT_LARGE_ROBOTO_18_R_DEFAULT_TEXT);
    textblock_setText(p_tempTextRec, "T");
    base_addNewInitAnchor(p_tempTextRec);
    anchor_setTopAnchor(p_tempTextRec, p_pane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_tempTextRec, p_readingsLabel, Gui_Anchor_Right);
    anchor_setTopMargin(p_tempTextRec, 5);
    anchor_setLeftMargin(p_tempTextRec, 47);
    pane_addComponent(p_pane, p_tempTextRec);

    TextBlock_s *p_parenthesesOpen = textblock_newInit();
    textblock_setFont(p_parenthesesOpen, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_DEFAULT_TEXT);
    textblock_setText(p_parenthesesOpen, "(");
    base_addNewInitAnchor(p_parenthesesOpen);
    anchor_setTopAnchor(p_parenthesesOpen, p_pane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_parenthesesOpen, p_tempTextRec, Gui_Anchor_Right);
    anchor_setTopMargin(p_parenthesesOpen, 5);
    anchor_setLeftMargin(p_parenthesesOpen, 6);
    pane_addComponent(p_pane, p_parenthesesOpen);

    const file_key_e tempUnitKey = (TemperatureUnit_Celsius == g_guiApp.temperatureUnit) ?
            FILE_KEY_TEXT_DEG_CEL : FILE_KEY_TEXT_DEG_FAR;

    Label_s *p_unitLabel = label_new();
    label_initBmp(p_unitLabel, tempUnitKey);
    base_setWidth(p_unitLabel, 30);
    base_addNewInitAnchor(p_unitLabel);
    anchor_setTopAnchor(p_unitLabel, p_pane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_unitLabel, p_tempTextRec, Gui_Anchor_Right);
    anchor_setTopMargin(p_unitLabel, 10);
    anchor_setLeftMargin(p_unitLabel, 6);
    pane_addComponent(p_pane, p_unitLabel);

    TextBlock_s *p_parenthesesClose = textblock_newInit();
    textblock_setFont(p_parenthesesClose, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_DEFAULT_TEXT);
    textblock_setText(p_parenthesesClose, ")");
    base_addNewInitAnchor(p_parenthesesClose);
    anchor_setTopAnchor(p_parenthesesClose, p_pane, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_parenthesesClose, p_tempTextRec, Gui_Anchor_Right);
    anchor_setTopMargin(p_parenthesesClose, 5);
    anchor_setLeftMargin(p_parenthesesClose, 30);
    pane_addComponent(p_pane, p_parenthesesClose);

    Rectangle_s *p_rect = rectangle_newInit();
    rectangle_initFillSize(p_rect, COLOR_SEPARATOR, p_pane->base.width, 1);
    base_addNewInitAnchor(p_rect);
    anchor_setTopAnchor(p_rect, p_pane, Gui_Anchor_Top);
    anchor_setTopMargin(p_rect, 30);
    anchor_setRightAnchor(p_rect, p_pane, Gui_Anchor_Right);
    pane_addComponent(p_pane, p_rect);

    const uint8_t rowHight = 25;
    const uint8_t itemsVisible = 4;
    const uint16_t listViewHigh = rowHight * itemsVisible;

    ListView_s *p_listView = listview_newInit();
    listview_setRowHight(p_listView, rowHight);
    p_listView->itemsVisible = itemsVisible;
    base_setSize(p_listView, p_pane->base.width - RV_SCROLLBAR_WIDTH, listViewHigh);
    base_setId(&p_listView->base, RV_READINGS_LISTVIEW_ID);
    base_addNewInitTouch(p_listView);
    base_addNewInitAnchor(p_listView);
    anchor_setTopAnchor(p_listView, p_rect, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_listView, p_pane, Gui_Anchor_Left);
    anchor_setTopMargin(p_listView, 1);
    anchor_setLeftMargin(p_listView, 1);
    pane_addComponent(p_pane, p_listView);
    rc_addReadingItems(p_listView, itemsVisible);

    Button_s *p_upButton = button_new();
    button_initBmp(p_upButton, FILE_KEY_ICON_SCROLL_UP);
    button_setOnPressedEvent(p_upButton, rv_moveReadingsUpButtonPressed);
    base_setSize(&p_upButton->base, RV_SCROLLBAR_WIDTH, RV_SCROLLBAR_WIDTH);
    base_addNewInitTouch(p_upButton);
    base_addNewInitAnchor(p_upButton);
    anchor_setTopAnchor(p_upButton, p_rect, Gui_Anchor_Top);
    anchor_setRightAnchor(p_upButton, p_pane, Gui_Anchor_Right);
    pane_addComponent(p_pane, p_upButton);

    Button_s *p_downButton = button_new();
    button_initBmp(p_downButton, FILE_KEY_ICON_SCROLL_DOWN);
    button_setOnPressedEvent(p_downButton, rc_moveReadingsDownButtonPressed);
    base_setSize(&p_downButton->base, RV_SCROLLBAR_WIDTH, RV_SCROLLBAR_WIDTH);
    base_addNewInitTouch(p_downButton);
    base_addNewInitAnchor(p_downButton);
    anchor_setBottomAnchor(p_downButton, p_pane, Gui_Anchor_Bottom);
    anchor_setRightAnchor(p_downButton, p_pane, Gui_Anchor_Right);
    pane_addComponent(p_pane, p_downButton);
}

static void rc_addRecordingItems(ListView_s *p_listView)
{
    rc_loadRecordings();
    qsort(m_recordings, m_numRecordings, sizeof(Recording_s), rc_sortRecordingsId);

    for (uint8_t i = 0; i < m_numRecordings; i++)
    {
        ListViewItem_s *p_listItem = listviewitem_newInit();
        listview_addItem(p_listView, p_listItem);
        p_listItem->base.p_data = &m_recordings[i];
        p_listItem->onPressed = listview_ext_itemPressed;
        base_setOnDisplay(p_listItem, rc_displayRecordingItem);
    }
}

static void rc_addReadingItems(ListView_s *p_listView, int32_t itemsVisible)
{
    for (uint8_t i = 0; i < itemsVisible; i++)
    {
        ListViewItem_s *p_listItem = listviewitem_newInit();
        listview_addItem(p_listView, p_listItem);
        p_listItem->base.p_data = &m_readings[i];
        base_setOnDisplay(p_listItem, rc_displayReadingItem);
    }
}

static void rc_displayRecordingItem(BaseComponent_s *p_itemBase)
{
    Recording_s *p_recording = (Recording_s*)p_itemBase->p_data;
    ListViewItem_s *p_listViewItem = (ListViewItem_s*)p_itemBase;
    ListView_s *p_listView = (ListView_s*)p_itemBase->p_parent;

    const bool activeItem = (p_listView->activeIndex == p_listViewItem->index);
    const uint8_t fontId = (activeItem) ? FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_PANE_TEXT : FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_DEFAULT_TEXT;
    const Color_t backgroundColor = (activeItem) ? COLOR_PANE : COLOR_BACKGROUND;

    Item_s item;
    item_init(&item);
    base_setPosition(&item, p_itemBase->x, p_itemBase->y);
    base_setSize(&item, p_itemBase->width, p_itemBase->height);
    base_setBackground(&item, backgroundColor);

    char p_text[36] = {0};
    sprintf(p_text, "% 3d     %s", p_recording->id, p_recording->start_time);

    TextBlock_s idTextBlock;
    textblock_initText(&idTextBlock, p_text);
    textblock_setFont(&idTextBlock, fontId);
    GuiAnchor_s anchor;
    anchor_init(&anchor);
    base_addAnchor(&idTextBlock, &anchor);
    anchor_setVerticalCenter(&idTextBlock, &item);
    anchor_setLeftAnchor(&idTextBlock, &item, Gui_Anchor_Left);
    anchor_setLeftMargin(&idTextBlock, 5);

    item_addComponent(&item, &idTextBlock);
    base_display(&item);
}

static void rc_displayReadingItem(BaseComponent_s *p_itemBase)
{
    Reading_s *p_reading = (Reading_s*)p_itemBase->p_data;

    Item_s item;
    item_init(&item);
    base_setPosition(&item, p_itemBase->x, p_itemBase->y);
    base_setSize(&item, p_itemBase->width, p_itemBase->height);
    base_setBackground(&item, COLOR_BACKGROUND);

    const float_t tempDivider = (float_t)utils_math_ipow(10, TEMP_RECORDER_DECIMALS);
    char p_text[16] = {0};
    unit_converter_getTemperatureStr(p_text, sizeof(p_text), p_reading->temp / tempDivider, g_guiApp.temperatureUnit);

    TextBlock_s textBlock;
    textblock_init(&textBlock);
    textblock_setFont(&textBlock, FONT_KEY_TEXT_REGULAR_ROBOTO_16_R_DEFAULT_TEXT);
    snprintf(textBlock.text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "% d       %s", p_reading->id, p_text);
    GuiAnchor_s anchor;
    anchor_init(&anchor);
    base_addAnchor(&textBlock, &anchor);
    anchor_setVerticalCenter(&textBlock, &item);
    anchor_setLeftAnchor(&textBlock, &item, Gui_Anchor_Left);
    anchor_setLeftMargin(&textBlock, 5);

    item_addComponent(&item, &textBlock);
    base_display(&item);
}

static void rc_activeItemChanged(ListView_s *p_listView)
{
    listview_ext_activeItemChanged(p_listView);
    rc_updateVisibilityDeleteButton(p_listView);

    char filename[256] = {0};
    rc_getFileNameActiveItem(filename, sizeof(filename), p_listView);

    FIL file = {0};
    FRESULT openResult = f_open(&file, filename, FA_READ);

    if (FR_OK == openResult)
    {
        UINT bytesRead = 0;
        f_read(&file, &m_selectedRecordingHeader, sizeof(RecFileHeader_s), &bytesRead);

        if (bytesRead == sizeof(RecFileHeader_s))
        {
            m_currentReadingIndex = 0;
            rc_displayHeaderInfo(&m_selectedRecordingHeader);
            rc_displayReadings(&file, 0);
        }
        else
        {
            gui_log_error("Failed to read header");
        }
    }
    else
    {
        gui_log_error("Failed to open file");
    }

    f_close(&file);
}

static void rc_getFileNameActiveItem(char *p_filename, int32_t strLength, ListView_s *p_listView)
{
    snprintf(p_filename, strLength, "Recordings/new/%s", m_recordings[p_listView->activeIndex].filename);
}

static void rc_updateVisibilityDeleteButton(ListView_s *p_listView)
{
    if (p_listView->previousActiveIndex < 0)
    {
        Button_s *p_deleteButton = (Button_s*) view_getComponentById(&g_guiApp.view, RV_DELETE_BUTTON_ID);
        base_setVisible(p_deleteButton, true);
        base_display(&p_deleteButton->base);
    }
}

static void rc_displayHeaderInfo(RecFileHeader_s *p_header)
{
    TextBlock_s *p_idTextBlock = (TextBlock_s *)view_getComponentById(&g_guiApp.view, RV_INTERVAL_TEXTBLOCK_ID);
    snprintf(p_idTextBlock->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%lu", p_header->interval);
    base_display(&p_idTextBlock->base);

    TextBlock_s *p_readingsTextBlock = (TextBlock_s *)view_getComponentById(&g_guiApp.view, RV_READINGS_TEXTBLOCK_ID);
    snprintf(p_readingsTextBlock->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, "%ld", p_header->num_samples);
    base_display(&p_readingsTextBlock->base);

    const float_t tempDivider = (float_t)utils_math_ipow(10, TEMP_RECORDER_DECIMALS);

    TextBlock_s *p_tempMaxTextBlock = (TextBlock_s *)view_getComponentById(&g_guiApp.view, RV_TEMP_MAX_TEXTBLOCK_ID);
    unit_converter_getTemperatureStr(
        p_tempMaxTextBlock->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, p_header->max_temp / tempDivider, g_guiApp.temperatureUnit);
    base_display(&p_tempMaxTextBlock->base);

    TextBlock_s *p_tempMinTextBlock = (TextBlock_s *)view_getComponentById(&g_guiApp.view, RV_TEMP_MIN_TEXTBLOCK_ID);
    unit_converter_getTemperatureStr(
        p_tempMinTextBlock->text, GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH, p_header->min_temp / tempDivider, g_guiApp.temperatureUnit);
    base_display(&p_tempMinTextBlock->base);
}

static void rc_displayReadings(FIL *p_file, int32_t startIndex)
{
    uint32_t temp = 0;
    UINT bytesToRead = sizeof(uint32_t);
    UINT bytesRead = 0;

    ListView_s *p_readingsListView = (ListView_s *)view_getComponentById(&g_guiApp.view, RV_READINGS_LISTVIEW_ID);

    for (uint32_t i = 0; i < RV_NUM_READINGS_ITEMS; i++)
    {
        f_read(p_file, &temp, bytesToRead, &bytesRead);

        if (bytesRead == bytesToRead)
        {
            m_readings[i].id = startIndex + i + 1;
            m_readings[i].temp = temp;
        }
        else
        {
            m_readings[i].id = 0;
            m_readings[i].temp = 0;
        }
    }

    base_display(&p_readingsListView->base);
}

static void rv_moveReadingsUpButtonPressed(void)
{
    if (m_currentReadingIndex == 0)
    {
        return;
    }

    m_currentReadingIndex -= RV_NUM_READINGS_ITEMS;

    if (m_currentReadingIndex < 0)
    {
        m_currentReadingIndex = 0;
    }

    ListView_s *p_listView = (ListView_s*) view_getComponentById(&g_guiApp.view, RV_RECORDINGS_LISTVIEW_ID);

    char filename[256] = {0};
    rc_getFileNameActiveItem(filename, sizeof(filename), p_listView);

    FIL file = {0};
    FRESULT openResult = f_open(&file, filename, FA_READ);

    if (FR_OK == openResult)
    {
        f_lseek(&file, sizeof(RecFileHeader_s) + (m_currentReadingIndex * sizeof(uint32_t)));
        rc_displayReadings(&file, m_currentReadingIndex);
    }
    else
    {
        gui_log_error("Failed to open file");
    }

    f_close(&file);
}

static void rc_moveReadingsDownButtonPressed(void)
{
    if (m_currentReadingIndex == (m_selectedRecordingHeader.num_samples - RV_NUM_READINGS_ITEMS))
    {
        return;
    }

    m_currentReadingIndex += RV_NUM_READINGS_ITEMS;

    if (m_selectedRecordingHeader.num_samples < (m_currentReadingIndex + RV_NUM_READINGS_ITEMS))
    {
        m_currentReadingIndex = m_selectedRecordingHeader.num_samples - RV_NUM_READINGS_ITEMS;
    }

    ListView_s *p_listView = (ListView_s *)view_getComponentById(&g_guiApp.view, RV_RECORDINGS_LISTVIEW_ID);

    char filename[256] = {0};
    rc_getFileNameActiveItem(filename, sizeof(filename), p_listView);

    FIL file = {0};
    FRESULT openResult = f_open(&file, filename, FA_READ);

    if (FR_OK == openResult)
    {
        f_lseek(&file, sizeof(RecFileHeader_s) + (m_currentReadingIndex * sizeof(uint32_t)));
        rc_displayReadings(&file, m_currentReadingIndex);
    }
    else
    {
        gui_log_error("Failed to open file");
    }

    f_close(&file);
}

static void rc_loadRecordings(void)
{
    m_numRecordings = 0;

    DIR dir = {0};
    FILINFO fileInfo = {0};
    FRESULT openDirResult = f_opendir(&dir, "Recordings/new");

    if (FR_OK == openDirResult)
    {
        for (;;)
        {
            FRESULT readDirResult = f_readdir(&dir, &fileInfo);
            if ((FR_OK != readDirResult) || (fileInfo.fname[0] == '\0'))
            {
                break;
            }

            if ((fileInfo.fattrib & AM_DIR) == 0)
            {
                rc_getIdAndStartTimeFromFileName(&fileInfo);
                m_numRecordings += 1;

                if (m_numRecordings >= RV_NUM_RECORDINGS_ITEMS)
                {
                    break;
                }
            }
        }
    }

    f_closedir(&dir);
}

static void rc_getIdAndStartTimeFromFileName(FILINFO *p_fileInfo)
{
    m_recordings[m_numRecordings].filename[0] = '\0';
    strcpy(m_recordings[m_numRecordings].filename, p_fileInfo->fname);

    const int32_t strLength = strlen(p_fileInfo->fname);
    int32_t idStartIndex = 0;
    int32_t idEndIndex = 0;

    for (int32_t i = 0; i < strLength; i++)
    {
        if ((idStartIndex == 0) && (p_fileInfo->fname[i] == '_'))
        {
            idStartIndex = i + 1;
        }
        else if ((idStartIndex > 0) && (p_fileInfo->fname[i] == '_'))
        {
            idEndIndex = i - 1;
        }
        else if (p_fileInfo->fname[i] == '-')
        {
            p_fileInfo->fname[i] = ':';
        }
        else
        {
        }
    }

    const int32_t idStrLength = idEndIndex - idStartIndex + 1;

    char idStr[16] = {0};
    memcpy(idStr, &p_fileInfo->fname[idStartIndex], idStrLength);
    m_recordings[m_numRecordings].id = atol(idStr);

    const int32_t timeStartIndex = idEndIndex + 2;
    const int32_t timeStrLength = 8;
    memcpy(m_recordings[m_numRecordings].start_time, &p_fileInfo->fname[timeStartIndex], timeStrLength);
}

static void rc_deleteRecording(void)
{
    ListView_s *p_listView = (ListView_s*) view_getComponentById(&g_guiApp.view, RV_RECORDINGS_LISTVIEW_ID);

    if ((p_listView != NULL) && (p_listView->activeIndex >= 0))
    {
        char filename[256] = {0};
        sprintf(filename, "Recordings/new/%s", m_recordings[p_listView->activeIndex].filename);
        f_unlink(filename);

        recordings_view_navigateTo();
    }
    else
    {
        gui_log_error("No active recording");
    }
}

static int rc_sortRecordingsId(const void *p_rec1, const void *p_rec2)
{
    return ((Recording_s*) p_rec1)->id - ((Recording_s*) p_rec2)->id;
}
