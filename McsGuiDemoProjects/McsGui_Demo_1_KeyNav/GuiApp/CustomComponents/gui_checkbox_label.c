#include "gui_checkbox_label.h"

#include <stddef.h>
#include <string.h>

#include "gui_app.h"
#include "Graphics/gui_graphics.h"
#include "Core/gui_memory.h"

#define GUI_CHECKBOX_LABEL_BUFFER_SIZE 10

#define CHECKBOX_WIDTH 150
#define CHECKBOX_HEIGHT 30

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticCheckBoxLabelMemInUse[GUI_CHECKBOX_LABEL_BUFFER_SIZE];
static CheckboxLabel_s staticCheckBoxLabelMem[GUI_CHECKBOX_LABEL_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void checkbox_label_onDisplay(BaseComponent_s *p_baseComponent);
static void checkbox_label_focusChanged(BaseComponent_s *p_baseComponent);
static void checbox_label_setCheckboxIcon(CheckboxLabel_s *p_checkboxLabel);
static void checkbox_label_selectionChanged(Checkbox_s *p_checkbox);


CheckboxLabel_s* checkbox_label_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
    return gui_mem_malloc(sizeof(CheckboxLabel_s));
#else
    for (uint32_t i = 0; i < GUI_CHECKBOX_LABEL_BUFFER_SIZE; i++)
    {
        if (!staticCheckBoxLabelMemInUse[i])
        {
            staticCheckBoxLabelMemInUse[i] = true;

            return &staticCheckBoxLabelMem[i];
        }
    }

    gui_log_write(GUI_LOG_LEVEL_ERROR, "No CheckboxLabel_s static memory");

    return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

CheckboxLabel_s* checkbox_label_newInit(void)
{
    CheckboxLabel_s *p_checkboxLabel = checkbox_label_new();
    if (p_checkboxLabel != NULL)
    {
        checkbox_label_init(p_checkboxLabel);
    }

    return p_checkboxLabel;
}

void checkbox_label_delete(BaseComponent_s *p_checkboxLabelBase)
{
    base_clear(p_checkboxLabelBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_checkboxLabelBase, sizeof(CheckboxLabel_s));
#else
    for (uint32_t i = 0; i < GUI_CHECKBOX_LABEL_BUFFER_SIZE; i++)
    {
        if (&staticCheckBoxLabelMem[i].checkBox.base == p_checkboxLabelBase)
        {
            staticCheckBoxLabelMemInUse[i] = false;
            break;
        }
    }
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void checkbox_label_init(CheckboxLabel_s *p_checkboxLabel)
{
    checkbox_init(&p_checkboxLabel->checkBox);
    p_checkboxLabel->label = FILE_KEY_NONE;
    base_setDimensions(p_checkboxLabel, CHECKBOX_WIDTH, CHECKBOX_HEIGHT);
    base_setOnDelete(p_checkboxLabel, checkbox_label_delete);
    base_setOnDisplay(p_checkboxLabel, checkbox_label_onDisplay);
    keynav_init(&p_checkboxLabel->keyNavigation);
    base_addKeyNavigation(p_checkboxLabel, &p_checkboxLabel->keyNavigation);
    base_setOnFocusChanged(&p_checkboxLabel->checkBox.base, checkbox_label_focusChanged);
    checkbox_setOnSelectionChanged(&p_checkboxLabel->checkBox, checkbox_label_selectionChanged);
}

void checkbox_label_initLabel(CheckboxLabel_s *p_checkboxLabel, file_key_e label)
{
    checkbox_label_init(p_checkboxLabel);
    p_checkboxLabel->label = label;
}

static void checkbox_label_onDisplay(BaseComponent_s *p_baseComponent)
{
    CheckboxLabel_s *p_checkboxLabel = (CheckboxLabel_s*)p_baseComponent;
    checbox_label_setCheckboxIcon(p_checkboxLabel);
    theme_applyThemeProperty(&p_checkboxLabel->checkBox);
    base_setHorizontalAlignment(p_baseComponent, Gui_Align_Left);
    graphics_displayComponent(p_baseComponent);

    Label_s label;
    label_initBmpPos(&label, p_checkboxLabel->label, p_baseComponent->x, p_baseComponent->y);
    theme_applyThemeProperty(&label);
    base_setHeight(&label, CHECKBOX_HEIGHT);
    base_setHorizontalAlignment(&label.base, Gui_Align_Left);
    base_setLeftPadding(&label.base, 30);
    gui_app_translate(&label);
    base_display(&label);
}

static void checbox_label_setCheckboxIcon(CheckboxLabel_s *p_checkboxLabel)
{
    Checkbox_s *p_checkbox = &p_checkboxLabel->checkBox;

    const uint32_t icon = p_checkbox->checked ? FILE_KEY_ICON_PANE_RADIO_BUTTON_CHECKED : FILE_KEY_ICON_PANE_RADIO_BUTTON_UNCHECKED;
    base_setBmpKey(p_checkbox, icon);

    if (p_checkbox->base.focused)
    {
        theme_applyCursorColorProperty(p_checkbox);
    }
    else
    {
        base_setProperty(p_checkbox, FILE_PROPERTY_ACCENT_COLOR, PROPERTY_ACCENT_COLOR_VALUE_WHITE);
    }
}

static void checkbox_label_focusChanged(BaseComponent_s *p_baseComponent)
{
    base_display(p_baseComponent);
}

static void checkbox_label_selectionChanged(Checkbox_s *p_checkbox)
{
    base_display(p_checkbox);
}

