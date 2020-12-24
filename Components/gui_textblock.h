/** @file gui_textblock.h
 *
 * @par COPYRIGHT NOTICE:
 * Copyright (c) 2020, Marijn van Stee, all rights reserved.
 *
 */

#ifndef MCSGUI_COMPONENTS_GUI_TEXTBLOCK_H_
#define MCSGUI_COMPONENTS_GUI_TEXTBLOCK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "McsGui/gui_config.h"
#include "McsGui/Core/gui_basecomponent.h"


typedef struct text_block_s
{
    BaseComponent_s base;
    FontData_s fontData;
#if !GUI_USE_DYNAMIC_MEMORY
    char bmpName[GUI_CONFIG_BITMAP_NAME_LENGTH_INC_NULL];
#endif /* GUI_USE_DYNAMIC_MEMORY */
} TextBlock_s;


#if GUI_USE_DYNAMIC_MEMORY
TextBlock_s *textblock_new(void);
#endif /* GUI_USE_DYNAMIC_MEMORY */

void textblock_delete(BaseComponent_s *p_textBlockBase);
void textblock_init(TextBlock_s *p_textBlock);
void textblock_init_1(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t xPos, const uint16_t yPos);

void textblock_init_2(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height);

void textblock_init_3(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t xPos, const uint16_t yPos,
        const uint16_t width, const uint16_t height,
        const Color_t color);

void textblock_setText(TextBlock_s *p_textBlock, const char *p_text);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_TEXTBLOCK_H_ */


/*** end of file ***/
