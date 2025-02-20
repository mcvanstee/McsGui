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

#include "gui_config.h"
#include "Core/gui_basecomponent.h"


typedef struct text_block_s
{
    BaseComponent_s base;
    FontData_s fontData;
    void (*valueChanged)(void);
    char text[GUI_CONFIG_TEXTBLOCK_MAX_STRING_LENGTH_INC_NULL];
} TextBlock_s;


TextBlock_s *textblock_new(void);
TextBlock_s *textblock_newInit(void);

void textblock_delete(BaseComponent_s *p_textBlockBase);
void textblock_init(TextBlock_s *p_textBlock);
void textblock_initText(TextBlock_s *p_textBlock, const char *p_text);
void textblock_initTextSize(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t width, const uint16_t height);

void textblock_initTextPos(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t x, const uint16_t y);

void textblock_initTextPosSize(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height);

void textblock_initTextPosSizeBack(
        TextBlock_s *p_textBlock, const char *p_text,
        const uint16_t x, const uint16_t y,
        const uint16_t width, const uint16_t height,
        const Color_t color);

void textblock_setText(TextBlock_s *p_textBlock, const char *p_text);
void textblock_setFont(TextBlock_s *p_textBlock, const uint8_t font);
void textblock_setValueChanged(TextBlock_s *p_textBlock, void (*valueChanged)(void));

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_TEXTBLOCK_H_ */


/*** end of file ***/
