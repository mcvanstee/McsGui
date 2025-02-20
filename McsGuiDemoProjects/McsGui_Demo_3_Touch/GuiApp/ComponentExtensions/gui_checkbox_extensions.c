#include "gui_checkbox_extensions.h"

#include "Graphics/gui_graphics.h"

static void custom_cmp_displayCheckbox(BaseComponent_s *p_base);

Checkbox_s *custom_cmp_createCheckbox(
    const uint32_t bmpKey, bool checked, void (*onSelectionChanged)(Checkbox_s *p_checkboxChanged))
{
    Checkbox_s *p_checkbox = checkbox_newInit();
    if (p_checkbox == NULL)
    {
        return NULL;
    }

    checkbox_initBmp(p_checkbox, bmpKey);
    base_setOnDisplay(p_checkbox, custom_cmp_displayCheckbox);
    checkbox_setSelection(p_checkbox, checked);
    checkbox_setOnSelectionChanged(p_checkbox, onSelectionChanged);
    base_addNewInitTouch(&p_checkbox->base);

    return p_checkbox;
}

static void custom_cmp_displayCheckbox(BaseComponent_s *p_base)
{
    Checkbox_s *p_checkbox = (Checkbox_s *)p_base;

    const property_value_selected_e selected = p_checkbox->checked ?
            PROPERTY_SELECTED_VALUE_TRUE : PROPERTY_SELECTED_VALUE_FALSE;
    base_setProperty(p_checkbox, FILE_PROPERTY_SELECTED, selected);

    graphics_displayComponent(p_base);
}
