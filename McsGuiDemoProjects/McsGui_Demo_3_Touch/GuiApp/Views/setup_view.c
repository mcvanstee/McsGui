#include "setup_view.h"

#include "gui_app.h"
#include "gui_custom_components.h"
#include "gui_component_extensions.h"
#include "gui_settings.h"
#include "fs_file_search.h"


#include "logger.h"


#define SV_PANE_WIDTH (STYLE_DISPLAY_WIDTH - 53 - 10)
#define SV_SAVE_BUTTON_ID 1

static void sv_create(View_s *p_view);
static void sv_addSaveSwitch(Grid_s *p_grid);
static void sv_addSelectTempUnit(Grid_s *p_grid, Pane_s *p_pane);
static void sv_addIntervalInput(Grid_s *p_grid);
static void sv_addMaxPointsInput(Grid_s *p_grid);

static void sv_checkboxSelectionChanged(Checkbox_s *p_checkbox);
static void sv_intervalChanged(NumberInput_s *p_numberInput);
static void sv_maxPointsChanged(NumberInput_s *p_numberInput);
static void sv_tempUnitChanged(RadioGroup_s *p_radioGroup);

static void sv_saveButtonPressed(Button_s *p_button);
static void sv_showSaveButton(void);

static GuiSettings_s m_settings;

void setup_view_navigateTo(void)
{
	view_navigateTo(&g_guiApp.view, sv_create);
}

static void sv_create(View_s *p_view)
{
	gui_app_clearView();

	m_settings = settings_getSettings();

    Item_s *p_item = item_newInit();
    base_setPosition(p_item, STYLE_VIEW_X, STYLE_VIEW_Y);
    base_setSize(p_item, STYLE_VIEW_WIDTH, STYLE_DISPLAY_HEIGHT);
    view_addComponent(p_view, p_item);

    Pane_s *p_pane = pane_newInit();
    p_pane->borderPane = true;
    base_setSize(p_pane, SV_PANE_WIDTH, (STYLE_DISPLAY_HEIGHT - 20));
    base_addNewInitAnchor(p_pane);
    anchor_setTopAnchor(p_pane, p_item, Gui_Anchor_Top);
    anchor_setLeftAnchor(p_pane, p_item, Gui_Anchor_Left);
    anchor_setTopMargin(p_pane, 10);
    anchor_setLeftMargin(p_pane, 10);
    view_addComponent(p_view, p_pane);

	Grid_s *p_grid = grid_newInit();
	grid_setColumns(p_grid, 2);
	grid_setRows(p_grid, 4);
	grid_setColumnSpacing(p_grid, 10);
	grid_setRowSpacing(p_grid, 10);
	base_addNewInitAnchor(&p_grid->base);
	anchor_setTopAnchor(p_grid, p_pane, Gui_Anchor_Top);
	anchor_setLeftAnchor(p_grid, p_pane, Gui_Anchor_Left);
	anchor_setTopMargin(p_grid, 10);
	anchor_setLeftMargin(p_grid, 10);
	pane_addComponent(p_pane, p_grid);

	sv_addSaveSwitch(p_grid);
	sv_addSelectTempUnit(p_grid, p_pane);
	sv_addIntervalInput(p_grid);
	sv_addMaxPointsInput(p_grid);

	Button_s *p_saveButton = button_new();
	button_initBmp(p_saveButton, FILE_KEY_TEXT_SAVE);
	button_setOnReleased(p_saveButton, sv_saveButtonPressed);
	gui_app_translate(p_saveButton);
	base_setSize(p_saveButton, 80, 30);
	base_setBackground(p_saveButton, COLOR_ACCENT_BLUE);
	base_setVisible(p_saveButton, false);
	base_addNewInitTouch(&p_saveButton->base);
	base_addNewInitAnchor(p_saveButton);
	base_setId(p_saveButton, SV_SAVE_BUTTON_ID);
	anchor_setRightAnchor(p_saveButton, p_pane, Gui_Anchor_Right);
	anchor_setBottomAnchor(p_saveButton, p_pane, Gui_Anchor_Bottom);
	anchor_setRightMargin(p_saveButton, 10);
	anchor_setBottomMargin(p_saveButton, 10);
	pane_addComponent(p_pane, p_saveButton);
}

static void sv_addSaveSwitch(Grid_s *p_grid)
{
    Label_s *p_saveLabel = label_new();
    label_initBmp(p_saveLabel, FILE_KEY_TEXT_SAVE_REC);
    gui_app_translate(p_saveLabel);
    base_setHeight(p_saveLabel, 30);
    grid_addComponent(p_grid, p_saveLabel);

    Checkbox_s *p_checkbox = custom_cmp_createCheckbox(
            FILE_KEY_ICON_SWITCH, m_settings.saveData, sv_checkboxSelectionChanged);
    base_setSize(p_checkbox, 50, 30);
    grid_addComponent(p_grid, p_checkbox);
}

