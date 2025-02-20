#ifndef CUSTOMCOMPONENTS_GUI_GROUP_BOX_H_
#define CUSTOMCOMPONENTS_GUI_GROUP_BOX_H_

#include "mcsgui.h"
#include "fs_file_search.h"

typedef struct
{
	Rectangle_s rect;
	file_key_e title;
	int8_t titleHeightOffset;
} GroupBox_s;

GroupBox_s *group_box_new(void);
GroupBox_s *group_box_newInit(void);
GroupBox_s *group_box_newInitTitleSize(
		file_key_e title, uint16_t width, uint16_t height);
GroupBox_s *group_box_newInitTitlePosSize(
		file_key_e title, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
void group_box_init(GroupBox_s *p_groupBox);

void group_box_setTitleHeightOffset(GroupBox_s *p_groupBox, int8_t offset);
void group_box_addComponent(GroupBox_s *p_groupBox, void *p_component);

#endif /* CUSTOMCOMPONENTS_GUI_GROUP_BOX_H_ */
