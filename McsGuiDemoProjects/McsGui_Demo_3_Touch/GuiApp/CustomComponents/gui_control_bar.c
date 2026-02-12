#include "gui_control_bar.h"

#include "gui_app.h"
#include "colors.h"

#include "Graphics/gui_graphics.h"
#include "Core/gui_log.h"

static void control_bar_onDisplay(BaseComponent_s *p_baseComponent);
static bool control_bar_handleEvent(BaseComponent_s *p_baseComponent, const GuiEvent_s *p_event);

static void control_bar_displayBtn(file_key_e icon, uint16_t x, uint16_t y, bool selected);
static void control_bar_displayBtnIndex(ControlBar_s *p_controlBar, uint8_t buttonIndex);
static int8_t control_bar_getPressedBtnIdx(ControlBar_s *p_controlBar, uint16_t yPressed);

void control_bar_init(ControlBar_s *p_controlBar)
{
	base_initParentComp(&p_controlBar->base, control_bar_delete);
	base_setPosition(&p_controlBar->base, 0, 0);
	base_setDimensions(&p_controlBar->base, STYLE_CONTROL_BAR_WIDTH, STYLE_CONTROL_BAR_HEIGHT);
	base_setOnDisplay(&p_controlBar->base, control_bar_onDisplay);
	base_setOnHandleEvent(&p_controlBar->base, control_bar_handleEvent);

	touch_init(&p_controlBar->touch);
	base_addTouch(&p_controlBar->base, &p_controlBar->touch);

	for (uint8_t i = 0; i < CONTROL_BAR_BUTTON_COUNT; i++)
	{
		p_controlBar->iconList[i] = FILE_KEY_NONE;
		p_controlBar->onPressed[i] = NULL;
	}

	p_controlBar->selectedButton = 0;
}

void control_bar_delete(BaseComponent_s *p_controlBarBase)
{

}

void control_bar_setSelected(ControlBar_s *p_controlBar, uint8_t buttonIndex)
{
	if (buttonIndex >= CONTROL_BAR_BUTTON_COUNT)
	{
		gui_log_write(GUI_LOG_LEVEL_ERROR, "Invalid button index");

		return;
	}

	p_controlBar->selectedButton = buttonIndex;
}

void control_bar_addButton(ControlBar_s *p_controlBar, uint8_t buttonIndex, file_key_e icon, void (*onPressed)(void))
{
	if (buttonIndex >= CONTROL_BAR_BUTTON_COUNT)
	{
		gui_log_write(GUI_LOG_LEVEL_ERROR, "Invalid button index");

		return;
	}

	p_controlBar->iconList[buttonIndex] = icon;
	p_controlBar->onPressed[buttonIndex] = onPressed;
}

void control_bar_setButtonIcon(ControlBar_s *p_controlBar, uint8_t buttonIndex, file_key_e icon)
{
    if (buttonIndex >= CONTROL_BAR_BUTTON_COUNT)
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "Invalid button index");

        return;
    }

    p_controlBar->iconList[buttonIndex] = icon;
}

void control_bar_drawButton(ControlBar_s *p_controlBar, uint8_t buttonIndex)
{
    if (buttonIndex >= CONTROL_BAR_BUTTON_COUNT)
    {
        gui_log_write(GUI_LOG_LEVEL_ERROR, "Invalid button index");

        return;
    }

    const uint16_t y = CONTROL_BAR_BUTTON_HEIGHT * buttonIndex;
    const bool selected = (buttonIndex == p_controlBar->selectedButton);
    control_bar_displayBtn(p_controlBar->iconList[buttonIndex], 0, y, selected);
}

static void control_bar_onDisplay(BaseComponent_s *p_baseComponent)
{
	ControlBar_s *p_controlBar = (ControlBar_s*)p_baseComponent;

	if (!p_controlBar->base.visible)
	{
		return;
	}

	uint16_t y = 0;

	for (uint8_t i = 0; i < CONTROL_BAR_BUTTON_COUNT; i++)
	{
		if (p_controlBar->iconList[i] != FILE_KEY_NONE)
		{
			const bool selected = (i == p_controlBar->selectedButton);
			control_bar_displayBtn(p_controlBar->iconList[i], 0, y, selected);
		}

		y += CONTROL_BAR_BUTTON_HEIGHT;
	}
}

static bool control_bar_handleEvent(BaseComponent_s *p_baseComponent, const GuiEvent_s *p_event)
{
	ControlBar_s *p_controlBar = (ControlBar_s*)p_baseComponent;
    bool eventHandled = false;

    if (p_event->event == GUI_EVENT_TOUCH_ON_RELEASED)
    {
    	const uint16_t yPosPressed = ((uint16_t)p_event->eventArgs[3] << 8) + p_event->eventArgs[2];
    	const int8_t buttonPressedIndex = control_bar_getPressedBtnIdx(p_controlBar, yPosPressed);
    	const int8_t selectedButtonIndex = p_controlBar->selectedButton;

		if ((buttonPressedIndex != -1) && (buttonPressedIndex != selectedButtonIndex))
		{
			p_controlBar->selectedButton = buttonPressedIndex;

			if (p_controlBar->onPressed[buttonPressedIndex] != NULL)
			{
				p_controlBar->onPressed[buttonPressedIndex]();
			}

			if (p_controlBar->base.visible)
			{
				control_bar_displayBtnIndex(p_controlBar, buttonPressedIndex);
				control_bar_displayBtnIndex(p_controlBar, selectedButtonIndex);
		    }

			eventHandled = true;
		}
    }

    return eventHandled;
}

static void control_bar_displayBtn(file_key_e icon, uint16_t x, uint16_t y, bool selected)
{
	const property_value_selection_e propertyValue = selected ? PROPERTY_SELECTION_VALUE_TRUE : PROPERTY_SELECTION_VALUE_FALSE;

	Label_s label;
	label_initBmpPosSize(&label, icon, x, y, CONTROL_BAR_BUTTON_WIDTH, CONTROL_BAR_BUTTON_HEIGHT);
	base_setProperty(&label.base, FILE_PROPERTY_SELECTION, propertyValue);
	base_display(&label);
}

static void control_bar_displayBtnIndex(ControlBar_s *p_controlBar, uint8_t buttonIndex)
{
	if (buttonIndex >= CONTROL_BAR_BUTTON_COUNT)
	{
		return;
	}

	const uint16_t y = buttonIndex * CONTROL_BAR_BUTTON_HEIGHT;
	const bool selected = buttonIndex == p_controlBar->selectedButton;

	control_bar_displayBtn(p_controlBar->iconList[buttonIndex], 0, y, selected);
}

static int8_t control_bar_getPressedBtnIdx(ControlBar_s *p_controlBar, uint16_t yPressed)
{
	int8_t index = -1;
	uint16_t y = 0;

	for (uint8_t i = 0; i < CONTROL_BAR_BUTTON_COUNT; i++)
	{
		if ((yPressed >= y) && (yPressed <= (y + CONTROL_BAR_BUTTON_HEIGHT)))
		{
			if (p_controlBar->iconList[i] != FILE_KEY_NONE)
			{
				index = i;
			}

			break;
		}

		y += CONTROL_BAR_BUTTON_HEIGHT;
	}

	return index;
}