static void sv_addSelectTempUnit(Grid_s *p_grid, Pane_s *p_pane)
{
    Label_s *p_tempUnitLabel = label_new();
    label_initBmp(p_tempUnitLabel, FILE_KEY_TEXT_UNITS);
    gui_app_translate(p_tempUnitLabel);
    base_setHeight(p_tempUnitLabel, 30);
    grid_addComponent(p_grid, p_tempUnitLabel);

    Row_s *p_row = row_newInit();
    row_setSpacing(p_row, 20);
    grid_addComponent(p_grid, p_row);

    RadioGroup_s *p_radioGroup = radiogroup_newInit();
    radiogroup_setOnSelectionChanged(p_radioGroup, sv_tempUnitChanged);
    pane_addComponent(p_pane, p_radioGroup);

    CheckboxLabel_s *p_celsiusCBL = checkbox_label_new();
    checkbox_label_init_1(p_celsiusCBL, FILE_KEY_TEXT_DEG_CEL);
    base_setWidth(p_celsiusCBL, 60);
    row_addComponent(p_row, p_celsiusCBL);
    radiogroup_addButton(p_radioGroup, &p_celsiusCBL->checkBox);

    CheckboxLabel_s *p_fahrenheitCBL = checkbox_label_new();
    checkbox_label_init_1(p_fahrenheitCBL, FILE_KEY_TEXT_DEG_FAR);
    base_setWidth(p_fahrenheitCBL, 60);
    row_addComponent(p_row, p_fahrenheitCBL);
    radiogroup_addButton(p_radioGroup, &p_fahrenheitCBL->checkBox);

    radiogroup_setSelectedAtIndex(p_radioGroup, m_settings.temperatureUnit);
}

static void sv_addIntervalInput(Grid_s *p_grid)
{
    Label_s *p_intervalLabel = label_new();
    label_initBmp(p_intervalLabel, FILE_KEY_TEXT_INTERVAL);
    gui_app_translate(p_intervalLabel);
    base_setHeight(p_intervalLabel, 30);
    grid_addComponent(p_grid, p_intervalLabel);

    NumberInput_s *p_numberInput = num_input_newInit();
    num_input_setMaximumValue(p_numberInput, 10);
    num_input_setValue(p_numberInput, m_settings.interval);
    num_input_setOnValueChanged(p_numberInput, sv_intervalChanged);
    grid_addComponent(p_grid, p_numberInput);
}

static void sv_addMaxPointsInput(Grid_s *p_grid)
{
    Label_s *p_maxPointsLabel = label_new();
    label_initBmp(p_maxPointsLabel, FILE_KEY_TEXT_MAX_DATA_POINTS);
    gui_app_translate(p_maxPointsLabel);
    base_setHeight(p_maxPointsLabel, 30);
    grid_addComponent(p_grid, p_maxPointsLabel);

    NumberInput_s *p_maxPointsInput = num_input_newInit();
    num_input_setMaximumValue(p_maxPointsInput, 100);
    num_input_setValue(p_maxPointsInput, m_settings.maxDataPoints);
    num_input_setOnValueChanged(p_maxPointsInput, sv_maxPointsChanged);
    grid_addComponent(p_grid, p_maxPointsInput);
}

static void sv_checkboxSelectionChanged(Checkbox_s *p_checkbox)
{
    base_display(p_checkbox);
    m_settings.saveData = p_checkbox->checked;

    sv_showSaveButton();
}

static void sv_intervalChanged(NumberInput_s *p_numberInput)
{
    m_settings.interval = p_numberInput->value;
    sv_showSaveButton();
}

static void sv_maxPointsChanged(NumberInput_s *p_numberInput)
{
    m_settings.maxDataPoints = p_numberInput->value;
    sv_showSaveButton();
}

static void sv_tempUnitChanged(RadioGroup_s *p_radioGroup)
{
    m_settings.temperatureUnit = radiogroup_getSelectedIndex(p_radioGroup);
    sv_showSaveButton();
}

static void sv_saveButtonPressed(Button_s *p_button)
{
    g_guiApp.temperatureUnit = m_settings.temperatureUnit;
    settings_setSettings(m_settings);
    settings_save();

    base_setVisible(p_button, false);

	Label_s label;
	label_initBmpPosSize(
	        &label, FILE_KEY_TEXT_SAVED,
	        p_button->base.x, p_button->base.y,
	        p_button->base.width, p_button->base.height);
	base_setBackground(&label, COLOR_BACKGROUND);
	base_display(&label);
}

static void sv_showSaveButton(void)
{
    Button_s *p_saveButton = (Button_s *)view_getComponentById(&g_guiApp.view, SV_SAVE_BUTTON_ID);

    if (!p_saveButton->base.visible)
    {
        base_setVisible(p_saveButton, true);
        base_display(p_saveButton);
    }
}
