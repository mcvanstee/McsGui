#include "gui_radiogroup.h"

#include <stddef.h>

#include "McsGui/Utils/gui_memory.h"


#if GUI_USE_DYNAMIC_MEMORY
/**
 * @brief Creates a new malloced RadioGroup component.
 * @return Pointer to the malloced memory.
 *
 * @warning The returned component is not initialized.
 *
 */
RadioGroup_s *radiogroup_new(void)
{
    return gui_mem_malloc(sizeof(RadioGroup_s));
}
#endif /* GUI_USE_DYNAMIC_MEMORY */


/**
 * @brief Delete the RadioGroup component. This functions calls the gui_mem_free function to free the allocated memory.
 * @param[in] p_radioGroupBase Pointer to the RadioGroup component to be freed.
 *
 */
void radiogroup_delete(BaseComponent_s *p_radioGroupBase)
{
    base_clear(p_radioGroupBase);
#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_radioGroupBase, sizeof(RadioGroup_s));
    p_radioGroupBase = NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}


/**
 * @brief Initialize the RadioGroup component to the default values.
 * @param[in] p_radioGroup Pointer to the RadioGroup component to be freed.
 *
 */
void radiogroup_init(RadioGroup_s *p_radioGroup)
{
    base_initParentComp(&p_radioGroup->base, radiogroup_delete);
    p_radioGroup->numberOfButtons = 0;
    p_radioGroup->onSelectionChanged = NULL;
}


/**
 * @brief Add a Checkbox button to the RadioGroup.
 * @param[in] p_radioGroup Pointer to the RadioGroup component.
 * @param[in] p_checkbox Pointer to the Checkbox component
 *
 */
void radiogroup_addButton(RadioGroup_s *p_radioGroup, Checkbox_s *p_checkbox)
{
    p_checkbox->checked = false;
    p_checkbox->p_radioGroupBase = &p_radioGroup->base;

    if (p_radioGroup->base.p_childList == NULL)
    {
        p_radioGroup->base.p_childList = &p_checkbox->base;
        p_radioGroup->numberOfButtons = 1;

        return;
    }

    BaseComponent_s *p_iterator = p_radioGroup->base.p_childList;
    while (p_iterator->p_nextBaseComponent != NULL)
    {
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    p_iterator->p_nextBaseComponent = &p_checkbox->base;
    p_radioGroup->numberOfButtons += 1;
}


/**
 * @brief Set the on-selection-changed callback function.
 * @param[in] p_radioGroup Pointer to the RadioGroup component.
 * @param[in] onSelectionChanged Pointer to the callback function, with a RadioGroup pointer variable.
 *
 */
void radiogroup_setOnSelectionChg(RadioGroup_s *p_radioGroup, void (*onSelectionChanged)(RadioGroup_s *p_radioGroupChanged))
{
    p_radioGroup->onSelectionChanged = onSelectionChanged;
}


/**
 * @brief Set the selection of the RadioGroup. The checked propertie is set and the onSelectionChanged callback function is called.
 * @param[in] p_radioGroup Pointer to the RadioGroup component.
 * @param[in] selected
 *
 */
void radiogroup_setSelected(RadioGroup_s *p_radioGroup, Checkbox_s *p_checkboxToSelect)
{
    if (p_checkboxToSelect->checked)
    {
        return;
    }

    Checkbox_s *p_checkboxToUnSelect = radiogroup_getSelected(p_radioGroup);

    if (p_checkboxToUnSelect != NULL)
    {
        checkbox_setSelection(p_checkboxToUnSelect, false);
    }

    checkbox_setSelection(p_checkboxToSelect, true);

    if (p_radioGroup->onSelectionChanged != NULL)
    {
        p_radioGroup->onSelectionChanged(p_radioGroup);
    }
}


/**
 * @brief Set the Checkbox at index selected.
 * @param[in] p_radioGroup Pointer to the RadioGroup component.
 * @param[in] index.
 *
 */
void radiogroup_setSelectedAtIndex(RadioGroup_s *p_radioGroup, const int8_t index)
{
    Checkbox_s *p_checkboxToSelect = radiogroup_getButtonAtIndex(p_radioGroup, index);
    if (p_checkboxToSelect->checked)
    {
        return;
    }

    Checkbox_s *p_checkboxToUnSelect = radiogroup_getSelected(p_radioGroup);
    if (p_checkboxToUnSelect != NULL)
    {
        checkbox_setSelection(p_checkboxToUnSelect, false);
    }

    checkbox_setSelection(p_checkboxToSelect, true);

    if (p_radioGroup->onSelectionChanged != NULL)
    {
        p_radioGroup->onSelectionChanged(p_radioGroup);
    }
}


/**
 * @brief Get the selected Checkbox of the RadioGroup.
 * @param[in] p_radioGroup Pointer to the RadioGroup component.
 * @return Pointer to selected Checkbox.
 *
 */
Checkbox_s *radiogroup_getSelected(RadioGroup_s *p_radioGroup)
{
    BaseComponent_s *p_iterator = p_radioGroup->base.p_childList;
    while (p_iterator != NULL)
    {
        Checkbox_s *p_checkbox = (Checkbox_s *)p_iterator;
        if (p_checkbox->checked)
        {
            return p_checkbox;
        }

        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return NULL;
}


/**
 * @brief Get the Checkbox at index.
 * @param[in] p_radioGroup Pointer to the RadioGroup component.
 * @param[in] index.
 * @return Pointer to the Checkbox at index.
 *
 */
Checkbox_s *radiogroup_getButtonAtIndex(RadioGroup_s *p_radioGroup, const int8_t index)
{
    if ((index < 0) || (index >= p_radioGroup->numberOfButtons))
    {
        return NULL;
    }

    BaseComponent_s *p_iterator = p_radioGroup->base.p_childList;

    for (int32_t buttonIndex = 0; buttonIndex < index; buttonIndex++)
    {
        p_iterator = p_iterator->p_nextBaseComponent;

        if (p_iterator == NULL)
        {
            return NULL;
        }
    }

    return (Checkbox_s *)p_iterator;
}


/**
 * @brief Get the Checkbox at index.
 * @param[in] p_radioGroup Pointer to the RadioGroup component.
 * @return Index of the selected Checkbox.
 *
 */
int8_t radiogroup_getSelectedIndex(RadioGroup_s *p_radioGroup)
{
    int8_t selectedIndex = 0;
    BaseComponent_s *p_iterator = p_radioGroup->base.p_childList;

    while (p_iterator != NULL)
    {
        Checkbox_s *p_checkbox = (Checkbox_s *)p_iterator;
        if (p_checkbox->checked)
        {
            return selectedIndex;
        }

        selectedIndex += 1;
        p_iterator = p_iterator->p_nextBaseComponent;
    }

    return -1;
}

bool radiogroup_handleButtonPressed(BaseComponent_s *p_radioGroupBase, Checkbox_s *p_checkboxPressed)
{
    if (p_checkboxPressed->checked)
    {
        return true;
    }

    radiogroup_setSelected(
            (RadioGroup_s *)p_radioGroupBase, p_checkboxPressed);

    return true;
}


/*** end of file ***/
