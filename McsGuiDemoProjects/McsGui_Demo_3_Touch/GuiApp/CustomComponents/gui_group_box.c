#include "gui_group_box.h"

#include "gui_app.h"
#include "Graphics/gui_graphics.h"
#include "Core/gui_memory.h"

#define GUI_GROUP_BOX_BUFFER_SIZE 5

#if !GUI_USE_DYNAMIC_MEMORY
static bool staticGroupBoxMemInUse[GUI_GROUP_BOX_BUFFER_SIZE];
static GroupBox_s staticGroupBoxMem[GUI_GROUP_BOX_BUFFER_SIZE];
#endif /* GUI_USE_DYNAMIC_MEMORY */

static void group_box_onDisplay(BaseComponent_s *p_base);
static void group_box_delete(BaseComponent_s *p_base);

GroupBox_s* group_box_new(void)
{
#if GUI_USE_DYNAMIC_MEMORY
	return gui_mem_malloc(sizeof(GroupBox_s));
#else
	for (uint32_t i = 0; i < GUI_GROUP_BOX_BUFFER_SIZE; i++)
	{
		if (!staticGroupBoxMemInUse[i])
		{
			staticGroupBoxMemInUse[i] = true;

			return &staticGroupBoxMem[i];
		}
	}

	gui_log_write(GUI_LOG_LEVEL_ERROR, "No GroupBox_s static memory");

	return NULL;
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

GroupBox_s* group_box_newInit(void)
{
	GroupBox_s *p_groupBox = group_box_new();
	group_box_init(p_groupBox);

	return p_groupBox;
}

static void group_box_delete(BaseComponent_s *p_groupBoxBase)
{
	base_clear(p_groupBoxBase);

#if GUI_USE_DYNAMIC_MEMORY
    gui_mem_free(p_groupBoxBase, sizeof(GroupBox_s));
#else
	for (uint32_t i = 0; i < GUI_GROUP_BOX_BUFFER_SIZE; i++)
	{
		if (&staticGroupBoxMem[i].rect.base == p_groupBoxBase)
		{
			staticGroupBoxMemInUse[i] = false;

			break;
		}
	}
#endif /* GUI_USE_DYNAMIC_MEMORY */
}

void group_box_init(GroupBox_s *p_groupBox)
{
	rectangle_initBorderSize(&p_groupBox->rect,
			0, 0, 1, COLOR_SEPARATOR);
	p_groupBox->title = FILE_KEY_NONE;
	p_groupBox->titleHeightOffset = 0;
	base_setOnDelete(p_groupBox, group_box_delete);
	base_setOnDisplay(p_groupBox, group_box_onDisplay);
}

void group_box_setTitleHeightOffset(GroupBox_s *p_groupBox, int8_t offset)
{
    p_groupBox->titleHeightOffset = offset;
}

void group_box_addComponent(GroupBox_s *p_groupBox, void *p_component)
{
	base_addChild(&p_groupBox->rect.base, p_component);
}

GroupBox_s *group_box_newInitTitleSize(
		file_key_e title, uint16_t width, uint16_t height)
{
	GroupBox_s *p_groupBox = group_box_newInit();
	base_setDimensions(&p_groupBox->rect.base, width, height);
	p_groupBox->title = title;

	return p_groupBox;
}

GroupBox_s *group_box_newInitTitlePosSize(
		file_key_e title, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
	GroupBox_s *p_groupBox = group_box_newInit();
	base_setPosition(&p_groupBox->rect.base, x, y);
	base_setDimensions(&p_groupBox->rect.base, width, height);
	p_groupBox->title = title;

	return p_groupBox;
}

static void group_box_onDisplay(BaseComponent_s *p_base)
{
	GroupBox_s *p_groupBox = (GroupBox_s*)p_base;

    if (p_base->p_anchor != NULL)
    {
        graphics_setPosistionFromAnchor(p_base);
    }

	Label_s titleLabel;
	label_initBmp(&titleLabel, p_groupBox->title);
	gui_app_translate(&titleLabel);
	graphics_setSizeFromBmp(&titleLabel.base);
	const uint16_t y = p_base->y - (titleLabel.base.height / 2) + p_groupBox->titleHeightOffset;
	base_setPosition(&titleLabel.base, p_base->x + 10, y);

	graphics_displayComponent(&p_groupBox->rect.base);
	base_display(&titleLabel);
}

