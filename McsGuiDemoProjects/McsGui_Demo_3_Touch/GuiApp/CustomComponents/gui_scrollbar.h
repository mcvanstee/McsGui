#ifndef CUSTOMCOMPONENTS_GUI_SCROLLBAR_H_
#define CUSTOMCOMPONENTS_GUI_SCROLLBAR_H_

#include "mcsgui.h"
#include "fs_file_search.h"

#define SCROLLBAR_MIN_THUMB_SIZE 10
#define SCROLLBAR_MAX_THUMB_SIZE 50
#define SCROLLBAR_DEFAULT_THUMB_SIZE 20
#define SCROLLBAR_DEFAULT_THUMB_POSITION 0

typedef enum
{
    Scrollbar_Vertical,
    Scrollbar_Horizontal
} ScrollBarOrientation_e;

typedef struct
{
    BaseComponent_s base;
    Button_s upButton;
    Button_s downButton;
    Touch_s upButtonTouch;
    Touch_s downButtonTouch;
    GuiAnchor_s anchor;
    uint16_t thumbSize;
    uint16_t thumbPosition;
    uint16_t thumbMinSize;
    uint16_t thumbMaxSize;
    uint8_t thumbAreaWidth;
    ScrollBarOrientation_e orientation;
    uint8_t thumbRadius;
    Color_t thumbColor;
    uint8_t thumbAreaRadius;
    uint8_t thumbAreaBorderThickness;
    Color_t thumbAreaBorderColor;
    ListView_s *p_listView;
} ScrollBar_s;

ScrollBar_s *scrollbar_new(void);
ScrollBar_s *scrollbar_newInit(void);
void scrollbar_init(ScrollBar_s *p_scrollBar);

void scrollbar_addListview(ScrollBar_s *p_scrollBar, ListView_s *p_listView);
void scrollbar_setWidth(ScrollBar_s *p_scrollBar, uint16_t width);
void scrollbar_setHeight(ScrollBar_s *p_scrollBar, uint16_t height);
void scrollbar_setThumbAreaWidth(ScrollBar_s *p_scrollBar, uint8_t width);
void scrollbar_setThumbAreaColor(ScrollBar_s *p_scrollBar, const Color_t color);
void scrollbar_setThumbRadius(ScrollBar_s *p_scrollBar, uint8_t radius);
void scrollbar_setThumbColor(ScrollBar_s *p_scrollBar, const Color_t color);
void scrollbar_setThumbAreaRadius(ScrollBar_s *p_scrollBar, uint8_t radius);
void scrollbar_setThumbAreaBorderThickness(ScrollBar_s *p_scrollBar, uint8_t thickness);
void scrollbar_setThumbAreaBorderColor(ScrollBar_s *p_scrollBar, const Color_t color);

void scrollbar_setUpIcon(ScrollBar_s *p_scrollBar, const file_key_e icon);
void scrollbar_setDownIcon(ScrollBar_s *p_scrollBar, const file_key_e icon);
void scrollbar_setButtonSize(ScrollBar_s *p_scrollBar, uint16_t width, uint16_t height);

void scrollbar_setThumbSize(ScrollBar_s *p_scrollBar, uint16_t thumbSize);
void scrollbar_setThumbPosition(ScrollBar_s *p_scrollBar, uint16_t thumbPosition);
void scrollbar_setThumbMinSize(ScrollBar_s *p_scrollBar, uint16_t thumbMinSize);
void scrollbar_setThumbMaxSize(ScrollBar_s *p_scrollBar, uint16_t thumbMaxSize);
void scrollbar_setOrientation(ScrollBar_s *p_scrollBar, ScrollBarOrientation_e orientation);



#endif /* CUSTOMCOMPONENTS_GUI_SCROLLBAR_H_ */
