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

typedef enum
{
  Text_Align_Left = 1,   /**/
  Text_Align_Right = 2,  /**/
  Text_Align_Center = 3, /**/
  Text_Align_Top = 4,    /**/
  Text_Align_Bottom = 5  /**/
} TextAlignment_e;

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
void textblock_setFontForeColor(TextBlock_s *p_textBlock, const Color_t foreColor);
void textblock_setFontBackColor(TextBlock_s *p_textBlock, const Color_t backColor);
void textblock_setFontAndColor(TextBlock_s *p_textBlock, const uint8_t font, const Color_t foreColor, const Color_t backColor);
void textblock_setValueChanged(TextBlock_s *p_textBlock, void (*valueChanged)(void));

void textblock_setTextAlignment(TextBlock_s *p_textBlock, const TextAlignment_e horizontal, const TextAlignment_e vertical);
void textblock_setHorizontalTextAlignment(TextBlock_s *p_textBlock, const TextAlignment_e alignment);
void textblock_setVerticalTextAlignment(TextBlock_s *p_textBlock, const TextAlignment_e alignment);

void textblock_setTextPadding(TextBlock_s *p_textBlock, const uint8_t left, const uint8_t right, const uint8_t top, const uint8_t bottom);
void textblock_setLeftTextPadding(TextBlock_s *p_textBlock, const uint8_t padding);
void textblock_setRightTextPadding(TextBlock_s *p_textBlock, const uint8_t padding);
void textblock_setTopTextPadding(TextBlock_s *p_textBlock, const uint8_t padding);
void textblock_setBottomTextPadding(TextBlock_s *p_textBlock, const uint8_t padding);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* MCSGUI_COMPONENTS_GUI_TEXTBLOCK_H_ */


/*** end of file ***/
